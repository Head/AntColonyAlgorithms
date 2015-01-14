//Ant algorithms for Travelling salesman Problem

#include <stdio.h>
#include "common.h"
#include <mpi.h>
#include <complex>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv) {

    cout << "S-ACO:";
    cout << "MaxTime=" << MAX_TIME << endl;

    srand(time(NULL));

    int    myid, numprocs, namelen;
    char   processor_name[MPI_MAX_PROCESSOR_NAME];
    double startwtime = 0.0, endwtime;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Get_processor_name(processor_name,&namelen);

    fprintf(stdout,"Process %d of %d is on %s\n", myid, numprocs, processor_name);
    fflush(stdout);

    if (myid == 0)
        startwtime = MPI_Wtime();

    init();

    int curTime = myid;
    while (curTime < MAX_TIME) {
        curTime+=numprocs;
        if (simulateAnts() == 0) {
            updateTrails();

            MPI_Bcast( &phero, MAX_CITIES*MAX_CITIES, MPI_DOUBLE, 0, MPI_COMM_WORLD);
            MPI_Bcast( &best, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

            if (curTime != MAX_TIME)
                restartAnts();

            cout << "\nProcess " << myid << " time is " << curTime << " (" << best << " km)";
        }
    }


    if (myid == 0) {
        endwtime = MPI_Wtime();
        printf("\nWall clock time = %.8f seconds.\n", (endwtime-startwtime) );
        fflush(stdout);

        cout << "\nSACO: Best tour = " << best << " km" << endl << endl << endl;
        antType antBest;
        antBest = ants[bestIndex];
        for (int i = 0; i < MAX_CITIES; i++) {
            cout << cities[antBest.path[i]].name << " > ";
        }

        emitDataFile(bestIndex);
    }

    MPI_Finalize();

    return 0;
}