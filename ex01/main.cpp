#include <iostream>
#include "RPN.hpp"

int	main(int argc, char **argv)
{
	(void)argc;
	RPN	rpn;

	try {
		rpn.parse_fill_do(argv[1]);
	} catch (std::exception &exception) {
		std::cerr	<< exception.what() << '\n';
	}
}