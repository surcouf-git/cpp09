#pragma once

#include <fstream>
#include <map>

typedef struct	s_data {
	std::string	str;
	float		multiplier;
}	t_data;

class BitcoinExchange
{
	private:
		std::map<std::string, float>	_csv;
		std::map<int, t_data*>			_input;
		std::ifstream					_infile;
		std::ifstream					_infile_csv;

		void			fill_input_map(void);
		void			get_csv_values(void);
		void			find_and_display(void);
		bool			isInt(const std::string &string);
		bool			isFloat(const std::string &string);
		void			delete_whitespaces(std::string &string);
		void			check_format(std::string &date, const int &count);
		static t_data	*new_data(const std::string &str, float multiplier);
		void			parse_line(std::string current_line, const int &count);
		float			extract_mutliplier(std::string &s_multiplier, const int &count);
		size_t			find_pipe(std::string &date, std::string &current_line, const int &count);

	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &other);
		~BitcoinExchange(void);

		BitcoinExchange	&operator=(const BitcoinExchange &other);

		void	handleInfile(std::string infile);
};