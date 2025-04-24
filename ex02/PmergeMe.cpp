#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(char **argv) : _argv(argv) {}

PmergeMe::PmergeMe(const PmergeMe &other) { (void)other; }

PmergeMe::~PmergeMe(void) {}

PmergeMe	&PmergeMe::operator=(const PmergeMe &other) { (void)other; return (*this); }

void	PmergeMe::_parse_(void) {
	std::string			line;
	std::stringstream	stream;
	char				**argv = this->_argv;
	int					i = 0, o = 1, dbl = 0, vec_size = static_cast<int>(this->_vector.size());

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
	o = 0;
	(void)dbl;
	while (o < vec_size) {
		dbl = this->_vector.at(o);
		i = o + 1;
		while (i < vec_size) {
			if (dbl == this->_vector.at(i))
				throw (std::runtime_error("Error"));
			i++;
		}
		o++;
	}
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
	typename C::iterator	it;
	C						values;
	size_t					contenair_size = contenair.size();
	int						i = 0, to_find = 0, upper = 0;

	for (size_t i = pair_size - 1; i < contenair_size; i += pair_size)
		values.push_back(contenair.at(i));
	it = values.end();
	--it;
	if (values.size() > 0 && value > *it) {
		to_find = *it;
		upper = 1;
	} else {
		it = std::upper_bound(values.begin(), values.end(), value);
		to_find = *it;
	}
	for (i = 0; values.at(i) < to_find; i++) {}
	if (i == 0)
		return (0);
	return ((i + upper) * pair_size);
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

#include <ctime> // Pour mesurer le temps en C++98

void sort(std::vector<int> &vector, std::deque<int> &deque) {
	// Les mesures de temps seront faites dans la fonction _launch_
	make_pairs< std::vector<int> >(vector, 1);
	make_pairs< std::deque<int> >(deque, 1);
}

void PmergeMe::_launch_(void) {
	size_t	size;

	this->_parse_();
	size = this->_vector.size();
	std::cout << "Before: ";
	for (size_t i = 0; i < size; i++)
		std::cout << this->_vector.at(i) << ' ';
	std::cout << '\n';

	// Créer des copies pour mesurer séparément
	std::deque<int>		deque_copy = this->_deque;
	std::vector<int>	vector_copy = this->_vector;

	// Mesure du temps pour vector
	clock_t start_vector = clock();
	make_pairs< std::vector<int> >(vector_copy, 1);
	clock_t end_vector = clock();

	// Mesure du temps pour deque
	clock_t start_deque = clock();
	make_pairs< std::deque<int> >(deque_copy, 1);
	clock_t end_deque = clock();

	// Calculer les temps en microsecondes
	double vector_time = (double)(end_vector - start_vector) * 1000000 / CLOCKS_PER_SEC;
	double deque_time = (double)(end_deque - start_deque) * 1000000 / CLOCKS_PER_SEC;

	// Trier les conteneurs originaux pour l'affichage
	sort(this->_vector, this->_deque);

	std::cout << "After: ";
	for (size_t i = 0; i < size; i++)
		std::cout << this->_vector.at(i) << ' ';
	std::cout << '\n';

	// Afficher les temps avec suffisamment de précision
	std::cout << "Time to process a range of " << size << " elements with std::vector : " 
			  << std::fixed << std::setprecision(5) << vector_time << " us\n";
	std::cout << "Time to process a range of " << size << " elements with std::deque : " 
			  << std::fixed << std::setprecision(5) << deque_time << " us\n";
}

// void	sort(std::vector<int> &vector, std::deque<int> &deque) {
// 	make_pairs< std::vector<int> >(vector, 1);
// 	make_pairs< std::deque<int> >(deque, 1);
// }

// void	PmergeMe::_launch_(void) {
// 	size_t	size;

// 	this->_parse_();
// 	size = this->_vector.size();
// 	std::cout	<< "Before: ";
// 	for (size_t i = 0; i < size; i++)
// 		std::cout	<< this->_vector.at(i) << ' ';
// 	std::cout	<< '\n';
// 	sort(this->_vector, this->_deque);
// 	std::cout	<< "After: ";
// 	for (size_t i = 0; i < size; i++)
// 		std::cout	<< this->_vector.at(i) << ' ';
// 	if (std::is_sorted(this->_vector.begin(), this->_vector.end()))
// 		std::cout	<< "Sorted !";
// 	std::cout	<< "\n";
// 	std::cout	<< "Time to process a range of " << size << " elements with vector: ";
// 	std::cout	<< "--time--\n";
// 	std::cout	<< "Time to process a range of " << size << " elements with deque: ";
// 	std::cout	<< "--time--\n";
// }