//Ant algorithms for Travelling salesman Problem

#include <stdio.h>
#include "common.h"
#include <complex>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <iomanip>
#include <omp.h>

using namespace std;

int simulateSharedAnts() {
    int k;
    int moving = 0;

    #pragma omp parallel for \
            reduction(+: moving)
    for (k = 0; k < MAX_ANTS; k++) {
        //checking if there are any more cities to visit
        if (ants[k].pathIndex < MAX_CITIES) {
            ants[k].nextCity = selectNextCity(k);
            ants[k].tabu[ants[k].nextCity] = 1;
            ants[k].path[ants[k].pathIndex++] = ants[k].nextCity;

            ants[k].tourLength += dist[ants[k].curCity][ants[k].nextCity];

            //handle last case->last city to first
            if (ants[k].pathIndex == MAX_CITIES) {
                ants[k].tourLength += dist[ants[k].path[MAX_CITIES - 1]][ants[k].path[0]];
            }

            ants[k].curCity = ants[k].nextCity;
            moving++;
        }
    }

    return moving;
}

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

    omp_set_num_threads( 8 );

    while (curTime++ < MAX_TIME) {
        if (simulateSharedAnts() == 0) {
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