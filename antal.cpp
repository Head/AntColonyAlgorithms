//Ant algorithms for Travelling salesman Problem

#include <stdio.h>
#include "common.h"
#include <complex>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <iomanip>

using namespace std;

int main() {
    int curTime = 0;

    cout << "S-ACO:";
    cout << "MaxTime=" << MAX_TIME << endl;

    srand(time(NULL));

    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();

    init();

    std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
    std::chrono::microseconds microRunTime
            = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    double runTime = microRunTime.count() / 1000000.0;

    std::cout << std::setprecision( 8 )
            << "Init clock time = " << runTime << " seconds."
            << std::endl << std::flush;

    startTime = std::chrono::system_clock::now();

    while (curTime++ < MAX_TIME) {
        if (simulateAnts() == 0) {
            updateTrails();

            if (curTime != MAX_TIME)
                restartAnts();

            cout << "\n Time is " << curTime << " (" << best << " km)";
        }
    }

    endTime = std::chrono::system_clock::now();
    microRunTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    runTime = microRunTime.count() / 1000000.0;

    std::cout << std::setprecision( 8 ) << endl
            << "Wall clock time = " << runTime << " seconds."
            << std::endl << std::flush;

    cout << "\nSACO: Best tour = " << best << " km" << endl << endl << endl;
    antType antBest;
    antBest = ants[bestIndex];
    for (int i = 0; i < MAX_CITIES; i++) {
        cout << cities[antBest.path[i]].name << " > ";
    }

    emitDataFile(bestIndex);

    return 0;
}