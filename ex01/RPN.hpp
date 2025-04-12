#pragma once

#include <iostream>
#include <stack>
#include <sstream>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <iomanip>

class RPN
{
	private:
		std::stack<int>			_resultStack;
		std::stack<std::string>	_stringStack;
		std::stack<std::string>	_revStringStack;

		void	_do_(void);
		void	_fill_(void);
		void	_swap_(const char c);
		void	_parse_(std::string &line);
		int		_calculate_(int n1, int n2, char operat);

	public:
		RPN(void);
		RPN(const RPN &other);
		~RPN(void);

		RPN		operator=(const RPN &other);

		void	parse_fill_do(std::string &line);
};