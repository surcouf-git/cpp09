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
		this->_deque.push_back(std::atoi(argv[o]));
		o++;
	}
	if (o < 2)
		throw (std::runtime_error("Error"));
}

template <typename C>
void	swap_range(C &contenair, size_t end, size_t pair_size, size_t start) {
	C	swapper;

	while (start < (end + 1)) {
		swapper.push_back(contenair[start]);
		contenair[start] = contenair[start + pair_size];
		start++;
	}
	for (size_t i = (end + 1), range = 0; range < pair_size; i++, range++) {
		contenair.at(i) = swapper.at(range);
	}
}

template <typename C>
size_t	binary_search(C &contenair, size_t pair_size, int value) {
	C						values;
	typename C::iterator	it;
	int	i = 0;
	int		to_find = 0;

	for (size_t i = pair_size - 1; i < contenair.size(); i += pair_size)
		values.push_back(contenair.at(i));
	it = std::upper_bound(values.begin(), values.end(), value);
	to_find = *it;
	for (; static_cast<int>(values.at(i)) < to_find; i++) {}
	if (i == 0)
		return (0);
	return (i * pair_size);
}

int	jacobsthal_generator(int j_n, int n) { return (2 * j_n + pow(-1, n)); }

template <typename C>
C	jacobsthal_insert(size_t &pair_size, std::list<int> &b, C &main, C &pend) {
	size_t				index = 0, start = 0;
	int					b_popped = 0;
	int	j_n = 1, n = 2, actual, range;
	bool				passed = false;

	while (!b.empty()) {
		if (passed == false) {
			actual = jacobsthal_generator(j_n, n);
			if (actual > static_cast<int>(b.front()))
				passed = true;
			range = actual - j_n;
			j_n = actual;
			actual -= 1;
		}
		if (passed == true) {
			actual = b_popped + 1;
			range = 1;
		}
		while (range > 0) {
			start = actual * pair_size - pair_size;
			index = binary_search<C>(main, pair_size, pend.at(actual * pair_size - 1));
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

template <typename C>
void	sort_back(C &contenair, size_t pair_size) {
	C				pend, main, excludes;
	std::list<int>	b;
	size_t			start = 0, pair = 0, cutter = 0;;
	int				b_count = 2, i = 0;

	if (pair_size * 3 > contenair.size()) {
		return ;
	}
	while (start < contenair.size()) {
		if (start + pair_size > contenair.size()) {
			for (size_t i = start; i < contenair.size(); i++)
				excludes.push_back(contenair.at(i));
			break ;
		}
		if (pair == 0 || (pair % 2 != 0)) {
			for (size_t o = start; o < (start + pair_size) - cutter; o++, i++)
				main.push_back(contenair.at(o)); 
		} else if (pair % 2 == 0) {
			for (size_t o = start; o < (start + pair_size) - cutter; o++, i++)
				pend.push_back(contenair.at(o));
			b.push_back(b_count++);
		}
		start += pair_size;
		pair++;
	}
	contenair = jacobsthal_insert<C>(pair_size, b, main, pend);
	for (size_t i = 0; i < excludes.size(); i++)
		contenair.push_back(excludes.at(i));
}

template <typename C>
void	make_pairs(C &contenair, size_t pair_size) {
	if (pair_size > (contenair.size() / 2))
		return ;
	size_t	end = (pair_size - 1);

	while ((end + pair_size) < contenair.size()) {
		if (contenair[end] > contenair[end + pair_size])
			swap_range<C>(contenair, end, pair_size, ((end + 1) - pair_size));
		end += (pair_size * 2);
	}
	make_pairs<C>(contenair, pair_size * 2);
	//Apres le dernier appel recursif
	sort_back<C>(contenair, pair_size);
}

void	sort(std::vector<int> &vector, std::deque<int> &deque) {
	make_pairs<std::vector<int>>(vector, 1);
	make_pairs<std::deque<int>>(deque, 1);
}

void	PmergeMe::_launch_(void) {
	this->_parse_();
	sort(this->_vector, this->_deque);
	if (std::is_sorted(_vector.begin(), _vector.end()))
		std::cout	<< "Vector sorted\n";
	if (std::is_sorted(_deque.begin(), _deque.end()))
		std::cout	<< "Deque sorted\n";
}