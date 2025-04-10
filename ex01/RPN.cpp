#include "RPN.hpp"

RPN::RPN(void) {}

RPN::RPN(const RPN &other) { (void)other; }

RPN::~RPN(void) {}

RPN	RPN::operator=(const RPN &other) { (void)other; return (*this); }

void	RPN::_parse_(std::string &line) {
	int			sign = 0;
	int			digit = 0;
	std::string	operators = "/*-+";

	(void)sign;
	(void)digit;
	for (size_t i = 0; line.length(); i++) {
		// if (i % 2 != 0)
		// 	std::cout	<< i << "-{" << line.at(i) << "} ";
		if (i != 0 && i % 2 != 0)
			if (line.at(i) != ' ') {
				// std::cout << "{" << line.at(i) << "} ";
				throw (std::runtime_error("Error"));
			}
	}
	if (line.length() < 3)
		throw (std::runtime_error("Error"));
	for (size_t i = 0; i < line.length(); i++) {
		if (std::isdigit(line.at(i))) {
			digit++;
			continue ;
		}
		if (operators.find(line.at(i)) != std::string::npos) {
			if (digit < 2)
				throw (std::runtime_error("Error"));
			sign++;
			continue ;
		}
	}
}

void	RPN::parse_fill_do(std::string &line) {
	int			count = 0;
	(void)count;
	std::string	operators = "/*-+ ";

	this->_parse_(line);
	// for (int i = (line.length() - 1); i >= 0; i--) {
	// 	count++;
	// 	if (operators.find(line.at(i)) != std::string::npos) {
	// 		if (line.at(i) != ' ') {
	// 			if (i < 2)
	// 				throw (std::runtime_error("Error"));
	// 			count++;
	// 			this->_stack.push(line.at(i));
	// 		}
	// 		continue ;
	// 	}
	// 	if (std::isdigit(line.at(i)))
	// 		this->_stack.push(line.at(i));
	// 	else
	// 		throw (std::runtime_error("Error"));
	// }
	// this->_do_();
	// for (;!this->_stack.empty();) {
	// 	std::cout	<< this->_stack.top() << '\n';
	// 	this->_stack.pop();
	// }
}

void	RPN::_do_(void) {
	// int		result;
	// char	n1, n2, sign;

	for (;!this->_stack.empty();) {
		std::cout	<< this->_stack.top() << '>';
		if (std::isdigit(this->_stack.top())) {
			this->_result.push(static_cast<unsigned int>(this->_stack.top()));
			this->_stack.pop();
		} else {
		}
	}
}