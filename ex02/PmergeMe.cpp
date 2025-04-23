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
std::vector<unsigned long long>	p;

template <typename C>
size_t	binary_search(C &contenair, size_t pair_size, int value) {
try {
	size_t					index = 0, odd = 0;
	C						values;
	typename C::iterator	it;
	int	i = 0, o = 0;
	unsigned long long		to_find = 0;

	for (size_t i = pair_size - 1; i < contenair.size(); i += pair_size) {
		values.push_back(contenair.at(i));
		// std::cout	<< values.at(o) << ' ';
		o++;
	}
	it = std::upper_bound(values.begin(), values.end(), value);
	to_find = *it;
	for (; values.at(i) < to_find; i++) {}
	std::cout	<< "{" << to_find << "} [" << value << "] " << i  << '/' << *it << "\n";
	if (i == 0)
		return (0);
	return (i * pair_size);
	} catch (...) { std::cout	<< "dedans\n"; throw(1); }
}

unsigned long long	jacobsthal_generator(unsigned long long j_n, unsigned long long n) { return (2 * j_n + pow(-1, n)); }

std::vector<int>	_jacobsthal_insert_(size_t &pair_size, std::list<int> &b, std::vector<int> &vector, std::vector<int> &main, std::vector<int> &pend) {
	std::vector<int>	temp_vec;
	size_t				index = 0, start = 0;
	int					i = 0, b_popped = 0;
	unsigned long long	j_n = 1, n = 2, actual, range;
	bool				passed = false;

	while (!b.empty()) {
		if (passed == false) {
			actual = jacobsthal_generator(j_n, n);
			if (actual > b.front())
				passed = true;
			p.push_back(actual);
			range = actual - j_n;
			j_n = actual;
			actual -= 1;
		}
		if (passed == true) {
			// actual = b.front() - 2;
			actual = b_popped + 1;
			range = 1;
			std::cout	<< b_popped << "-" << b.front() << "-";
		}
		while (range > 0) {
			start = actual * pair_size - pair_size;
			try {
			std::cout	<< "ACTUAL: " << actual << " pair_size:" << pair_size << " count: " << count << '\n';
			index = binary_search(main, pair_size, pend.at(actual * pair_size - 1)); } catch (...) {std::cout	<< "izi " << pair_size << ' ' << (actual * pair_size - 1) << ' ' << actual; exit(0); }
			for (size_t i = 0; i < pair_size; i++, index++, start++)
				main.insert(main.begin() + index, pend.at(start));
			b.erase(std::find(b.begin(), b.end(), actual + 1));
			b_popped++;
			actual--, range--;
		}
		n++;
	}
	return (main);
}

void	PmergeMe::_sort_back_(std::vector<int> &vector, size_t pair_size) {
	std::vector<int>::iterator	it;
	std::vector<int>			pend, main, excludes;
	std::list<int>				b;
	size_t						start = 0, pair = 0, both_size = 0, cutter = 0;;
	int							b_count = 2, i = 0;
	static bool					skipper = true;

	if (pair_size * 3 > vector.size()) {
		skipper = false;
		return ;
	}
	while (start < vector.size()) {
		if (start + pair_size > vector.size()) {
			for (size_t i = start; i < vector.size(); i++)
				excludes.push_back(vector.at(i));
			break ;
		}
		if (pair == 0 || (pair % 2 != 0)) {
			for (size_t o = start; o < (start + pair_size) - cutter; o++, i++) {
				main.push_back(vector.at(o)); if (count == 100) {std::cout	<< vector.at(o) << "<-";} }
		} else if (pair % 2 == 0) {
			for (size_t o = start; o < (start + pair_size) - cutter; o++, i++) {
				pend.push_back(vector.at(o)); if (count == 100) {std::cout	<< vector.at(o) << ' ';} }
			b.push_back(b_count++);
		}
		start += pair_size;
		pair++;
	}
	// for (;i < vector.size(); i++)
	// 	main.push_back(vector.at(i));
	// if (1) {
	// 	// std::cout	<< "{" << start << "}\n";
	// 	std::cout	<< "APPEL:" << count << '\n';
	// 	std::cout	<< "vector:\n";
	// 	for (size_t i = 0; i < vector.size(); i++) {
	// 		std::cout	<< vector.at(i) << ' ';
	// 	}
	// 	std::cout	<< '\n';
	// 	std::cout	<< "main:\n";
	// 	for (size_t i = 0; i < main.size(); i++) {
	// 		std::cout	<< main.at(i) << ' ';
	// 	}
	// 	std::cout	<< std::endl;
	// 	std::cout	<< "pend:\n";
	// 	for (size_t i = 0; i < pend.size(); i++) {
	// 		std::cout	<< pend.at(i) << ' ';
	// 	}
	// 	std::cout	<< '\n';
	// 	// if (count == 3)
	// 	// 	exit(0);
	// }
	try {
		vector = _jacobsthal_insert_(pair_size, b, vector, main, pend);
		for (size_t i = 0; i < excludes.size(); i++)
			vector.push_back(excludes.at(i));
	} catch (...) { std::cout	<< "ici\n"; exit(1); }
	count++;
}

void	PmergeMe::_vec_make_pairs_(std::vector<int> &vector, size_t pair_size) {
	if (pair_size > (vector.size() / 2))
		return ;
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
	this->_vec_make_pairs_(this->_vector, 1);
}

void	PmergeMe::_launch_(void) {
	this->_parse_();
	this->_sort_();
	if (std::is_sorted(_vector.begin(), _vector.end()))
		std::cout	<< "Sorted\n";
}