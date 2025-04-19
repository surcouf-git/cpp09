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
		void _sort_back_(std::vector<int> &vec, size_t pair_size);
		void salope(int actual, int range, int i, size_t &start, size_t pair_size);
		void				_vec_make_pairs_(std::vector<int> &vector, size_t pair_size);
		// void				_make_pairs_(std::vector<std::pair<int, int>> &vec_pair, std::list<std::pair<int, int>> &list_pair);

	public:
		PmergeMe(void);
		PmergeMe(char **argv);
		PmergeMe(const PmergeMe &other);
		~PmergeMe(void);
		PmergeMe	&operator=(const PmergeMe &other);

		void	_launch_(void);
};