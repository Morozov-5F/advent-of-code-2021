#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>

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

	std::string binary;
	input >> binary;

	int total_numbers = 0;
	std::vector<int> bits(binary.size());
	do
	{
		for (int i = 0; i < binary.size(); ++i)
		{
			if (binary[i] == '1')
			{
				bits[i]++;
			}
		}
		total_numbers++;
	} while (input >> binary);
	input.close();

	int gamma = 0, epsilon = 0;
	for (int i = 0; i < bits.size(); ++i)
	{
		if (bits[i] > total_numbers / 2)
		{
			gamma |= 1 << (bits.size() - i - 1);
		}
		else
		{
			epsilon |= 1 << (bits.size() - i - 1);
		}
	}

	std::cout << "Gamma: " << gamma << "; Epsilon: " << epsilon << "; g * e = " << gamma * epsilon << std::endl;
	return 0;
}
