#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>  
#include <vector>


#include "TC.h"
#include "Race.h"
#include "Rendering.h"


//Rendering::Rendering(int x_, int y_, int time_) : x{ x_ }, y{ y_ }, time{ time_ } {};

//void Rendering::paint_go(HANDLE console)
void Rendering::Frace()
{
    std::cout << "1.Верблюд" << std::endl;
    std::cout << "2.Верблюд - быстроход" << std::endl;
    std::cout << "3.Кентавр" << std::endl;
    std::cout << "4.Ботинки - вездеходы" << std::endl;
    std::cout << "5.Ковёр - самолёт" << std::endl;
    std::cout << "6.Орёл" << std::endl;
    std::cout << "7.Метла" << std::endl;
    std::cout << "0.Закончить регистрацию" << std::endl;
    std::cout << "Выберите транспорт или 0 для окончания процесса регистрации: " << std::endl;
}


void Rendering::paint_go(HANDLE console, TC* tc[], Race race)
{
    COORD* pos = new COORD[QuantytyRiders + 1];
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(console, &csbi)) pos[0] = csbi.dwCursorPosition;
    else std::cerr << "Error screen cirsor " << std::endl;

    for (int i = 1; i <= QuantytyRiders; ++i)
    {
        pos[i]={0,0};
        pos[i].Y = pos[0].Y + i;
    }

    SetConsoleCursorPosition(console, pos[0]);
    for (int k = 0;k < Q_mesh;++k) {
        std::cout << "-";
    }

    pos[0].Y += QuantytyRiders+1;
    SetConsoleCursorPosition(console, pos[0]);
    for (int k = 0;k < Q_mesh;++k) {
        std::cout << "-";
    }
    
    
    for (int i = 0; i < Q_mesh; ++i)
    {
        
        for (size_t r = 0; r < QuantytyRiders; ++r)
        {
            pos[r+1].X = (tc[r]->Dist(race, i)) % Q_mesh;
            SetConsoleCursorPosition(console, pos[r+1]);
            std::cout << "\x1b[2K";
            std::cout << "*";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(time));

    }
    pos[0].X = 0;
    pos[0].Y += 1;
    SetConsoleCursorPosition(console, pos[0]);

    delete[] pos;
}