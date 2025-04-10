#include "RPN.hpp"

RPN::RPN(void) {}

RPN::RPN(const RPN &other) { (void)other; }

RPN::~RPN(void) {}

RPN	RPN::operator=(const RPN &other) { (void)other; return (*this); }

void	RPN::_parse_(std::string &line) {
	int			sign = 0;
	int			digit = 0;
	std::string	operators = "/*-+";

	if (line.length() < 3)
		throw (std::runtime_error("Error"));
	for (size_t i = 0; i < line.length(); i++) {
		if (i != 0 && i % 2 != 0)
			if (line.at(i) != ' ')
				throw (std::runtime_error("Error"));
	}
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
	int		count = 0;
	(void)count;
	std::string	operators = "/*-+ ";

	this->_parse_(line);
	// std::cout << chars << '\n';
	for (int i = (line.length() - 1); i >= 0; i--) {
		count++;
		if (operators.find(line.at(i)) != std::string::npos) {
			if (line.at(i) != ' ') {
				if (i < 2)
					throw (std::runtime_error("Error"));
				count++;
				this->_stack.push(chars);
			}
			continue ;
		}
		if (std::isdigit(line.at(i)))
			this->_stack.push(chars);
		else
			throw (std::runtime_error("Error"));
	}
	this->_do_();
	// for (;!this->_stack.empty();) {
	// 	std::cout	<< this->_stack.top() << "";
	// 	this->_stack.pop();
	// }
}

void	RPN::_swap_(const char c) {
	int	n1, n2 = 0;

	n1 = this->_result.top();
	std::cout	<< ">" << this->_result.top() << "<\n";
	this->_result.pop();
	std::cout	<< ">" << this->_result.top() << "<\n";
	n2 = this->_result.top();
	this->_result.pop();
	std::cout	<< ">" << n1 << ' ' << n2 << "<\n";
	if (c == '/')
		this->_result.push(n1 / n2);
	else if (c == '*')
		this->_result.push(n1 * n2);
	this->_stack.pop();
}

void	RPN::_do_(void) {

	std::cout	<< static_cast<int>(std::atol(this->_stack.top())) << '\n';
	this->_stack.pop();
	// std::string	test(&this->_stack.top());
	std::cout << ">" << this->_stack.top() << '\n';
	std::cout	<< std::atol(this->_stack.top()) << '\n';
	this->_stack.pop();
	std::cout	<< &this->_stack.top() << '\n';
	exit (0);
	for (;!this->_stack.empty();) {
		if (this->_stack.top()[0] == '/')
			this->_swap_('/');
		else if (this->_stack.top()[0] == '*')
			this->_swap_('*');
		else {
			this->_result.push(static_cast<int>(std::atol(this->_stack.top())));
			this->_stack.pop();
		}
	}
	for (;!this->_result.empty();) {
		std::cout	<< this->_result.top() << " ";
		this->_result.pop();
	}
}