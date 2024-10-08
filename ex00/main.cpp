/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:02:34 by facarval          #+#    #+#             */
/*   Updated: 2024/06/05 11:50:40 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"



int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << red << "The program needs 1 argument" << reset << std::endl;
        return 1;
    }

    BitcoinExchange btc;

    btc.run(av[1]);

    return 0;
}