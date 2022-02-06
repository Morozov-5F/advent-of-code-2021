#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <cmath>
#include <array>
#include <tuple>

constexpr auto MAX_SIZE = 1000;

struct line
{
	std::pair<int, int> start;
	std::pair<int, int> end;

	line() : start(0, 0), end(0, 0) {}

	template <std::size_t N>
	void draw(std::array<std::array<int, N>, N> & plane) const
	{
		int x0 = start.first, y0 = start.second, x1 = end.first, y1 = end.second;
		bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
		if (steep)
		{
			std::swap(x0, y0);
			std::swap(x1, y1);
		}
		if (x0 > x1)
		{
			std::swap(x0, x1);
			std::swap(y0, y1);
		}

		int dx = x1 - x0;
		int dy = std::abs(y1 - y0);
		int error = dx / 2;
		int ystep = (y0 < y1) ? 1 : -1;
		int y = y0;
		for (int x = x0; x <= x1; x++)
		{
			plane[steep ? y : x][steep ? x : y]++;
			error -= dy;
			if (error < 0)
			{
				y += ystep;
				error += dx;
			}
		}
	}

	friend std::istream& operator>> (std::istream& in, line& line)
	{
		in >> line.start.first;
		in.ignore();
		in >> line.start.second;
		in.ignore(4);
		in >> line.end.first;
		in.ignore();
		in >> line.end.second;

		return in;
	}

	friend std::ostream& operator<< (std::ostream& out, const line& line)
	{
		return out << line.start.first << "," << line.start.second << " -> " << line.end.first << "," << line.end.second;
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

	std::vector<line> lines;

	std::string buffer;
	while (std::getline(input, buffer))
	{
		std::istringstream lines_stream(buffer);

		line temp_line;
		lines_stream >> temp_line;
		lines.push_back(temp_line);
	}
	input.close();

	std::array<std::array<int, MAX_SIZE>, MAX_SIZE> plane = { 0 };
	for (const auto &line : lines)
	{
		line.draw(plane);
	}

	int intersections = 0;
	for (const auto &line : plane)
	{
		for (auto element : line)
		{
			if (element > 1)
			{
				intersections++;
			}
		}
	}
	std::cout << "Total intersections: " << intersections << std::endl;
	return 0;
}
