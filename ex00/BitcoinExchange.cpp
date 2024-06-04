/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:59:22 by facarval          #+#    #+#             */
/*   Updated: 2024/05/30 10:00:08 by facarval         ###   ########.fr       */
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
    (void)cpy;
    // Copy what you want : this->name = cpy.name
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
    return;
}