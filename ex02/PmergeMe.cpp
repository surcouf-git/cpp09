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
	this->_split_(vec1);
	this->_split_(vec2);
	this->_sort_back_(vec, vec1, vec2);
}

void	PmergeMe::_is_usable_(void) {

}

void	PmergeMe::_parse_(void) {
	// int		i = 1;
	// this->_is_usable_();
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

/* void	PmergeMe::_make_pairs_(std::vector<std::pair<int, int>> &vec_pair, std::list<std::pair<int, int>> &list_pair) {
	int	a = 0, b = 0;

	if (this->_vector.size() % 2 != 0) {
		this->_vector.push_back(-1);
	}
	for (size_t i = 0; i < this->_vector.size(); i += 2) {
		a = this->_vector[i];
		b = this->_vector[i + 1];
		if (a < b) {
			vec_pair.push_back(std::make_pair(a, b));
			list_pair.push_back(std::make_pair(a, b));
		} else if (b < a) {
			vec_pair.push_back(std::make_pair(b, a));
			list_pair.push_back(std::make_pair(b, a));
		}
	}
} */

void	PmergeMe::_vec_make_pairs_(std::vector<int> &vec_max, std::vector<int> &vec_min) {
	int	a = 0, b = 0;

	if (this->_vector.size() % 2 != 0) {
		this->_vector.push_back(-1);
	}
	for (size_t i = 0; i < this->_vector.size(); i += 2) {
		a = this->_vector[i];
		b = this->_vector[i + 1];
		if (a < b) {
			vec_max.push_back(b);
			vec_min.push_back(a);
		} else if (a > b) {
			vec_max.push_back(a);
			vec_min.push_back(b);
		}
	}
}

void	PmergeMe::_sort_(void) {
	int		min = 0, max = 0;
	std::vector<std::pair<int, int>>	vec_pair;
	std::list<std::pair<int, int>>		list_pair;
	std::vector<int>					vec_max, vec_min;
	std::list<int>						list_max, list_min;


	this->_vec_make_pairs_(vec_max, list_min);
	for (size_t i = 0; i < vec_pair.size(); i++) {
		min = vec_pair[i].first;
	}
	// for (size_t i = 0; i < vec_pair.size(); i++) {
	// 	std::cout << "vec_pair: ";
	// 	std::cout	<< vec_pair[i].first << " " << vec_pair[i].second << "\n";
	// }
	// std::cout	<< "\n\n";
	// std::list<std::pair<int, int>>::iterator it = list_pair.begin();
	// for (; it != list_pair.end(); ++it) {
	// 	std::cout << "list_pair: ";
	// 	std::cout << it->first << " " << it->second << std::endl;
	// }
	// this->_split_(this->_vector);
}


void	PmergeMe::_launch_(void) {
	this->_parse_();
	this->_sort_();
	try {
		// for (size_t p = 0; p < this->_vector.size(); p++) {
		// 	std::cout	<< this->_vector.at(p) << '\n';
		// }
	} catch (std::exception &e) {
		std::cout	<< e.what() << '\n';
	}
}