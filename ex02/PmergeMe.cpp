/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:36:38 by facarval          #+#    #+#             */
/*   Updated: 2024/06/06 17:43:16 by facarval         ###   ########.fr       */
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

template <class T, class T_P>
void create_pairs(T &vec, T_P &vec_pair)
{
    for (typename T::iterator it = vec.begin(); it != vec.end(); it++)
    {
        std::pair<int, int> pair(*it , *(++it));
        vec_pair.push_back(pair);
    }
    return ;
}

template <class T_P>
void sort_pairs(T_P &vec_pair)
{
    for(typename T_P::iterator it = vec_pair.begin(); it != vec_pair.end(); it++)
    {
        if (it->first > it->second)
        {
            std::swap(it->first,it->second);
        }
    }
    return ;
}

template <class T_P>
void sort_vec_pairs(T_P &vec_pair)
{
    if (vec_pair.size() <= 1)
        return;
   typename T_P::iterator mid = vec_pair.begin() + (vec_pair.size() / 2);
    
    T_P left(vec_pair.begin(), mid);
    T_P right(mid, vec_pair.end());
    sort_vec_pairs(left);
    sort_vec_pairs(right);
    
   typename T_P::iterator l = left.begin();
   typename T_P::iterator r = right.begin();
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

template <class T,class T_P>
void place_all_greater(T &vec, T_P const &vec_pair)
{
    for(typename T_P::const_iterator it = vec_pair.begin(); it != vec_pair.end(); it++)
    {
        vec.push_back(it->second);
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

template <class T>
int binarySearchInsert(T const & v, int value, std::vector<int> const &jacob)
{
    int n = v.size();
    int low = 0;
    int high = n - 1;
    int jcb = jacob.size();
    int mid = 0;

    while(low <= high)
    {
        jcb--;
        if(jacob_idx < 0)
            mid = low;
        else
            mid = low + jacob[jcb];
        if (mid >= n)
            mid = n - 1;
        if (v[mid] == value)
            return (mid);
        else if(v[mid] < value)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return(low);
}

template <class T>
void insertInOrder(T& vec, int value, const std::vector<int>& jacob) 
{
    int pos = binarySearchInsert(vec, value, jacob);
    vec.insert(vec.begin() + pos, value);
}

template <class T, class T_P>
void fordJohnsonSort(T& vec, const T_P& vec_pair, const std::vector<int>& jacob) 
{
    vec.clear();
    place_all_greater(vec, vec_pair);
    for (typename T_P::const_iterator it = vec_pair.begin(); it != vec_pair.end(); ++it) {
        insertInOrder(vec, it->first, jacob);
    }
}

template <class T>
void print_container(T cont, bool before)
{
    if (before == 1)
        std::cout << magenta << "Before : ";
    else
        std::cout << green << "After : ";
    for(typename T::const_iterator it = cont.begin(); it != cont.end(); it++)
        std::cout << *it << " ";
    std::cout << reset << std::endl;
    
}

template <class T,class T_P>
void FJMI(T &vec, T_P &vec_pair, std::vector<int> const &jacob)
{    
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

    fordJohnsonSort(vec, vec_pair, jacob);
    
    if (isOdd)
        insertInOrder(vec, lastOdd, jacob);

    return ;
}

void print_time(clock_t start, clock_t end, std::string const &cont)
{
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    
    std::cout << "Time to process a range of 5 elements with std::" << cont  << ": " << std::fixed 
         << time_taken;
    std::cout << " sec " << std::endl;
}

void PmergeMe::run(int ac, char **av)
{
    if (init_containers(ac, av) == true)
        return;
    
    vector_pair vec_pair;
    deque_pair deq_pair;
    std::vector<int> const jacob = generateJacobsthal(1431655765);
    
    print_container(this->vector, 1);
    
    clock_t start,end;

    start = clock();
    
    FJMI(this->vector, vec_pair, jacob);
    
    end = clock();
    
    print_container(this->vector, 0);
    
    print_time(start, end, "vector");

    start = clock();
    
    FJMI(this->deque,deq_pair, jacob);

    end = clock();

    print_time(start, end, "deque");

    this->vector.clear();
    this->deque.clear();
    this->strings.clear();
    return;
}