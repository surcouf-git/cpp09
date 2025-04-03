#include "BitcoinExchange.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <limits>

#define	line_error 

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

//PARSING

t_data	*BitcoinExchange::new_data(const std::string &str, float multiplier) {
	t_data *data = new t_data;
	data->str = str;
	data->multiplier = multiplier;
	data->value = 0;
	return (data);
}

void	BitcoinExchange::find_and_display(void) {
	std::map<int, t_data*>::iterator	_input_it = this->_input.begin();

	for (; _input_it != this->_input.end(); ++_input_it) {
		if (_input_it->second->str.substr(0, 5) == "Error")
			std::cout	<< "found: ";
		std::cout	<< _input_it->second->str << '\n';
	}
}

void	BitcoinExchange::get_csv_values(void) {
	std::string	line;
	float		value;

	std::getline(this->_infile_csv, line);
	if (line != "date,exchange_rate")
		throw (std::runtime_error("Invalid head in data.csv"));
	while (std::getline(this->_infile_csv, line)) {
		value = std::strtof(line.substr(line.find(",") + 1).c_str(), NULL);
		this->_csv.insert(std::make_pair(line.substr(0, line.find(",")), value));
	}
	// for (std::map<std::string, float>::iterator it = this->_csv.begin(); it != this->_csv.end(); ++it) {
	// }
}

float	BitcoinExchange::extract_mutliplier(std::string &s_multiplier, const int &count) {
	std::string	msg;
	double	multiplier;

	if (!isInt(s_multiplier) && !isFloat(s_multiplier)) {
		this->_input.insert(std::make_pair(count, new_data("Error: bad input => " + s_multiplier + " -line:", -1.0f)));
		throw (-1);
	}
	multiplier = std::atof(s_multiplier.c_str());
	if (multiplier < 0 || multiplier > std::numeric_limits<int>::max()) {
		(multiplier < 0) ? msg = "Error: not a positive number." : "Error: too large a number.";
		this->_input.insert(std::make_pair(count, new_data(msg, -1.0f)));
		throw (-1);
	}
	return (multiplier);
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
	return (true);
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

size_t	BitcoinExchange::find_pipe(std::string	&date, std::string &current_line, const int &count) {
	size_t		pipe_pos;

	pipe_pos = current_line.find('|');
	if (pipe_pos == std::string::npos) {
		this->_input.insert(std::make_pair(count, new_data("Error: bad input => " + current_line + " -line:", -1.0f)));
		throw (-1);
	}
	date = current_line.substr(current_line.find_first_not_of(" "), pipe_pos);
	return (pipe_pos);
}

void	BitcoinExchange::delete_whitespaces(std::string &string) {
	size_t	start = string.find_first_not_of(" \t\n\r\f\v|");
	size_t	end = string.find_last_not_of(" \t\n\r\f\v|");

	if (start != std::string::npos) {
		string = string.substr(start, end - start + 1);
	} else {
		this->_input.insert(std::make_pair(-1.0f, new_data("Error: bad input => " + string + " -line:", -1.0f))); // EXPRESSION MANQUANTE
		throw (-1);
	}
}

void	BitcoinExchange::parse_line(std::string current_line, const int &count) {
	std::string		date, s_multiplier;
	float			multiplier;
	size_t			pipe_pos;

	//extraire la date
	pipe_pos = this->find_pipe(date, current_line, count);
	this->delete_whitespaces(date);
	if (date.length() != 10) {
		this->_input.insert(std::make_pair(count, new_data("Error: bad input => " + date + " -line:", -1.0f)));
		throw (-1);
	}
	//extraire la valeur
	s_multiplier = current_line.substr(pipe_pos, current_line.find_last_not_of(" \t\n\r\f\v"));
	this->delete_whitespaces(s_multiplier);
	multiplier = this->extract_mutliplier(s_multiplier, count);
	this->_input.insert(std::make_pair(count, new_data(date + " => " + s_multiplier, multiplier)));
}

void	BitcoinExchange::fill_input_map(void) {
	int			count = 1;
	std::string	current_line, line_saver;

	if (!std::getline(this->_infile, current_line))
		throw (std::runtime_error("Error: empty file detected"));
	else if (current_line.empty() || (current_line != "date | value"))
		throw (std::runtime_error("Error: \'date | value\': head missing"));
	while (std::getline(this->_infile, current_line)) {
		count++;
		try {
			this->parse_line(current_line, count);
		} catch (int) {}
	}
/* 	for (std::map<float, t_data*>::iterator it = this->_input.begin(); it != this->_input.end(); ++it) {
		std::cout	 << it->second->str << " " << it->first << '\n';
	} */
}

void	BitcoinExchange::handleInfile(std::string infile) {
	this->_infile.open(infile.c_str());
	this->_infile_csv.open("data.csv");
	if (!this->_infile)
		throw (std::runtime_error("Error: cannot open file: " + infile));
	if (!this->_infile_csv)
		throw (std::runtime_error("Error: cannot open csv file"));
	this->get_csv_values();
	this->fill_input_map();
	this->find_and_display();
}