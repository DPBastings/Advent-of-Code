#include <array>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>

using IndexedInt = std::pair<int, long>;

static int			solve1(std::ifstream&);
static int			solve2(std::ifstream&);
static IndexedInt	find_left_digit(std::string const&);
static IndexedInt	find_right_digit(std::string const&);
static IndexedInt	find_left_number(std::string const&);
static IndexedInt	find_right_number(std::string const&);
static IndexedInt	find_number(std::string const&);
static IndexedInt	rfind_number(std::string const&);

int
main(int argc, char** argv) {
	if (argc != 2)
		return (EXIT_FAILURE);
	std::ifstream	input;
	input.open(argv[1]);
	std::cout << "Solution 1: " << solve1(input) << '\n';
	std::cout << "Solution 2: " << solve2(input) << std::endl;
	input.close();
	return (EXIT_SUCCESS);
}

static int
solve1(std::ifstream& inf) {
	std::string	line;
	int			result = 0;
	
	inf.clear();
	inf.seekg(0, std::ios::beg);
	while (std::getline(inf, line)) {
		IndexedInt const	left = find_left_digit(line);
		IndexedInt const	right = find_right_digit(line);
		result += (10 * left.first + right.first);
	}
	return (result);
}

static int
solve2(std::ifstream& inf) {
	std::string	line;
	int			result = 0;
	
	inf.clear();
	inf.seekg(0, std::ios::beg);
	while (std::getline(inf, line)) {
		IndexedInt const	left = find_left_number(line);
		IndexedInt const	right = find_right_number(line);
		result += (10 * left.first + right.first);
	}
	return (result);
}

static IndexedInt	find_left_digit(std::string const& line) {
	size_t const	index = line.find_first_of("0123456789");
	if (index == line.npos)
		return (IndexedInt{0, std::numeric_limits<long>::max()});
	return (IndexedInt{line[index] - '0', index});
}

static IndexedInt	find_right_digit(std::string const& line) {
	size_t const	index = line.find_last_of("0123456789");
	if (index == line.npos)
		return (IndexedInt{0, -1});
	return (IndexedInt{line[index] - '0', index});
}

static IndexedInt	find_left_number(std::string const& line) {
	IndexedInt const	digit = find_left_digit(line);
	IndexedInt const	text = find_number(line);

	if (digit.second < text.second)
		return (digit);
	return (text);
}

static IndexedInt	find_right_number(std::string const& line) {
	IndexedInt const	digit = find_right_digit(line);
	IndexedInt const	text = rfind_number(line);

	if (digit.second > text.second)
		return (digit);
	return (text);
}

constexpr std::array<char const*, 10>	numbers{
	"zero", "one", "two", "three", "four",
	"five", "six", "seven", "eight", "nine"
};

static IndexedInt
find_number(std::string const& str) {
	IndexedInt	result{0, std::numeric_limits<long>::max()};
	int			value = 0;
	
	for (auto const& numstring: numbers) {
		size_t const	found_at = str.find(numstring);
		if (found_at != str.npos && (long)found_at < result.second) {
			result.first = value;
			result.second = (long)found_at;
		}
		++value;
	}
	return (result);
}

static IndexedInt
rfind_number(std::string const& str) {
	IndexedInt	result{0, -1};
	int			value = 0;
	
	for (auto const& numstring: numbers) {
		size_t const	found_at = str.rfind(numstring);
		if (found_at != str.npos && (long)found_at > result.second) {
			result.first = value;
			result.second = found_at;
		}
		++value;
	}
	return (result);
}
