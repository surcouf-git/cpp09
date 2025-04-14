#include "PmergeMe.hpp"

#include <algorithm>

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(char **argv) : _argv(argv) {}

PmergeMe::PmergeMe(const PmergeMe &other) { (void)other; }

PmergeMe::~PmergeMe(void) {}

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

void	PmergeMe::_split_(std::vector<int> &vec) {
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
	_split_(vec1);
	_split_(vec2);
	this->_sort_back_(vec, vec1, vec2);
}

void	PmergeMe::_is_usable_(void) {
	int			i = 0, o = 0;
	char		**argv = this->_argv;

	while (argv && argv[o]) {
		while (argv[o][i]) {
			if (argv[o][i] < '0' || argv[o][i] > '9' || argv[o][i] != '-') {
				throw (std::runtime_error("Error"));
			}
		}
	}
}

void	PmergeMe::_parse_(void) {
	int		i = 1;

	this->_is_usable_();
}

void	PmergeMe::_sort_(void) {
	this->_parse_();
	this->_split_(this->_vector);
	for (size_t i = 0; i < this->_vector.size(); i++) {
		std::cout	<< this->_vector[i] << '\n';
	}
}

int	main(int argc, char **argv)
{
	if (argc < 2) {
		std::cerr	<< "Error\n";
		return (1);
	}
	PmergeMe	FJohnson(argv);
	try {
		FJohnson._sort_();
	} catch (std::exception &e) {
		std::cout	<< e.what() << '\n';
	}
	return (0);
}