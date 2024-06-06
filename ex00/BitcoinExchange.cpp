/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:59:22 by facarval          #+#    #+#             */
/*   Updated: 2024/06/06 13:20:03 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    return;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &cpy)
{
    *this = cpy;
    return;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &cpy)
{
    this->db_map = cpy.db_map;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
    return;
}

int BitcoinExchange::detect_type(std::string const &str)
{
    unsigned long i = 0;
    int counter = 0;

    if (str[str.length() - 1] == '.')
        return -1;
    while (i < str.length())
    {
        if (str[i] == '.')
            counter++;
        i++;
    }
    if (counter > 1)
        return -1;
    if (str.length() == 1 && isprint(str[0]) != 0)
    {
        if (isdigit(str[0]))
            return 1;
        return 1;
    }
    i = 0;
    if (str[i] == '-')
        i++;
    while (i < str.length() && isdigit(str[i]))
    {
        i++;
    }
    if (str[i] != '.')
    {
        if (str[i] && isdigit(str[i + 1]) == 0)
        {
            return -1;
        }
        return 1;
    }
    i++;
    while (i < str.length() && isdigit(str[i]))
    {
        i++;
    }
    if (str[i] == 'f')
    {
        if (isdigit(str[i - 1]))
            return 1;
        return -1;
    }
    return 1;
}

bool BitcoinExchange::line_error(std::string const &line)
{
    if (line.find_first_of(" | ") != 10)
    {
        std::cout << red << "Error: --> " << line << " :Format not valid it must look like this YYYY-MM-DD | x " << reset << std::endl;
        return true;
    }

    int i = 0;
    while (i < 4)
    {
        if (isdigit(line[i]) == 0)
        {
            std::cout << red << "Error: --> " << line << " :Format not valid it must look like this YYYY-MM-DD | x " << reset << std::endl;
            return true;
        }
        i++;
    }

    if (line[4] != '-')
    {
        std::cout << red << "Error: --> " << line << " :Format not valid it must look like this YYYY-MM-DD | x " << reset << std::endl;
        return true;
    }
    i++;

    while (i < 7)
    {
        if (isdigit(line[i]) == 0)
        {
            std::cout << red << "Error: --> " << line << " :Format not valid it must look like this YYYY-MM-DD | x " << reset << std::endl;
            return true;
        }
        i++;
    }

    if (line[7] != '-')
    {
        std::cout << red << "Error: --> " << line << " :Format not valid it must look like this YYYY-MM-DD | x " << reset << std::endl;
        return true;
    }
    i++;

    while (i < 9)
    {
        if (isdigit(line[i]) == 0)
        {
            std::cout << red << "Error: --> " << line << " :Format not valid it must look like this YYYY-MM-DD | x " << reset << std::endl;
            return true;
        }
        i++;
    }
    int tm_year = std::atoi(line.c_str());
    int tm_mon = std::atoi(line.substr(5, 7).c_str());
    int tm_mday = std::atoi(line.substr(8, 10).c_str());

    if (tm_year < 2009 || tm_year > 2023 || tm_mon < 1 || tm_mon > 12 || tm_mday < 1 || tm_mday > 31)
    {
        std::cout << red << "Error: --> " << line << " :Invalid date" << reset << std::endl;
        return true;
    }

    if (line.length() < 13)
    {
        std::cout << red << "Error: --> " << line << " :Number must be between 0 and 1000" << reset << std::endl;
        return true;
    }
    float nb_btc = std::strtof(&line[13], 0);

    if (nb_btc < 0.1 || nb_btc > 999.9 || detect_type(&line[13]) == -1)
    {
        std::cout << red << "Error: --> " << line << " :Number must be between 0 and 1000" << reset << std::endl;
        return true;
    }
    
    int calendar[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (calendar[tm_mon - 1] < tm_mday)
    {
        std::cout << red << "Error: --> " << line << " :Invalid date" << reset << std::endl;
        return true;
    } 

    return false;
}

void BitcoinExchange::ft_compare(std::string const &line)
{
    std::map<std::string, float>::iterator it = db_map.upper_bound(line.substr(0, 10));
    if (it != db_map.begin())
    {
        it--;
        std::cout << green << line << " = " << it->second * std::strtof(&line[13], 0) << reset << std::endl;
    }
    else
    {
        std::cout << red << "Error: --> " << line << " :No date prior to : " << it->first << " found in database" << reset << std::endl;
    }
}

void BitcoinExchange::parsing(std::fstream &input)
{
    std::string line;

    while (getline(input, line))
    {
        if (line.empty() == true)
        {
            std::cout << std::endl;
        }
        else if (line.length() < 12)
        {
            std::cerr << red << "Error: line too short for a possible input" << reset << std::endl;
        }
        else if (line_error(line) == true)
            ;
        else
        {
            ft_compare(line);
        }
    }
    return;
}

void BitcoinExchange::db_to_db_map(std::fstream &db)
{
    std::string line;
    getline(db, line);
    while (getline(db, line))
    {
        db_map.insert(std::make_pair(line.substr(0, 10), std::strtof(line.substr(11, 12).c_str(), 0)));
    }
    return;
}

void BitcoinExchange::run(char *infile)
{
    std::fstream db_stream, input;

    if (input_error(infile, db_stream, input) == true)
        return;

    db_to_db_map(db_stream);

    parsing(input);
}

bool BitcoinExchange::input_error(char *av, std::fstream &db, std::fstream &input)
{
    db.open("data.csv", std::fstream::in);
    if (db.is_open() == false)
    {
        std::cerr << red << "Error Opening data.csv or modified data.csv file" << reset << std::endl;
        return true;
    }

    if (strcmp(av, "data.csv") == 0)
    {
        std::cerr << red << "Can't have same database and input file " << reset << std::endl;
        return true;
    }

    input.open(av, std::fstream::in);
    if (input.is_open() == false)
    {
        std::cerr << red << "Error Opening " << av << reset << std::endl;
        return true;
    }
    return false;
}