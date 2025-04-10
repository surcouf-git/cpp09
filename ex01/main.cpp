#include <iostream>
#include "RPN.hpp"

int	main(int argc, char **argv)
{
	(void)argc;
	RPN	rpn;
	std::string	line(argv[1]);

	try {
		rpn.parse_fill_do(line);
	} catch (std::exception &exception) {
		std::cerr	<< exception.what() << '\n';
	}
}