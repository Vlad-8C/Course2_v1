#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h> 


#include "TC.h"
#include "Rendering.h"
#include "Race.h"


double Race::Fun_(double distation, Surface* obj)
{

	double time = distation / obj->velocity;
	int add_time = static_cast<int>(time / obj->time_continuity);
	for (int i = 0, j = 0; i < add_time;++i)
	{
		if (j + 1 < obj->time_relax.size() && i + 1 == obj->time_relax[j + 1].first) ++j;
		time += obj->time_relax[j].second;
	}
	return time;
}

double Race::Fun_(double distation, Air* obj)
{
	double kf{};
	register int j{};
	if (obj->type_kf == "discrete")
	{
		while (j + 1 < obj->kf_less.size())
		{
			//static int j{};
			if (distation >= obj->kf_less[j].first) ++j;
			else break;
		}

		obj->velocity *= (1+obj->kf_less[j].second/100);
		return distation / obj->velocity;
	}
	if (obj->type_kf == "integral")
	{
		//std::cout << kf_less[0].second * static_cast<int>(distation / kf_less[0].first)<<std::endl;
		obj->velocity *= (1 + (obj->kf_less[0].second * static_cast<int>(10100 / obj->kf_less[0].first)) / 100);
		return distation / obj->velocity;
	}
}



int Race::dist_(Surface* obj, int mesh)
{
	double dist_real{};
	double time = mesh * T_mesh;
	double time_real{};

	for (int i=0, j=0; time_real <= time; ++i)
	{
		if (time_real + obj->time_continuity <= time)
		{ 
			dist_real += obj->velocity * obj->time_continuity;
			time_real += obj->time_continuity;
		}
		else
		{
			dist_real += obj->velocity * (time-time_real);
			break;
		}

		if (j + 1 < obj->time_relax.size() && i + 1 == obj->time_relax[j + 1].first) ++j;
		time_real += obj->time_relax[j].second;
		
	}

	return static_cast<int>(dist_real/S_mesh);
}

int Race::dist_(Air* obj, int mesh) { return static_cast<int>(((mesh*T_mesh) * obj->velocity)/S_mesh); };


void Race::MinTime(double* t, size_t Q_race, Rendering* obj1)
{
	double buf{t[0]};
	for (size_t i = 1; i < Q_race; ++i)
	{
		if (t[i] < buf)
		{
			buf = t[i];
			winner = i;
		}
	}

	inf_T = buf;
	
	S_mesh = distation / obj1->getMesh();
	T_mesh = inf_T / obj1->getMesh();
}