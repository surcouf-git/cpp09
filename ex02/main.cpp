#include <vector>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>

int	main(int argc, char **argv)
{
	(void)argc;
	std::vector<int>::iterator	it;
	std::string					line;
	std::vector<int>			vector;
	std::stringstream			stream(argv[1]);

	while (std::getline(stream, line, ' ')) {
		vector.push_back(std::atoi(line.c_str()));
	}
	it = vector.begin();
	size_t	i = 0, tmp = 0, o = 0;
	it++;
	while (!std::is_sorted(vector.begin(), vector.end()))
	{
		i++;
		if (*it > *(it - 1)) {
			tmp = *it;
			*it  = *(it - 1);
			*(it - 1) = tmp;
		}
		++it;
		if (i == vector.size()) {
			it = vector.begin();
			i = 0;
			continue ;
		}
		o++;
	}
	for (it = vector.begin(); it != vector.end(); ++it) {
		std::cout	<< *it << " " << '\n';
	}
}