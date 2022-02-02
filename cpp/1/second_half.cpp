#include <iostream>
#include <fstream>
#include <cstdint>

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

	uint64_t increasing_measurements = 0;

	int a, b, c, d;
	input >> a >> b >> c;

	while (input >> d)
	{
		if (b + c + d > a + b + c)
		{
			increasing_measurements++;
		}
		a = b;
		b = c;
		c = d;
	}
	
	input.close();
	
	std::cout << "Number of increasing measurements: " << increasing_measurements << std::endl;
	return 0;
}
