/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:59:35 by facarval          #+#    #+#             */
/*   Updated: 2024/06/04 11:31:17 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <sys/stat.h>
#include <cstdlib>
#include <time.h>
#include <map>

const std::string red("\033[1;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string blue("\033[1;34m");
const std::string cyan("\033[1;36m");
const std::string magenta("\033[1;35m");
const std::string reset("\033[0m");

class BitcoinExchange
{
private:
    std::map<std::string, float> db_map;

    bool input_error(char *av, std::fstream &db, std::fstream &input);
    void db_to_db_map(std::fstream &db);
    int detect_type(std::string const &str);
    bool line_error(std::string const &line);
    void ft_compare(std::string const &line);
    void parsing(std::fstream &input);

public:
    BitcoinExchange();
    BitcoinExchange(BitcoinExchange const &to_cpy);
    BitcoinExchange &operator=(BitcoinExchange const &cpy);
    ~BitcoinExchange();

    void run(char *infile);
};