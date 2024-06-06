/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:06:45 by facarval          #+#    #+#             */
/*   Updated: 2024/06/04 14:37:41 by facarval         ###   ########.fr       */
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
    this->line = cpy.line;
    this->stack = cpy.stack;
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
    std::list<double>::iterator it_stack = this->stack.end();
    it_stack--;
    double tmp = *it_stack;
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

bool Rpn::calculate()
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
                return true;
            }
            else
            {
                do_op(it);
            }
        }
        else
        {
            std::cerr << red << "Error" << reset << std::endl;
            return true;
        }
        it++;
        if (it == this->line.end())
            break;
        else if (isspace(*it) == false)
        {
            std::cerr << red << "Error" << reset << std::endl;
            return true;
        }
    }
    return false;
}

void Rpn::run(char *line)
{
    this->line = line;

    if (this->parsing_error() == true)
        return;

    if (this->calculate() == true)
        return;

    if (this->stack.size() != 1)
    {
        std::cerr << red << "Error" << reset << std::endl;
    }
    else
    {
        std::cout << this->stack.front() << std::endl;
    }
    return;
}