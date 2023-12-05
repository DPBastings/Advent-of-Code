#include "aoc.hpp"
#include "Range.hpp"

#include <istream>

// Constructors

Map::Map(std::string const& title):
	std::vector<MapLine>(), _title(title) {}

MapLine::MapLine(Range const& source, Range const& destination):
	_source(source), _destination(destination) {}

// Public methods

size_t
Map::find_destination(size_t entry) const {
	for (MapLine const& line: *this) {
		size_t	offset = line.source().offset(entry);
		if (offset != static_cast<size_t>(-1))
			return (line.destination().begin() + offset);
	}
	return (entry);
}

std::string const&
Map::title() const {
	return (_title);
}

Range const&
MapLine::source() const {
	return (_source);
}

Range const&
MapLine::destination() const {
	return (_destination);
}

size_t
MapLine::map(size_t entry) const {
	return (_destination.begin() + (entry - _source.begin()));
}

// Non-member functions

std::istream&
operator>>(std::istream& is, MapLine& mline) {
	size_t	srcbegin;
	size_t	dstbegin;
	size_t	len;

	is >> dstbegin >> srcbegin >> len;
	mline = MapLine(
		Range(srcbegin, len),
		Range(dstbegin, len));
	return (is);
}

std::ostream&
operator<<(std::ostream& os, Map const& map) {
	os << map.title() << '\n';
	for (auto const& line: map)
		os << line << '\n';
	return (os);
}

std::ostream&
operator<<(std::ostream& os, MapLine const& mline) {
	os << '{' << mline.source() << ", " << mline.destination() << '}';
	return (os);
}
