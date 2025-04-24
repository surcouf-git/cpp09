#pragma once

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <complex>
#include <valarray>
#include <cctype>
#include <vector>
#include <ctime>
#include <deque>
#include <list>

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