#include "RPN.hpp"

RPN::RPN(void) {}

RPN::RPN(const RPN &other) { (void)other; }

RPN::~RPN(void) {}

RPN	RPN::operator=(const RPN &other) { (void)other; return (*this); }

void	RPN::parse_fill_do(std::string line) {
	std::string	operators = "/*-+ ";
	for (int i = (line.length() - 1); i >= 0; i--) {
		if (operators.find(line.at(i)) != std::string::npos) {
			if (line.at(i) != ' ')
				this->_stack.push(line.at(i));
			continue ;
		}
		if (std::isdigit(line.at(i)))
			this->_stack.push(line.at(i));
		else
			throw (std::runtime_error("Error"));
	}
	this->_do();
	for (;!this->_stack.empty();) {
		std::cout	<< this->_stack.top() << '\n';
		this->_stack.pop();
	}
}

void	RPN::_do(void) {
	int		result;
	char	n1, n2, sign;

	for (;!this->_stack.empty();) {
		std::cout	<< this->_stack.top() << '>';
		if (std::isdigit(this->_stack.top())) {
			this->_result.push(static_cast<unsigned int>(this->_stack.top()));
			this->_stack.pop();
		} else {
			n2 = static_cast<unsigned int>(this->_result.top());
			this->_result.pop();
			n1 = static_cast<unsigned int>(this->_result.top());
			this->_result.pop();
			sign = this->_stack.top();
			if (sign == '/')
				result = n1 / n2;
			else if (sign == '*')
				result = n1 * n2;
			else if (sign == '-')
				result = n1 - n2;
			else if (sign == '+')
				result = n1 + n2;
			this->_result.push(result);
		}
	}
}