#include "BitcoinExchange.hpp"
#include <iostream>

int	main(int argc, char **argv) 
{
	if (argc != 2) {
		std::cerr	<< "Error: could not open file.\n";
		return (1);
	}
	try
	{
		BitcoinExchange	btc;
		btc.handleInfile(argv[1]);
	}
	catch (std::exception &exception)
	{
		std::cout	<< exception.what() << '\n';
		return (1);
	}
	return (0);
}