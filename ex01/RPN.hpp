#pragma once

#include <iostream>
#include <stack>

class RPN
{
	private:
		std::stack<char>				_stack;
		std::stack<unsigned int>		_result;

		void	_do(void);

	public:
		RPN(void);
		RPN(const RPN &other);
		~RPN(void);

		RPN	operator=(const RPN &other);

		void	parse_fill_do(std::string line);
};