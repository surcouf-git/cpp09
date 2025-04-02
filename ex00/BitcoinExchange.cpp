#include "BitcoinExchange.hpp"
#include <iostream>

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::~BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _csv(other._csv){}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other) {
		this->_csv = other._csv;
		this->_input = other._input;
	}
	return (*this);
}

bool	BitcoinExchange::isInt(const std::string &string) {
	size_t	i = 0;

	if (string.empty())
		return false;
	if (string[0] == '+' || string[0] == '-')
		i = 1;
	if (i == string.length())
		return false;
	for (; i < string.length(); i++) {
		if (!std::isdigit(string[i]))
			return false;
	}
	return true;
}

bool	BitcoinExchange::isFloat(const std::string &string) {
	size_t		i = 0;
	bool		hasDecimal = false;
	std::string	tmp = string.substr(0, string.length() - 1);

	if (string.empty())
		return false;
	if (string == "nanf" || string == "+inff" || string == "-inff")
		return true;
	if (string[string.length() - 1] != 'f')
		return false;
	if (tmp[0] == '+' || tmp[0] == '-')
		i = 1;
	if (i == tmp.length())
		return false;
	for (; i < tmp.length(); i++) {
		if (tmp[i] == '.' && !hasDecimal) {
			hasDecimal = true;
		} else if (!isdigit(tmp[i])) {
			return (false);
		}
	}
	return (hasDecimal);
}

void	BitcoinExchange::parse_line(std::string current_line) {
	std::string		date;
	// float			multiplier;
	size_t			pipe_pos;

	pipe_pos = current_line.find('|');
	if (pipe_pos == std::string::npos) {
		this->_input.insert(std::make_pair("Error: bad input => " + current_line, -1.0f));
		// return ;
	}
	date = current_line.substr(current_line.find_first_not_of(" "), current_line.find_last_not_of(" "));
	if (date.length() != 10) {
		this->_input.insert(std::make_pair("Error: bad input => " + date, -1.0f));
		// return ;
	}
	std::cout	<< current_line.find_first_not_of(" ") << current_line.find_last_not_of(' ') << "\n\n";
	std::cout	<< this->_input.begin()->first << "\n{" << date << "}\n";
}

bool	BitcoinExchange::fill_input_map(void) {
	std::string	current_line, line_saver;

	if (!std::getline(this->_infile, current_line))
		return (false);
	else if (current_line.empty() || (current_line != "date | value"))
		return (false);
	while (std::getline(this->_infile, current_line, '\n')) {
		try {
			this->parse_line(current_line);
		} catch (std::exception &e) {
			std::cerr	<< e.what() << '\n';
		}
	}
	return (true);
}

void	BitcoinExchange::handleInfile(std::string infile) {
	this->_infile.open(infile);
	if (!this->_infile)
		throw (std::runtime_error("Error: cannot open file: " + infile));
	if (!this->fill_input_map())
		throw (std::runtime_error("Error: invalid file content"));
}
