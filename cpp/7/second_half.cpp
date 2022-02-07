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

	int crab, sum = 0;
	while (input >> crab)
	{
		sum += crab;

		crabs.push_back(crab);
		if (input.peek() == ',')
		{
			input.ignore();
		}
	}

	int mean_floor = std::floor(sum / static_cast<double>(crabs.size()));
	int mean_ceil = std::ceil(sum / static_cast<double>(crabs.size()));

	auto distance = [](int n){ return n * (n + 1) / 2; };

	int sum_ceil = 0, sum_floor = 0;
	for (auto crab : crabs)
	{
		sum_ceil += distance(std::abs(mean_ceil - crab));
		sum_floor += distance(std::abs(mean_floor - crab));
	}
	std::cout << "Minimal fuel required: " << std::min(sum_ceil, sum_floor) << std::endl;
	return 0;
 }
