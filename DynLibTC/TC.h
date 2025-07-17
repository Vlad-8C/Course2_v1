#ifndef TC_H
#define TC_H



#ifdef DYNLIBTC_EXPORTS
#define DYNLIBTC_API __declspec(dllexport)
#else
#define DYNLIBTC_API __declspec(dllimport)
#endif



class DYNLIBTC_API Race;

class DYNLIBTC_API TC
{
protected:
public:
	double velocity{};
	std::string name{};
public:
	TC()=default;
	TC(double v, std::string name_) :velocity{ v }, name{ name_ } {};
	virtual double Time(double distation)=0;
	virtual int Dist(Race r1, int)=0;

};

class DYNLIBTC_API Surface :virtual public TC
{
protected:
public:
	size_t time_continuity{};
	std::vector<std::pair<size_t,double>> time_relax{};
public:
	Surface(double v, std::string name_, size_t t, std::vector<std::pair<size_t, double>> r);
	friend class Race;
	
	double Time(double distation);
	int Dist(Race r1, int);

};


class DYNLIBTC_API Air : virtual public TC
{
protected:
public:
	std::vector<std::pair<size_t, double>> kf_less{};
	std::string type_kf{};
public:
	Air(double v, std::string name_, std::vector<std::pair<size_t, double>> kf, std::string type);

	double Time(double distation);

	int Dist(Race r1,int);
	friend class Race;
};


#endif