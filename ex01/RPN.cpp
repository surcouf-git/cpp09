#include "RPN.hpp"

RPN::RPN(void) {}

RPN::RPN(const RPN &other) { (void)other; }

RPN::~RPN(void) {}

RPN	RPN::operator=(const RPN &other) { (void)other; return (*this); }

void	RPN::_parse_(std::string &line) {
	std::string			nwline;
	std::stringstream	stream(line);
	std::string			operators = "/*-+";
	int					operat = 0, number = 0, start = 0;

	while (std::getline(stream, nwline, ' ')) {
		start++;
		operat = 0, number = 0;
		for (size_t i = 0; i < nwline.length(); i++) {
			if (operators.find(nwline.at(i)) != std::string::npos)
				operat++;
			else if (std::isdigit(nwline.at(i)))
				number++;
			else
				throw (std::runtime_error("Error"));
			if (number != 0 && operat > 1)
				throw (std::runtime_error("Error"));
		}
		if (number == 0 && operat != 0 && start < 3) 
			throw (std::runtime_error("Error"));
		if (number > 1)
			throw (std::runtime_error("Error"));
		this->_stringStack.push(nwline);
	}
	if (this->_stringStack.size() < 3)
		throw (std::runtime_error("Error"));
}

void	RPN::_fill_(void) {
	for (;!this->_stringStack.empty();) {
		this->_revStringStack.push(this->_stringStack.top());
		this->_stringStack.pop();
	}
}

int		RPN::_calculate_(int n1, int n2, char operat) {
	if (operat == '/')
		return (n1 / n2);
	else if (operat == '*')
		return (n1 * n2);
	else if (operat == '-')
		return (n1 - n2);
	else if (operat == '+')
		return (n1 + n2);
	return (-2147483648);
}

void	RPN::_do_(void) {
	std::string	node;
	std::string	operators = "/*-+";
	int			digit = 0, operat = 0, n1 = 0, n2 = 0;

	for (;!this->_revStringStack.empty();) {
		digit = 0, operat = 0;
		node = this->_revStringStack.top();
		for (size_t i = 0; i < node.length(); i++) {
			if (operators.find(node.at(i)) != std::string::npos)
				operat++;
			if (std::isdigit(node.at(i)))
				digit++;
		}
		if (!digit && operat) {
			if (this->_resultStack.size() < 2)
				throw (std::runtime_error("Error"));
			else {
				for (size_t i = 0; i < node.length(); i++) {
					if (this->_resultStack.size() < 2)
						throw (std::runtime_error("Error"));
					n2 = this->_resultStack.top();
					this->_resultStack.pop();
					n1 = this->_resultStack.top();
					this->_resultStack.pop();
					this->_resultStack.push(this->_calculate_(n1, n2, node.at(i)));
				}
				this->_revStringStack.pop();
				continue ;
			}
		}
		this->_resultStack.push(std::atoi(this->_revStringStack.top().c_str()));
		this->_revStringStack.pop();
	}
}

void	RPN::parse_fill_do(std::string &line) {
	this->_parse_(line);
	this->_fill_();
	this->_do_();
	
	if (this->_resultStack.size() > 1)
		throw (std::runtime_error("Error"));
	std::cout	<< this->_resultStack.top() << '\n';
	this->_resultStack.pop();
}