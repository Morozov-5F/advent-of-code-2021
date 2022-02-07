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

	int crab, min = std::numeric_limits<int>::max(), max = std::numeric_limits<int>::min();
	while (input >> crab)
	{
		if (crab < min) min = crab;
		if (crab > max) max = crab;

		crabs.push_back(crab);
		if (input.peek() == ',')
		{
			input.ignore();
		}
	}

	std::sort(crabs.begin(), crabs.end());

	int min_distance = std::numeric_limits<int>::max();
	for (int i = min; i <= max; ++i)
	{
		int distance = 0;
		for (auto crab : crabs)
		{
			auto n = std::abs(i - crab);
			distance += n * (n + 1) / 2;
		}

		if (distance < min_distance)
		{
			min_distance = distance;
		}
	}
	std::cout << "Minimal fuel required: " << min_distance << std::endl;
	return 0;
 }
