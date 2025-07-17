#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <windows.h>  



#include "TC.h"
#include "Rendering.h"
#include "Race.h"



namespace dist
{
    double time{};
    std::vector<std::pair<size_t, double>> relax_{};
    enum tipy { camel, camel_speed_run, centaur, boot_jeep, carpet_airplane, orel, broom };
}

namespace race
{
    std::vector<int> race{};
    char repid{ 'y' };
}

int main()
{
    setlocale(LC_ALL, "Russian");
    double distation{};
    //int dist = 1000;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    Rendering paint1{ console, 0};

    int Q_add_time{};
    size_t Q_rice{ };


    ///=============================Init rice===========================///
    //+++++++++++++++++++++++++init surface object+++++++++++++++++++++++//
    dist::relax_.push_back({ 1,5 });
    dist::relax_.push_back({ 2,8 });
    Surface camel{ 10,"Верблюд", 30, dist::relax_ };
    dist::relax_ = {};
    dist::relax_.push_back({ 1,5 });
    dist::relax_.push_back({ 2,6.5 });
    dist::relax_.push_back({ 3,8 });
    Surface camel_speed_run{ 40,"Верблюд - быстроход", 10, dist::relax_ };
    dist::relax_ = {};
    dist::relax_.push_back({ 1,2 });
    Surface centaur{ 15,"Кентавр", 8, dist::relax_ };
    dist::relax_ = {};
    dist::relax_.push_back({ 1,10 });
    dist::relax_.push_back({ 2,5 });
    Surface boot_jeep{ 6,"Ботинки - вездеходы", 60, dist::relax_ };

    //+++++++++++++++++++++++++init fly object+++++++++++++++++++++++//
    dist::relax_ = {};
    dist::relax_.push_back({ 1000,0 });
    dist::relax_.push_back({ 5000,3 });
    dist::relax_.push_back({ 10000,10 });
    dist::relax_.push_back({ 10000,5 });
    Air carpet_airplane{ 10,"Ковер - самолет", dist::relax_, "discrete" };
    dist::relax_ = {};
    dist::relax_.push_back({ 0,6 });
    Air orel{ 8, "Орел", dist::relax_, "discrete" };
    dist::relax_ = {};
    dist::relax_.push_back({ 1000,1 });
    Air broom{ 8, "Метла",dist::relax_, "integral" };

    TC* race[7] = { nullptr };
    ///==========================End init rice========================///



    while (race::repid == 'y')
    {
        system("cls");

        std::cout << "Укажите длины дистанции (должна быть положительной) "; std::cin >> distation;
        std::cout << "Введите кол-во участников: "; std::cin >> Q_rice;

        paint1.Frace(); // Rice name

        for (size_t k = 0; k < Q_rice;++k)
        {
            int buf{};
            std::cout << "Введите тип гонщика " << k << ": "; std::cin >> buf;
            if (buf == 0) break;
            switch (buf)
            {
            case 1:
                race[k] = &camel;
                break;
            case 2:
                race[k] = &camel_speed_run;
                break;
            case 3:
                race[k] = &centaur;
                break;
            case 4:
                race[k] = &boot_jeep;
                break;
            case 5:
                race[k] = &carpet_airplane;
                break;
            case 6:
                race[k] = &orel;
                break;
            case 7:
                race[k] = &broom;
                break;
            case 0:
            default:
                std::cout << "Введен невозможный гонщик, повторите попытку" << std::endl;
                --k;
                break;
            }
        }

        ///=======================Selected riders=================///
        std::cout << "Races: ";
        for (const auto& race_ : race)
        {
            if (race_ == nullptr) break;
            std::cout << race_->name << ", ";
        }
        std::cout << ";\n";



        double* t = new double [Q_rice] {};   // Arr time distance travel

        for (size_t k = 0; k < Q_rice; ++k)
        {
            t[k] = race[k]->Time(distation);   // Time of each rider
        }

        Race r1{ distation };

        Rendering paint1{ console, Q_rice };


        r1.MinTime(t, Q_rice, &paint1);


        paint1.paint_go(console, race, r1);     //drawing the race


        ///=====================Output of race information==============///
        std::cout << "Winner: " << race[r1.winner]->name << std::endl;
        std::cout << "\nTime: " << std::endl;
        for (size_t k = 0; k < Q_rice; ++k)
        {
            std::cout << race[k]->name << ": " << t[k] << std::endl;
        }

        std::cout << "Провести еще одну гонку? (y/n) "; std::cin >> race::repid;
        //++curs;
        delete[] t;
    }
    std::cout << "Bay bay" << std::endl;
    
    return EXIT_SUCCESS;
}
