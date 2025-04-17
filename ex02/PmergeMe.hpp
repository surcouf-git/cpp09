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
		void				_sort_(void);
		void				_parse_(void);
		void				_recursive_(std::vector<int> &vec);
		void				_vec_make_pairs_(std::vector<int> &vec_max, std::vector<int> &vec_min);
		void				_sort_back_(std::vector<int> &vec, std::vector<int> &vec1, std::vector<int> &vec2);
		// void				_make_pairs_(std::vector<std::pair<int, int>> &vec_pair, std::list<std::pair<int, int>> &list_pair);

	public:
		PmergeMe(void);
		PmergeMe(char **argv);
		PmergeMe(const PmergeMe &other);
		~PmergeMe(void);
		PmergeMe	&operator=(const PmergeMe &other);

		void	_launch_(void);
};