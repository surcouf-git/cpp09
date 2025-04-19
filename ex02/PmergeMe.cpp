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

int	prochain_jacobsthal_efficace(int j_n, int n) { return (2 * j_n + pow(-1, n)); }

int	count = 0;

std::vector<int>	_jacobsthal_insert_(size_t &start, size_t &pair_size, std::vector<int> &b, std::vector<int> &vector, std::vector<int> &main, std::vector<int> &pend) {
	std::vector<int>	temp_vec;
	size_t				index = 0;
	int					j_n = 1, n = 4, i = 0, actual, range;

	if (count == 1 || count == 2) {
		while (!b.empty()) {
			actual = prochain_jacobsthal_efficace(j_n, n); // MODIFIER LE NOM
			range = actual - j_n;
			j_n = actual;
			actual -= 1;
			while (range > 0) {
				start = actual * pair_size - pair_size;
				std::cout	<< count << ": ";
				for (int i = 0; i < (int)pend.size(); i++) {
					std::cout	<< pend.at(i) << ' ';
				}
				std::cout	<< '\n';
				index = binary_search(main, pair_size, pend.at(actual * pair_size - 1));
				index++;
				for (size_t i = 0; i < pair_size; i++, index++, start++) {
					main.insert(main.begin() + index, pend.at(start));
				}
				b.pop_back();
				actual--, range--, n++;
			}
		}
		vector = main;
		if (count == 2) {
			for (size_t i = 0; i < main.size(); i++)
				std::cout	<< main[i] << " ";
			exit (0);
		}
	}
	return (main);
}

void	PmergeMe::_sort_back_(std::vector<int> &vector, size_t pair_size) {
	std::vector<int>::iterator	it;
	std::vector<int>			pend, main, b;
	size_t						start = pair_size, pair = 0;
	int							b_count = 2, i = 0;

	while (start < vector.size()) {
		if (pair == 0 || (pair % 2 != 0)) {
			for (size_t o = (start - pair_size); o < start; o++) {
				main.push_back(vector[o]);
				// vector.at(o) = -1;
			}
		} else if (pair % 2 == 0) {
			for (size_t o = (start - pair_size); o < start; o++) {
				pend.push_back(vector[o]);
				// vector.at(o) = -1;
				// main.push_back(-1);
			}
			b.push_back(b_count++);
		}
		start += pair_size;
		pair++;
	}
	_jacobsthal_insert_(start, pair_size, b, vector, main, pend);
	count++;
	// j(n), precedente valeur de jacob, index qui correspond a J(n)
	// std::cout	<< "pair size: " << pair_size << ";\npending  : ";
	// for (size_t i = 0; i < pend.size(); i++) {
	// 	std::cout	<< pend.at(i) << " ";
	// }
	// std::cout	<< '\n';
	// std::cout	<< "main     : ";
	// for (size_t i = 0; i < main.size(); i++) {
	// 	std::cout	<< main.at(i) << " ";
	// }
	// std::cout	<< "\n\n";
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
	for (size_t i = 0; i < this->_vector.size(); i++)
		std::cout	<< this->_vector[i] << " ";
}