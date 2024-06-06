/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:36:38 by facarval          #+#    #+#             */
/*   Updated: 2024/06/06 11:52:05 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    return;
}

PmergeMe::PmergeMe(PmergeMe const &cpy)
{
    *this = cpy;
    return;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &cpy)
{
    this->vector = cpy.vector;
    this->deque = cpy.deque;
    this->strings = cpy.strings;
    return *this;
}

PmergeMe::~PmergeMe()
{
    return;
}

bool PmergeMe::init_containers(int ac, char **av)
{
    if (ac < 3)
    {
        std::cerr << red << "The algorithm needs at least 2 arguments" << reset << std::endl;
        return true;
    }

    for (int i = 1; i < ac; i++)
    {
        this->strings.push_back(av[i]);
    }

    for (std::vector<std::string>::iterator it = this->strings.begin(); it != this->strings.end(); it++)
    {
        if (it->find_first_not_of("0123456789") != it->npos)
        {
            std::cerr << red << "Error" << reset << std::endl;
            return true;
        }
        this->deque.push_back(std::atoi(it->c_str()));
    }
    this->vector.assign(this->deque.begin(), this->deque.end());
    
    return false;
}

void PmergeMe::merge(std::vector<int> &left, std::vector<int> &right, std::vector<int> &vec)
{
    int leftSize = vec.size() / 2;
    int rightSize = vec.size() - leftSize;
    int i = 0, l = 0, r = 0;

    while (l < leftSize && r < rightSize)
    {
        if (left[l] < right[r])
        {
            vec[i] = left[l];
            l++;
        }
        else
        {
            vec[i] = right[r];
            r++;
        }
        i++;
    }
    while (l < leftSize)
    {
        vec[i] = left[l];
        l++;
        i++;
    }
    while (r < rightSize)
    {
        vec[i] = right[r];
        i++;
        r++;
    }
}

void PmergeMe::mergeSort(std::vector<int> &vec)
{
    if (vec.size() <= 1)
        return;

    std::vector<int>::iterator mid = vec.begin() + vec.size() / 2;

    std::vector<int> left;
    std::vector<int> right;

    std::vector<int>::iterator i = vec.begin();

    for (; i != vec.end(); i++)
    {
        if (i < mid)
        {
            left.push_back(*i);
        }
        else
        {
            right.push_back(*i);
        }
    }
    mergeSort(left);
    mergeSort(right);
    merge(left, right, vec);
    return;
}

void create_pairs(std::vector<int> &vec, vector_pair &vec_pair)
{
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
    {
        std::pair<int, int> pair(*it , *(++it));
        vec_pair.push_back(pair);
    }
    return ;
}

void sort_pairs(vector_pair &vec_pair)
{
    for(vector_pair::iterator it = vec_pair.begin(); it != vec_pair.end(); it++)
    {
        if (it->first > it->second)
        {
            std::swap(it->first,it->second);
        }
    }
    return ;
}

void sort_vec_pairs(vector_pair &vec_pair)
{
    if (vec_pair.size() <= 1)
        return;
    vector_pair::iterator mid = vec_pair.begin() + (vec_pair.size() / 2);
    
    vector_pair left(vec_pair.begin(), mid);
    vector_pair right(mid, vec_pair.end());
    sort_vec_pairs(left);
    sort_vec_pairs(right);
    
    vector_pair::iterator l = left.begin();
    vector_pair::iterator r = right.begin();
    int i = 0;
    while (l != left.end() && r != right.end())
    {
        if (l->second < r->second)
        {
            vec_pair[i] = *l;
            l++;
        }
        else
        {
            vec_pair[i] = *r;
            r++;
        }
        i++;
    }
    while(l != left.end())
    {
        vec_pair[i++] = *l++;
    }
    while(r != right.end())
    {
        vec_pair[i++] = *r++;
    }
}

std::vector<int> generateJacobsthal(int n) 
{
    std::vector<int> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    
    while (jacobsthal.back() < n) {
        int next = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
        if (next >= n) break;
        jacobsthal.push_back(next);
    }
    return jacobsthal;
}

int PmergeMe::binarySearchInsert(int value)
{
    int low = 0;
    int high = this->vector.size();
    while (low < high) {
        int mid = (low + high) / 2;
        if (this->vector[mid] < value) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

void PmergeMe::insertInOrder(int value) 
{
    int pos = binarySearchInsert(value);
    this->vector.insert(this->vector.begin() + pos, value);
}

void PmergeMe::fordJohnsonSort(vector_pair const &vec) 
{
    std::vector<int> jacobsthal = generateJacobsthal(vec.size());
    
    this->vector.clear();
    place_all_greater(vec);
    
    for (size_t i = 0; i < vec.size(); ++i) {
        int value = vec[i].first; 
        insertInOrder(value);
    }
}

void PmergeMe::place_all_greater(vector_pair const &vec_pair)
{
    for(vector_pair::const_iterator it = vec_pair.begin(); it != vec_pair.end(); it++)
    {
        this->vector.push_back(it->second);
    }
}

template <class T>
void print_container(T cont, bool before)
{
    if (before == 1)
        std::cout << "Before : ";
    else
        std::cout << "After : ";
    for(typename T::const_iterator it = cont.begin(); it != cont.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
    
}

void PmergeMe::FJMI(std::vector<int> &vec)
{
    vector_pair vec_pair;
    bool isOdd = vec.size() % 2;
    int lastOdd;

    if (isOdd)
    {
        lastOdd = vec.back();
        vec.pop_back();
    }
    create_pairs(vec, vec_pair);
    sort_pairs(vec_pair);
    sort_vec_pairs(vec_pair);
    fordJohnsonSort(vec_pair);
    
    if (isOdd)
        insertInOrder(lastOdd);

    return ;
}

void print_time(clock_t start, clock_t end)
{
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    
    std::cout << "Time to process a range of 5 elements with std::vector : " << std::fixed 
         << time_taken;
    std::cout << " sec " << std::endl;
}

void vector_route()
{

}

void PmergeMe::run(int ac, char **av)
{
    if (init_containers(ac, av) == true)
        return;
    
    print_container(this->vector, 1);
    
    clock_t start,end;

    start = clock();
    
    FJMI(this->vector);
    
    end = clock();
    
    print_container(this->vector, 0);
        
    print_time(start, end);
    
    this->vector.clear();
    this->deque.clear();
    this->strings.clear();
    return;
}