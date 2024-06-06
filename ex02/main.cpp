/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:34:03 by facarval          #+#    #+#             */
/*   Updated: 2024/06/06 17:19:15 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    try{
    PmergeMe merge_sort;

    merge_sort.run(ac, av);

    }
    catch(std::exception const &e)
    {
        std::cerr << red << e.what() << reset << std::endl;
    }
    return 0;
}