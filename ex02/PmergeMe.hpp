#pragma once

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <cctype>
#include <list>

class PmergeMe
{
	private:
		std::list<int>		_list;
		std::vector<int>	_vector;
		char				**_argv;
		void				_parse_(void);
		void				_is_usable_(void);
		void				_split_(std::vector<int> &vec);
		void				_sort_back_(std::vector<int> &vec, std::vector<int> &vec1, std::vector<int> &vec2);

	public:
		PmergeMe(void);
		PmergeMe(char **argv);
		PmergeMe(const PmergeMe &other);
		~PmergeMe(void);
		PmergeMe	&operator=(const PmergeMe &other);

		void	_sort_(void);
};