/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:36:26 by facarval          #+#    #+#             */
/*   Updated: 2024/06/06 11:45:24 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <cstdlib>
#include <iomanip>

const std::string red("\033[1;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string blue("\033[1;34m");
const std::string cyan("\033[1;36m");
const std::string magenta("\033[1;35m");
const std::string reset("\033[0m");

typedef std::vector<std::pair<int, int> > vector_pair;
typedef std::deque<std::pair<int, int> > deque_pair;


class PmergeMe
{
private:
    std::deque<int> deque;    
    std::vector<int> vector;
    std::vector<std::string> strings;

    bool init_containers(int ac, char **av);
    void mergeSort(std::vector<int> &vector);
    void merge(std::vector<int> &left, std::vector<int> &right, std::vector<int> &vec);
    void FJMI(std::vector<int> &vec);
    int binarySearchInsert(int value);
    void insertInOrder(int value);
    void place_all_greater(vector_pair const &vec_pair);
    void fordJohnsonSort(vector_pair const &vec);

public:
    PmergeMe();
    PmergeMe(PmergeMe const &to_cpy);
    PmergeMe &operator=(PmergeMe const &cpy);
    ~PmergeMe();

    void run(int ac, char **av);
};