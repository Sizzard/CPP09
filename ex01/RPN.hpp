/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:06:32 by facarval          #+#    #+#             */
/*   Updated: 2024/06/04 14:27:39 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <list>

const std::string red("\033[1;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string blue("\033[1;34m");
const std::string cyan("\033[1;36m");
const std::string magenta("\033[1;35m");
const std::string reset("\033[0m");

class Rpn
{
private:
    std::string line;
    std::list<double> stack;

    bool parsing_error();
    bool calculate();
    void do_op(std::string::iterator it);

public:
    Rpn();
    Rpn(Rpn const &to_cpy);
    Rpn &operator=(Rpn const &cpy);
    ~Rpn();

    void run(char *line);
};