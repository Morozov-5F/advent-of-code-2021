#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <cmath>
#include <array>
#include <tuple>

constexpr int TOTAL_DAYS = 256;

static std::vector<uint64_t> fishes_by_offset(TOTAL_DAYS + 1, 0);

uint64_t population(int start, int remaining, std::string prefix = "")
{
	if (start > remaining)
	{
		return 0;
	}

	if (fishes_by_offset[start] != 0)
	{
		return fishes_by_offset[start];
	}

	int children = (remaining - start) / 7 + ((remaining - start) % 7 != 0 ? 1 : 0);
	uint64_t res = 0;
	for (int i = 0; i < children; ++i)
	{
		res += population(start + 7 * i + 9, remaining, prefix + "\t");
	}
	fishes_by_offset[start] = children + res;
	return children + res;
}

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

	std::vector<int> fishes;

	int fish;
	while (input >> fish)
	{
		fishes.push_back(fish);
		if (input.peek() == ',')
		{
			input.ignore();
		}
	}

	uint64_t res = 0;
	for (auto fish : fishes)
	{
	res += population(fish, TOTAL_DAYS) + 1;
	}

	std::cout << "Total fishes: " << res << std::endl;
	return 0;
}
