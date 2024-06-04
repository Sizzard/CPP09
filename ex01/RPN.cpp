/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:06:45 by facarval          #+#    #+#             */
/*   Updated: 2024/06/04 14:15:26 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

Rpn::Rpn()
{
    return;
}

Rpn::Rpn(Rpn const &cpy)
{
    *this = cpy;
    return;
}

Rpn &Rpn::operator=(Rpn const &cpy)
{
    (void)cpy;
    // Copy what you want : this->name = cpy.name
    return *this;
}

Rpn::~Rpn()
{
    return;
}

bool Rpn::parsing_error()
{
    if (line.find_first_not_of("0123456789+-*/ ") != line.npos)
    {
        std::cerr << red << "Error" << reset << std::endl;
        return true;
    }
    return false;
}

bool is_valid_char(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

void Rpn::do_op(std::string::iterator it)
{
    std::list<long>::iterator it_stack = this->stack.end();
    it_stack--;
    long tmp = *it_stack;
    it_stack--;

    if (*it == '+')
    {
        *it_stack += tmp;
        this->stack.pop_back();
        it_stack = this->stack.end();
    }
    else if (*it == '-')
    {
        *it_stack -= tmp;
        this->stack.pop_back();
    }
    else if (*it == '*')
    {
        *it_stack *= tmp;
        this->stack.pop_back();
    }
    else if (*it == '/')
    {
        *it_stack /= tmp;
        this->stack.pop_back();
    }
    return;
}

void Rpn::calculate()
{

    for (std::string::iterator it = this->line.begin(); it != this->line.end(); it++)
    {
        if (std::isdigit(*it))
        {
            this->stack.push_back(*it - 48);
        }
        else if (is_valid_char(*it))
        {
            if (this->stack.size() < 2)
            {
                std::cerr << red << "Error" << reset << std::endl;
                return;
            }
            else
            {
                do_op(it);
            }
        }
        else
        {
            std::cerr << red << "Error" << reset << std::endl;
            return;
        }
        it++;
        if (it == this->line.end())
            break;
        else if (isspace(*it) == false)
        {
            std::cerr << red << "Error" << reset << std::endl;
            return;
        }
    }
    return;
}

void Rpn::run(char *line)
{
    this->line = line;

    if (this->parsing_error() == true)
        return;

    this->calculate();

    if (this->stack.size() != 1)
    {
        std::cerr << red << "Error" << reset << std::endl;
        return;
    }

    std::cout << this->stack.front() << std::endl;
    return;
}