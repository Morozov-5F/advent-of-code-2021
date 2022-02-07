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

	for (int i = 1; i <= 80; ++i)
	{
		for (std::size_t i = 0, s = fishes.size(); i < s; ++i)
		{
			if (fishes[i] == 0)
			{
				fishes[i] = 6;
				fishes.push_back(8);
				continue;
			}

			fishes[i]--;
		}
	}

	std::cout << "Total fishes: " << fishes.size() << std::endl;
	return 0;
}
