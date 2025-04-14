#include <iostream>
#include "RPN.hpp"

int	main(int argc, char **argv)
{
	RPN	rpn;

	if (argc != 2) {
		std::cerr	<< "Unsage: ./RPN \"...\"";
		return (1);
	}
	std::string	line(argv[1]);
	try {
		rpn.parse_fill_do(line);
	} catch (std::exception &exception) {
		std::cerr	<< exception.what() << '\n';
	}
}