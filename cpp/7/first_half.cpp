#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <cmath>
#include <array>
#include <tuple>

int main(int argc, char * const argv[])
{
	if (argc < 2)
	{
		std::cerr << "Input filename is required but not provided, aborting" << std::endl;
		return 1;
	}

	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cerr << "Unable to open the provided file" << std::endl;
		return 1;
	}

	std::vector<int> crabs;

	int crab;
	while (input >> crab)
	{
		crabs.push_back(crab);
		if (input.peek() == ',')
		{
			input.ignore();
		}
	}

	std::sort(crabs.begin(), crabs.end());

	int a = 0, b = 0, c = 0;
	for (std::size_t i = 0, size = crabs.size(); i < size; ++i)
	{
		a += std::abs(crabs[i] - crabs[size / 2 - 1]);
		b += std::abs(crabs[i] - crabs[size / 2]);
		c += std::abs(crabs[i] - crabs[size / 2 + 1]);
	}
	int res = std::min(a, std::min(b, c));
	std::cout << "Crabs movement: " << a << " " << b << " " << c << " " << res << std::endl;
	return 0;
 }
