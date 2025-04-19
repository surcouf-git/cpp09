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

int	prochain_jacobsthal_efficace(int j_n, int n) { return (2 * j_n + static_cast<int>(pow(-1, n))); }
int	count = 0;
void	PmergeMe::_sort_back_(std::vector<int> &vector, size_t pair_size) {
	std::vector<int>::iterator	it;
	std::vector<int>			pend, main, temp_vec, b;
	size_t						start = pair_size, pair = 0, original_size = vector.size();
	int							j_n = 1, n = 4, b_count = 2, i = 0, temp_saver, actual, range;

	while (start < vector.size()) {
		if (pair == 0 || (pair % 2 != 0)) {
			for (size_t o = (start - pair_size); o < start; o++) {
				main.push_back(vector[o]);
			}
		} else if (pair % 2 == 0) {
			for (size_t o = (start - pair_size); o < start; o++) {
				pend.push_back(vector[o]);
			}
			b.push_back(b_count++);
		}
		start += pair_size;
		pair++;
	}
	/* Creation d'un vecteur contenant 2, 3, 4... (b2, b3, b4...)
	 * le but etant de me servir de ce vecteur comme repaire pour
	 * l'insertion des ranges selon la suite de jacob
	 * reste a trouver comment se servir de jacob pour l'insertion binaire */
	int p = 0;
	if (count == 1) {
		while (!b.empty()) {
			actual = prochain_jacobsthal_efficace(j_n, n);
			range = actual - j_n;
			j_n = actual;
			actual -= 1;
			while (actual > 0) {
				start = actual * pair_size - pair_size;
				while (start < actual * pair_size) {
					temp_vec.push_back(pend[start]);
					start++;
				}
				it = std::lower_bound(vector.begin(), vector.end(), *temp_vec.end());
				vector.insert(it, temp_vec.begin(), temp_vec.end());
				temp_vec.clear();
				// b.pop_back();
				actual--;
				for (size_t i = 0; i < vector.size(); i++) {
					std::cout	<< vector.at(i) << ' ';
				}
				exit (0);
			}
		}
		exit (0);
	}
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
	// for (size_t i = 0; i < this->_vector.size(); i++)
	// 	std::cout	<< this->_vector[i] << " ";
}