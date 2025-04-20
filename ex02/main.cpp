#include "PmergeMe.hpp"

// int	jacobsthal_generator(int j_n, int n) { return (2 * j_n + static_cast<int>(pow(-1, n))); }

int	main(int argc, char **argv)
{
	if (argc < 2) {
		std::cerr	<< "Error\n";
		return (1);
	}
	PmergeMe	FJohnson(argv);
	try {
		FJohnson._launch_();
	} catch (std::exception &e) {
		std::cout	<< e.what() << '\n';
	}
	return (0);
}