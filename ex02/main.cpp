#include "PmergeMe.hpp"

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
		std::cerr	<< e.what() << '\n';
	}
	return (0);
}