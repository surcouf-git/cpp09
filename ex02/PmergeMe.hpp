#pragma once

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <cctype>
#include <list>
#include <deque>

class	PmergeMe
{
	private:
		std::deque<int>		_deque;
		std::vector<int>	_vector;
		char				**_argv;
		void				_parse_(void);

	public:
		PmergeMe(void);
		PmergeMe(char **argv);
		PmergeMe(const PmergeMe &other);
		~PmergeMe(void);
		PmergeMe	&operator=(const PmergeMe &other);

		void	_launch_(void);
};