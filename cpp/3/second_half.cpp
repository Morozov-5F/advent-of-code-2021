#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>
#include <limits>

struct node;

struct node
{
	int total_elements;
	node * zeros;
	node * ones;

	void insert_entry(const char* str)
	{
		total_elements++;
		if (*str == '\0')
		{
			return;
		}

		if (*str == '0')
		{
			if (nullptr == zeros)
			{
				zeros = new node();
			}
			zeros->insert_entry(str + 1);
		}
		else
		{
			if (nullptr == ones)
			{
				ones = new node();
			}
			ones->insert_entry(str + 1);
		}
	}

	void build_O2(int & result)
	{
		if (nullptr == ones && nullptr == zeros)
		{
			return;
		}

		auto ones_total = ones == nullptr ? std::numeric_limits<int>::min() : ones->total_elements;
		auto zeros_total = zeros == nullptr ? std::numeric_limits<int>::min() : zeros->total_elements;

		if (ones_total >= zeros_total)
		{
			result = (result << 1) | 1;
			ones->build_O2(result);
		}
		else
		{
			result = result << 1;
			zeros->build_O2(result);
		}
	}

	void build_CO2(int & result)
	{
		if (nullptr == ones && nullptr == zeros)
		{
			return;
		}

		auto ones_total = ones == nullptr ? std::numeric_limits<int>::max() : ones->total_elements;
		auto zeros_total = zeros == nullptr ? std::numeric_limits<int>::max() : zeros->total_elements;

		if (zeros_total <= ones_total)
		{
			result =  result << 1;
			zeros->build_CO2(result);
		}
		else
		{
			result = (result << 1) | 1;
			ones->build_CO2(result);
		}
	}
};

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

	node tree { 0, nullptr, nullptr };
	std::string binary;
	while (input >> binary)
	{
		tree.insert_entry(binary.c_str());
	}
	input.close();

	int o2 = 0, co2 = 0;
	tree.build_O2(o2);
	tree.build_CO2(co2);
	std::cout << o2 << " " << co2 << " " << o2 * co2 << std::endl;

	return 0;
}
