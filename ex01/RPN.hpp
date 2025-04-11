#pragma once

#include <iostream>
#include <stack>

#include <iostream>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <iomanip>

class RPN
{
	private:
		std::stack<int>	_stack;
		std::stack<std::string>	_stringStack;
		std::stack<int>			_result;

		void	_do_(void);
		void	_swap_(const char c);
		void	_parse_(std::string &line);

	public:
		RPN(void);
		RPN(const RPN &other);
		~RPN(void);

		RPN		operator=(const RPN &other);

		void	parse_fill_do(std::string &line);
};