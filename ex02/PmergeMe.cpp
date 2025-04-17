#include "PmergeMe.hpp"

#include <algorithm>

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(char **argv) : _argv(argv) {}

PmergeMe::PmergeMe(const PmergeMe &other) { (void)other; }

PmergeMe::~PmergeMe(void) {}

PmergeMe	&PmergeMe::operator=(const PmergeMe &other) { (void)other; return (*this); }

void	PmergeMe::_sort_back_(std::vector<int> &vec, std::vector<int> &vec1, std::vector<int> &vec2) {
	size_t	one = 0, two = 0, three = 0, vec1_size = vec1.size(), vec2_size = vec2.size();

	while (one < vec1_size && two < vec2_size) {
		if (vec1[one] < vec2[two])
			vec[three++] = vec1[one++];
		else if (vec1[one] > vec2[two])
			vec[three++] = vec2[two++];
	}
	while (one < vec1_size)
		vec[three++] = vec1[one++];
	while (two < vec2_size)
		vec[three++] = vec2[two++];
}

void	PmergeMe::_recursive_(std::vector<int> &vec) {
	if (vec.size() <= 1)
		return ;
	size_t				vec_size = vec.size();
	std::vector<int>	vec1, vec2;

	for (size_t i = 0; i < vec_size; i++) {
		if (i < (vec_size / 2))
			vec1.push_back(vec.at(i));
		else
			vec2.push_back(vec.at(i));
	}
	this->_recursive_(vec1);
	this->_recursive_(vec2);
	this->_sort_back_(vec, vec1, vec2);
}

void	PmergeMe::_parse_(void) {
	std::string			line;
	std::stringstream	stream;
	char				**argv = this->_argv;
	int					i = 0, o = 1;

	while (argv && argv[o]) {
		while (argv[o][i]) {
			if (argv[o][i] < 48 || argv[o][i] > 57)
				throw (std::runtime_error("Error"));
			i++;
		}
		if (std::atol(argv[o]) >= 2147483647)
			throw (std::runtime_error("Error"));
		this->_vector.push_back(std::atoi(argv[o]));
		this->_list.push_back(std::atoi(argv[o]));
		o++;
	}
	if (o < 2)
		throw (std::runtime_error("Error"));
}

void	swap_range(std::vector<int> &vector, size_t end, size_t pair_size, size_t start) {
	std::vector<int>	swapper;

	while (start < (end + 1)) {
		swapper.push_back(vector[start]);
		vector[start] = vector[start + pair_size];
		start++;
	}

	for (size_t i = (end + 1), range = 0; range < pair_size; i++, range++) {
		vector.at(i) = swapper.at(range);
	}
}

void	PmergeMe::_vec_make_pairs_(std::vector<int> &vector, size_t pair_size) {
	if (pair_size > (vector.size() / 2)) {
		return ;
	}
	int		number;
	size_t	end = (pair_size - 1), start = 0;

	while ((end + pair_size) < vector.size()) {
		if (vector[end] > vector[end + pair_size])
			swap_range(vector, end, pair_size, ((end + 1) - pair_size));
		end += pair_size;
	}
	this->_vec_make_pairs_(vector, pair_size * 2);
}

void	PmergeMe::_sort_(void) {
	std::vector<int>	vec_max, vec_min;
	this->_vec_make_pairs_(this->_vector, 2);
	for (size_t i = 0; i < this->_vector.size(); i++)
		std::cout	<< this->_vector[i];
}


void	PmergeMe::_launch_(void) {
	this->_parse_();
	this->_sort_();
}