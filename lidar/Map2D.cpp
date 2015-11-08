/*
 *      Author: Artur Waz
 *      Year: 2015
 */

#include <Map2D.h>
#include <fstream>
#include <sstream>
#include <stdexcept>


Map2D::Map2D() {
	// TODO Auto-generated constructor stub

}

Map2D::~Map2D() {
	// TODO Auto-generated destructor stub
}

bool Map2D::readMap(const std::string &fileName) {

	std::ifstream in{fileName,std::iostream::in};
	if (!in.is_open()) return false;

	//std::string const message{"Cannot properly parse input map file."};

	auto parseLine = [](std::string const &str) -> LineSegment2D {
		LineSegment2D line{};
		char *ptr = const_cast<char*>(str.data());

		line.p0().x() = strtod(ptr,&ptr);
		if (*ptr != ',') throw 3;
		line.p0().y() = strtod(++ptr,&ptr);
		if (*ptr != ',') throw 5;
		line.p1().x() = strtod(++ptr,&ptr);
		if (*ptr != ',') throw 7;
		line.p1().y() = strtod(++ptr,&ptr);

		return line;
	};


	try {
		std::string fileLine{};
		while (std::getline(in,fileLine)) {
			if (fileLine.at(0) != '#')
				lineSegments.push_back(parseLine(fileLine));
		}
	} catch (...) {
		throw std::runtime_error("Cannot properly parse input map file.");
	}

	return true;
}

bool Map2D::saveMap(const std::string &fileName) {

	return true;
}
