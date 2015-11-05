/*
 *      Author: Artur Waz
 *      Year: 2015
 */

#ifndef MAP_H_
#define MAP_H_


#include <vector>
#include <string>
#include "LineSegment2D.h"


class Map2D {
public:

	Map2D();
	~Map2D();

	bool readMap(std::string const &);
	bool saveMap(std::string const &);


	std::vector<LineSegment2D> lineSegments;

};

#endif /* MAP_H_ */
