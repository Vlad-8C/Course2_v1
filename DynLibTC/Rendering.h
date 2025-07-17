#ifndef RENDERING_H
#define RENDERING_H

#include "TC.h"

class DYNLIBTC_API Rendering
{
private:
	//COORD pos{};
	size_t QuantytyRiders{};
	int time{}, Q_mesh{};
public:
	Rendering(HANDLE console, size_t QRiders) : QuantytyRiders{QRiders}, time{ 10 }
	{
		COORD maxWindow = GetLargestConsoleWindowSize(console); // размер самого большого возможного консольного окна
		COORD bufferSize = { maxWindow.X, 50 };
		SetConsoleScreenBufferSize(console, bufferSize);
		SMALL_RECT windowSize = { 0, 0, maxWindow.X-1, 49 };
		SetConsoleWindowInfo(console, TRUE, &windowSize);
		Q_mesh = maxWindow.X-1;
	};

	int getMesh() { return Q_mesh; }

//	Rendering(int x_, int y_, int time_);
	
	void paint_go(HANDLE console, TC* tc[], Race race);

	void Frace();
};

#endif
