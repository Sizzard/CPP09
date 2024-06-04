/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:02:34 by facarval          #+#    #+#             */
/*   Updated: 2024/06/04 10:42:31 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool input_error(int ac, char **av, std::fstream &db, std::fstream &input)
{
    if (ac != 2)
    {
        std::cerr << red << "The program needs 1 argument" << reset << std::endl;
        return true;
    }

    db.open("data.csv", std::fstream::in);
    if (db.is_open() == false)
    {
        std::cerr << red << "Error Opening data.csv or modified data.csv file" << reset << std::endl;
        return true;
    }

    if (strcmp(av[1], "data.csv") == 0)
    {
        std::cerr << red << "Can't have same database and input file " << reset << std::endl;
        return true;
    }

    input.open(av[1], std::fstream::in);
    if (input.is_open() == false)
    {
        std::cerr << red << "Error Opening " << av[1] << reset << std::endl;
        return true;
    }
    return false;
}

int detect_type(std::string const &str)
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

bool line_error(std::string const &line, struct tm &tm)
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
    tm.tm_year = std::atoi(line.c_str());
    tm.tm_mon = std::atoi(line.substr(5, 7).c_str());
    tm.tm_mday = std::atoi(line.substr(8, 10).c_str());

    // std::cout << day << " ";

    if (tm.tm_year < 2009 || tm.tm_year > 2023 || tm.tm_mon < 1 || tm.tm_mon > 12 || tm.tm_mday < 1 || tm.tm_mday > 31)
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

    // std::cout << nb_btc << " ";

    if (nb_btc < 0.1 || nb_btc > 999.9 || detect_type(&line[13]) == -1)
    {
        std::cout << red << "Error: --> " << line << " :Number must be between 0 and 1000" << reset << std::endl;
        return true;
    }

    // std::cout << green << line << reset << std::endl;

    return false;
}

void ft_compare(std::map<std::string, float> &db_map, std::string const &line)
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

void parsing(std::fstream &input, std::map<std::string, float> &db_map, struct tm &tm)
{
    std::string line;

    while (getline(input, line))
    {
        if (line.empty() == true)
        {
            std::cout << std::endl;
        }
        else if (line.size() < 12)
        {
            std::cerr << red << "Error: line too short for a possible input" << reset << std::endl;
        }
        else if (line_error(line, tm) == true)
            ;
        else
        {
            ft_compare(db_map, line);
        }
    }
    return;
}

void db_to_db_map(std::fstream &db, std::map<std::string, float> &db_map)
{
    std::string line;
    getline(db, line);
    while (getline(db, line))
    {
        db_map.insert(std::make_pair(line.substr(0, 10), std::strtof(line.substr(11, 12).c_str(), 0)));
    }
    return;
}

int main(int ac, char **av)
{
    std::fstream db, input;
    struct tm tm;
    memset(&tm, 0, sizeof(tm));

    if (input_error(ac, av, db, input) == true)
        return (1);

    std::map<std::string, float> db_map;

    db_to_db_map(db, db_map);

    parsing(input, db_map, tm);

    std::cout << std::endl;

    // for (std::map<std::string, float>::iterator it = map.begin(); it != map.end(); it++)
    // {
    //     std::cout << it->first << " " << it->second << std::endl;
    // }

    // for (std::map<std::string, float>::iterator it = db_map.begin(); it != db_map.end(); it++)
    // {
    //     std::cout << it->first << " " << it->second << std::endl;
    // }

    // for (std::map<std::string, float>::iterator it = map.begin(); it != map.end(); it++)
    // {
    //     for (std::map<std::string, float>::iterator db_it = db_map.begin(); db_it != db_map.end(); db_it++)
    //     {
    //         if (db_it->first.compare(it->first.c_str()) > 0)
    //         {
    //             std::cout << it->first << " " << db_it->first << std::endl;
    //             std::cout << "str -" << std::endl;
    //             break;
    //         }
    //     }
    // }

    return 0;
}