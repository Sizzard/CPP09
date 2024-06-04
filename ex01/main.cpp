/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:06:08 by facarval          #+#    #+#             */
/*   Updated: 2024/06/04 11:34:44 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << red << "The program needs 1 argument" << reset << std::endl;
        return 1;
    }
    Rpn rpn;
    
    rpn.run(av[1]);
    return 0;
}