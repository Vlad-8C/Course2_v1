#ifndef RACE_H
#define RACE_H


class Rendering;

class DYNLIBTC_API Race
{
private:
public:
	double distation{};
	double S_mesh{};
	double T_mesh{};
	double inf_T{};
	int winner{};

public:
	Race()=default;
	Race(double d) :distation{ d } {};
	//Race(int ) : ;

	//Нужна функция минимального времени
	static double Fun_(double distation, Surface*);

	static double Fun_(double distation, Air*);

	void MinTime(double* t, size_t Q_race, Rendering* obj1);



		//return 0;
		//double time = distation / velocity;

	int dist_(Surface*, int);

	int dist_(Air*, int);


};

#endif