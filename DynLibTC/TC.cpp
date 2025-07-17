#include <vector>
#include <string>
#include <iostream>


#include "TC.h"
#include "Race.h"


Surface::Surface(double v, std::string name_, size_t t, std::vector<std::pair<size_t, double>> r) : TC{ v, name_ }, time_continuity{ t }, time_relax{ r } {};

double Surface::Time(double distation)
{
	return Race::Fun_(distation, this);
}

int Surface::Dist(Race r1, int mesh)
{
	return r1.dist_(this, mesh);
}

Air::Air(double v, std::string name_, std::vector<std::pair<size_t, double>> kf, std::string type) :TC{ v, name_ }, kf_less{ kf }, type_kf{type} {};
double Air::Time(double distation)
{
	return Race::Fun_(distation, this);
}

int Air::Dist(Race r1, int mesh)
{
	return r1.dist_(this, mesh);
}


