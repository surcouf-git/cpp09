#include "BitcoinExchange.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <limits>

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::~BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _csv(other._csv), _input(other._input) {}

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
	return (data);
}

void	BitcoinExchange::find_and_display(void) {
	float										result;
	std::map<std::string, float>::iterator		_csv_it = this->_csv.begin();
	std::map<int, t_data*>::iterator			_input_it = this->_input.begin();

	for (; _input_it != this->_input.end(); ++_input_it) {
		if (_input_it->second->str.substr(0, 5) != "Error") {
			for (_csv_it = this->_csv.begin(); _csv_it != this->_csv.end(); ++_csv_it) {
				if (_input_it->second->str <= _csv_it->first) {
					if (_input_it->second->str != _csv_it->first)
						--_csv_it;
					result = (_input_it->second->multiplier * _csv_it->second);
					std::cout	<< _input_it->second->str << " => " << result << '\n';
					break ;
				}
			}
		} else {
			std::cout	<< _input_it->second->str << '\n';
		}
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
}

float	BitcoinExchange::extract_mutliplier(std::string &s_multiplier, const int &count) {
	std::string	msg;
	double	multiplier;

	if (!isInt(s_multiplier) && !isFloat(s_multiplier)) {
		this->_input.insert(std::make_pair(count, new_data("Error: bad input => " + s_multiplier, -1.0f)));
		throw (-1);
	}
	multiplier = std::atof(s_multiplier.c_str());
	if (multiplier < 0 || multiplier > std::numeric_limits<int>::max() || multiplier > 1000) {
		msg = (multiplier < 0) ? "Error: not a positive number." : "Error: too large a number.";
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
	size_t	i = 0;
	bool	hasDecimal = false;

	if (string.empty())
		return false;
	if (string == "nan" || string == "+inf" || string == "-inf")
		return true;
	if (string[0] == '+' || string[0] == '-')
		i = 1;
	if (i == string.length())
		return false;
	for (; i < string.length(); i++) {
		if (string[i] == '.' && !hasDecimal) {
			hasDecimal = true;
		} else if (!isdigit(string[i])) {
			return false;
		}
	}
	return (hasDecimal);
}

size_t	BitcoinExchange::find_pipe(std::string	&date, std::string &current_line, const int &count) {
	size_t		pipe_pos;

	pipe_pos = current_line.find('|');
	if (pipe_pos == std::string::npos) {
		this->_input.insert(std::make_pair(count, new_data("Error: bad input => " + current_line, -1.0f)));
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
		this->_input.insert(std::make_pair(-1.0f, new_data("Error: bad input => " + string, -1.0f))); // EXPRESSION MANQUANTE
		throw (-1);
	}
}

void	BitcoinExchange::check_format(std::string &date, const int &count) {
	int					i = 0;
	int					value;
	std::stringstream	stream(date);
	std::string			tab[3], line;

	if (date.at(4) != '-' || date.at(7) != '-') {
		this->_input.insert(std::make_pair(count, new_data("Error: bad input => " + date, -1.0f)));
		throw (-1);
	}
	if (date > "2022-03-25") {
		this->_input.insert(std::make_pair(count, new_data("Error: bad input => " + date, -1.0f)));
		throw (-1);
	}
	while (std::getline(stream, line, '-')) {
		tab[i] = line;
		for (size_t o = 0; o < line.length(); o++) {
			if (line.at(o) == '.') {
				o++;
				continue ;
			}
			if (!std::isdigit(line.at(o))) {
				this->_input.insert(std::make_pair(count, new_data("Error: bad input => " + date, -1.0f)));
				throw (-1);
			}
		}
		value = std::atoi(line.c_str());
		if (i == 0 && (line.length() != 4 || value > 2022 || value < 0)) {
			this->_input.insert(std::make_pair(count, new_data("Error: bad input => " + date, -1.0f)));
			throw (-1);
		}
		if (i == 1 && (line.length() != 2 || value > 12 || value < 0)) {
			this->_input.insert(std::make_pair(count, new_data("Error: bad input => " + date, -1.0f)));
			throw (-1);
		}
		if (i == 2 && (line.length() != 2 || value > 31 || value < 0)) {
			this->_input.insert(std::make_pair(count, new_data("Error: bad input => " + date, -1.0f)));
			throw (-1);
		}
		i++;
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
		this->_input.insert(std::make_pair(count, new_data("Error: bad input => " + date, -1.0f)));
		throw (-1);
	}
	this->check_format(date, count);
	//extraire la valeur
	s_multiplier = current_line.substr(pipe_pos, current_line.find_last_not_of(" \t\n\r\f\v"));
	this->delete_whitespaces(s_multiplier);
	multiplier = this->extract_mutliplier(s_multiplier, count);
	//remplir map
	this->_input.insert(std::make_pair(count, new_data(date, multiplier)));
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
	// for (std::map<int, t_data*>::iterator it = this->_input.begin(); it != this->_input.end(); ++it) {
	// 	std::cout	 << it->second->str << '\n';
	// }
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