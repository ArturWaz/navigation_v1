/*
 *      Author: Artur Waz
 *      Year: 2015
 */


#include <Lidar2D.h>


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE lidar2d
#include <boost/test/unit_test.hpp>



struct UnitTest_Lidar2D {
	UnitTest_Lidar2D(): lidar{&map} {}

	double eps{1e-5};

	Lidar2D lidar;
	Map2D map;
	Point2D pose;
};


BOOST_FIXTURE_TEST_SUITE(LidarSensor, UnitTest_Lidar2D)



BOOST_AUTO_TEST_CASE(SimpleCase){
	map.lineSegments = std::vector<LineSegment2D>{
		LineSegment2D{Point2D{-2,-3},Point2D{68,84}}
	};
	pose = Point2D{12,45};

	double results[361] // generated from matlab/octave
				   { 24.62068965517240926033, 24.97519939730237936715, 25.34790137185640190864, 25.73985481880516346109, 26.15221149357639873756, 26.58622558805378233160, 27.04326497374392346273, 27.52482397636293498522, 28.03253792987669967829, 28.56819980508580414380,
				   29.13377926518710836490, 29.73144457092649162178, 30.36358784426254686650, 31.03285430610871031831, 31.74217623618335437641, 32.49481256841231413546, 33.29439524305631437073, 34.14498369916432096716, 35.05112922456242330327, 36.01795130749982121188,
				   37.05122868421183568444, 38.15750849085455342902, 39.34423786274086864978, 40.61992355673025656415, 41.99432681380205423238, 43.47870288421172801918, 45.08609763126315783666, 46.83171773761715428464, 48.73339674090469486600, 50.81218714231607691545,
				   53.09312025537042245560, 55.60619198035625743159, 58.38765695927327925574, 61.48174985001908510185, 64.94300775042920292890, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 49.45983400591644141286, 47.49703601365772698273, 45.69746629433420537225, 44.04220889519658044264, 42.51517137844427907112, 41.10257741154988764265,
				   39.79256499697325466514, 38.57486554344542639683, 37.44054541780738531997, 36.38179623260177208977, 35.39176347496294283701, 34.46440554112240306495, 33.59437706409643453753, 32.77693178727040645981, 32.00784126805787366266, 31.28332648181838848700,
				   30.60000000000000142109, 29.95481688378806595097, 29.34503279882520487831, 28.76816814245515985249, 28.22197720074163029835, 27.70442153193834755598, 27.21364691648103928401, 26.74796332880422156109, 26.30582747936445286996, 25.88582755081710473632,
				   25.48666981392567976172, 25.10716685928444391607, 24.74622722249183937038, 24.40284621475413473490, 24.07609779938790950382, 23.76512737841864009170, 23.46914537330380667868, 23.18742150044603178571, 22.91927965616356743794, 22.66409333760879007968,
				   22.42128153614209651323, 22.19030504817804327899, 21.97066315577315265273, 21.76189063542343049562, 21.56355505885037970870, 21.37525435411934537910, 21.19661459936623160161, 21.02728802480527292573, 20.86695120163187056050, 20.71530339898797734577,
				   20.57206509237904157317, 20.43697660886954281523, 20.30979689607902827220, 20.19030240348532601047, 20.07828606584695307902, 19.97355637970591502039, 19.87593656494701122028, 19.78526380428863262750, 19.70138855437748048871, 19.62417392287024853204,
				   19.55349510651981148612, 19.48923888585210306701, 19.43130317253145733503, 19.37959660597427458129, 19.33403819619007180108, 19.29455701021127111972, 19.26109189982343750103, 19.23359126863108414796, 19.21201287679436831013, 19.19632368205304828734,
				   19.18649971591930381010, 19.18252599417334636200, 19.18439646103860241055, 19.19211396664885427299, 19.20569027765125014184, 19.22514612101855036030, 19.25051126137460144605, 19.28182461237081923855, 19.31913438289139861581, 19.36249825911344757401,
				   19.41198362370871777216, 19.46766781374829946571, 19.52963841916482934380, 19.59799362394107902219, 19.67284259253418809976, 19.75430590441488831743, 19.84251604000643354198, 19.93761792175380520575, 20.03976951454677646325, 20.14914249026758241712,
				   20.26592296184359298650, 20.39031229286747404217, 20.52252798961200497274, 20.66280468312744034165, 20.81139521008050863315, 20.96857180209270410387, 21.13462739458232420020, 21.30987706753116839309, 21.49465963221317110765, 21.68933937976799342096,
				   21.89430800961701351071, 22.10998675814772340686, 22.33682875088625507942, 22.57532160460278802816, 22.82599030952362184621, 23.08940042614878507266, 23.36616163620146124913, 23.65693169309811239032, 23.96242082417816021689, 24.28339664496508731872,
				   24.62068965517241281304 };

	for (int i = 0; i <= 360; ++i) {
		double const distance{lidar.measure(pose,i)};
		BOOST_REQUIRE_MESSAGE(std::abs(distance-results[i]) <= eps,
				std::string("Problem with angle: ")+std::to_string(i)+
				std::string(". Should be: "+std::to_string(results[i])+
						std::string(", but is: ")+std::to_string(distance)));
	}
}


BOOST_AUTO_TEST_CASE(LidarPlacedInLineSegment){
	map.lineSegments = std::vector<LineSegment2D>{
		LineSegment2D{Point2D{-3,-3},Point2D{68,68}}
	};
	pose = Point2D{-3,-3};

	/*double results[361] // generated from matlab/octave
				   ;*/

	for (int i = 0; i <= 360; ++i) {
		double const distance{lidar.measure(pose,i)};
		BOOST_REQUIRE_MESSAGE(std::abs(distance) <= eps,
				std::string("Problem with angle: ")+std::to_string(i)+
				std::string(". Should be: "+std::to_string(0.)+
						std::string(", but is: ")+std::to_string(distance)));
	}
}


BOOST_AUTO_TEST_CASE(LidarPlacedInLine){
	map.lineSegments = std::vector<LineSegment2D>{
		LineSegment2D{Point2D{-3,-3},Point2D{68,68}}
	};
	pose = Point2D{100,100};

	double results[361] // generated from matlab/octave
				   { 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 45.25483399593903754976, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300, 1.0e+300,
				   1.0e+300 };

	for (int i = 0; i <= 360; ++i) {
		double const distance{lidar.measure(pose,i)};
		BOOST_REQUIRE_MESSAGE(std::abs(distance-results[i]) <= eps,
				std::string("Problem with angle: ")+std::to_string(i)+
				std::string(". Should be: "+std::to_string(results[i])+
						std::string(", but is: ")+std::to_string(distance)));
	}
}



BOOST_AUTO_TEST_SUITE_END()
