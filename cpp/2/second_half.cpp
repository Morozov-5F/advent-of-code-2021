#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

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

	std::string command;
	int value;

	int horizontal_position = 0, aim = 0, depth = 0;
	while (input >> command >> value)
	{
		if (command == "forward")
		{
			horizontal_position += value;
			depth += value * aim;
		}
		else if (command == "up")
		{
			aim -= value;
		}
		else if (command == "down")
		{
			aim += value;
		}
	}
	input.close();

	std::cout << "Depth x Horizontal Position: " << depth * horizontal_position << std::endl;
	return 0;
}
