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
	int previous_measurement = 0;
	input >> previous_measurement;

	int measurement = 0;
	while (input >> measurement)
	{
		if (measurement > previous_measurement)
		{
			increasing_measurements++;
		}
		previous_measurement = measurement;
	}

	input.close();
	
	std::cout << "Number of increasing measurements: " << increasing_measurements << std::endl;
	return 0;
}
