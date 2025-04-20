#include "PmergeMe.hpp"

#include <algorithm>

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(char **argv) : _argv(argv) {}

PmergeMe::PmergeMe(const PmergeMe &other) { (void)other; }

PmergeMe::~PmergeMe(void) {}

PmergeMe	&PmergeMe::operator=(const PmergeMe &other) { (void)other; return (*this); }

void	PmergeMe::_parse_(void) {
	std::string			line;
	std::stringstream	stream;
	char				**argv = this->_argv;
	int					i = 0, o = 1;

	while (argv && argv[o]) {
		i = 0;
		while (argv[o][i]) {
			if (argv[o][i] < 48 || argv[o][i] > 57) {
				std::cout	<< argv[i] << '\n';
				throw (std::runtime_error("Error")); }
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

int	count = 0;

template <typename C>
size_t	binary_search(C &contenair, size_t pair_size, int value) {
	size_t	index = (pair_size - 1), odd = 1;

	while (index + pair_size <= contenair.size()) {
		index += pair_size;
		odd++;
	}
	if (odd % 2 != 0)
		index -= pair_size;
	index = index / 2;
	if (count == 2) { std::cout	<< value << ' ' << pair_size << '\n'; }
	while (value > contenair.at(index)) {
		if ((index + pair_size) <= contenair.size() && value < contenair.at(index + pair_size))
			return (index);
		else if ((index + pair_size) >= contenair.size())
			return (index + pair_size);
		index += pair_size;
	} 
	index++;
	while (value < contenair.at(index)) {
		if ((index - pair_size) > 0 && value > contenair.at(index - pair_size))
			return (index - pair_size);
		else if ((index - pair_size) <= 0)
			return (index - pair_size);
		else
			index -= pair_size;
	}
	return (0);
}

int	jacobsthal_generator(int j_n, int n) { return (2 * j_n + static_cast<int>(pow(-1, n))); }

std::vector<int>	_jacobsthal_insert_(size_t &start, size_t &pair_size, std::vector<int> &b, std::vector<int> &vector, std::vector<int> &main, std::vector<int> &pend) {
	std::vector<int>	temp_vec;
	size_t				index = 0;
	int					j_n = 1, n = 4, i = 0, actual, range;

	while (!b.empty()) {
		actual = jacobsthal_generator(j_n, n);
		range = actual - j_n;
		j_n = actual;
		actual -= 1;
		if (count == 2)
			std::cout	<< j_n  << ' ' << b.size() << "<-\n";
		while (range > 0) {
			start = actual * pair_size - pair_size;
			index = binary_search(main, pair_size, pend.at(actual * pair_size - 1));
			index++;
			for (size_t i = 0; i < pair_size; i++, index++, start++) {
				main.insert(main.begin() + index, pend.at(start));
			}
			b.pop_back();
			actual--, range--;
		}
		n++;
	}
	return (main);
}

void	PmergeMe::_sort_back_(std::vector<int> &vector, size_t pair_size) {
	std::vector<int>::iterator	it;
	std::vector<int>			pend, main, excludes, b;
	size_t						start = 0, pair = 0, both_size = 0;
	int							b_count = 2, i = 0;

	while (start < vector.size()) {
		if (pair == 0 || (pair % 2 != 0)) {
			for (size_t o = (start); o < start; o++, i++)
				try { main.push_back(vector.at(o)); } catch (...) {std::cout << "izi\n"; }
		} else if (pair % 2 == 0) {
			for (size_t o = (start); o < start; o++, i++)
				try { pend.push_back(vector.at(o)); } catch (...) {std::cout << "aza: " << o << "\n"; }
			b.push_back(b_count++);
		}
		start += pair_size;
		pair++;
	}
	if (count == 2)
		std::cout	<< "[" << vector.size() << "] {" << start << "}\n";
	for (; i < vector.size(); i++) {
		main.push_back(vector.at(i));
	}
	if (count == 2) {
		// std::cout	<< "{" << start << "}\n";
		std::cout	<< "vector:\n";
		for (size_t i = 0; i < vector.size(); i++) {
			std::cout	<< vector.at(i) << ' ';
		}
		std::cout	<< '\n';
		std::cout	<< "main:\n";
		for (size_t i = 0; i < main.size(); i++) {
			std::cout	<< main.at(i) << ' ';
		}
		std::cout	<< std::endl;
		std::cout	<< "pend:\n";
		for (size_t i = 0; i < pend.size(); i++) {
			std::cout	<< pend.at(i) << ' ';
		}
		std::cout	<< '\n';
		// if (count == 2)
		exit(0);
	}
	vector = _jacobsthal_insert_(start, pair_size, b, vector, main, pend);
	count++;
}

void	PmergeMe::_vec_make_pairs_(std::vector<int> &vector, size_t pair_size) {
	if (pair_size > (vector.size() / 2)) {
		return ;
	}
	size_t	end = (pair_size - 1);

	while ((end + pair_size) < vector.size()) {
		if (vector[end] > vector[end + pair_size])
			swap_range(vector, end, pair_size, ((end + 1) - pair_size));
		end += (pair_size * 2);
	}
	this->_vec_make_pairs_(vector, pair_size * 2);
	//Apres le dernier appel recursif
	this->_sort_back_(vector, pair_size);
}

void	PmergeMe::_sort_(void) {
	for (size_t i = 0; (i + 1) < this->_vector.size(); i += 2) {
		if (this->_vector[i] > this->_vector[i + 1])
			std::swap(this->_vector[i], this->_vector[i + 1]);
	}
	this->_vec_make_pairs_(this->_vector, 1);
}

void	PmergeMe::_launch_(void) {
	this->_parse_();
	this->_sort_();
	// for (size_t i = 0; i < this->_vector.size(); i++)
	// 	std::cout	<< this->_vector[i] << " ";
}