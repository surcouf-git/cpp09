#pragma once

#include <fstream>
#include <map>

class BitcoinExchange
{
	private:
		std::ifstream					_infile;
		std::map<std::string, float>	_csv;
		std::map<std::string, float>	_input;

		bool	isInt(const std::string &string);
		bool	isFloat(const std::string &string);
		bool	fill_input_map(void);
		void	parse_line(std::string current_line);

	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &other);
		~BitcoinExchange(void);

		BitcoinExchange	&operator=(const BitcoinExchange &other);

		void	handleInfile(std::string infile);
};