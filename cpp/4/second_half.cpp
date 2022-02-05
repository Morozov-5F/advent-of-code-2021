#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <tuple>

constexpr int BINGO_SIZE = 5;

struct bingo_card
{
	bool won;
	int unassigned_sum;
	std::array<std::array<std::pair<bool, int>, BINGO_SIZE>, BINGO_SIZE> numbers;

	bingo_card() : unassigned_sum(0), won(false)
	{
		for (auto & line : numbers)
		{
			for (auto & pos : line)
			{
				pos = std::pair<bool, int>(false, 0);
			}
		}
	}

	void reset()
	{
		unassigned_sum = 0;
	}

	bool close_number(int number)
	{
		bool already_won = false;
		for (int i = 0; i < BINGO_SIZE; ++i)
		{
			for (int j = 0; j < BINGO_SIZE; ++j)
			{
				if (numbers[i][j].first || numbers[i][j].second != number)
				{
					continue;
				}

				numbers[i][j].first = true;
				unassigned_sum -= number;

				// Need this to eliminate other possible matches
				if (already_won)
				{
					continue;
				}

				// Check if we have a winner in line or column
				bool row_won = true, column_won = true;
				for (int k = 0; k < BINGO_SIZE; ++k)
				{
					row_won = row_won && numbers[i][k].first;
					column_won = column_won && numbers[k][j].first;
				}

				already_won = row_won || column_won;
			}
		}
		if (already_won)
		{
			won = true;
		}
		return already_won;
	}

	friend std::istream& operator>> (std::istream& in, bingo_card& card)
	{
		for (auto & line : card.numbers)
		{
			for (auto & position : line)
			{
				in >> position.second;
				card.unassigned_sum += position.second;
			}
		}
		return in;
	}

	friend std::ostream& operator<< (std::ostream& out, const bingo_card& card)
	{
		for (auto & line : card.numbers)
		{
			for (auto & position : line)
			{
				if (position.first)
				{
					out << "\033[0;31m " << position.second << "\033[0m ";
				}
				else
				{
					out << position.second << " ";
				}
			}
			out << std::endl;
		}
		return out;
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

	std::string buffer;
	std::getline(input, buffer);

	std::vector<int> numbers;
	std::istringstream numbers_stream(buffer);

	for (int number; numbers_stream >> number; )
	{
		numbers.push_back(number);
		if (numbers_stream.peek() == ',')
		{
			numbers_stream.ignore();
		}
	}

	std::vector<bingo_card> cards;
	for (bingo_card card; input >> card; )
	{
		cards.push_back(card);
		card.reset();
	}
	input.close();

	bool card_won = false;
	int number_that_ended_game = 0;
	int unassigned_sum = 0;
	for (auto number : numbers)
	{
		for (auto & card : cards)
		{
			if (!card.won && card.close_number(number))
			{
				number_that_ended_game = number;
				unassigned_sum = card.unassigned_sum;
			}
		}
	}

	std::cout << "Unassigned sum: " << unassigned_sum << ", Number that won: " << number_that_ended_game << ", Answer = " << unassigned_sum * number_that_ended_game << std::endl;
	return 0;
}
