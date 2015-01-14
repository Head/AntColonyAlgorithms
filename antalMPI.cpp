//Ant algorithms for Travelling salesman Problem

#include <stdio.h>
#include "common.h"
#include <mpi.h>
#include <complex>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

double best2;
double phero2[MAX_CITIES][MAX_CITIES];

int main(int argc, char** argv) {

    cout << "S-ACO:";
    cout << "MaxTime=" << MAX_TIME << endl;

    srand(time(NULL));

    int    myid, numprocs, namelen, pred, succ;
    char   processor_name[MPI_MAX_PROCESSOR_NAME];
    double startwtime = 0.0, endwtime;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Get_processor_name(processor_name,&namelen);
    MPI_Status    status;

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

            if (curTime != MAX_TIME)
                restartAnts();

            cout << "\nProcess " << myid << " time is " << curTime << " (" << best << " km)";
            if(best != MAX_TOUR) {
                succ=(myid+1)%(numprocs);
                pred=(myid+numprocs-1)%(numprocs);

                MPI_Sendrecv( &phero, MAX_CITIES*MAX_CITIES, MPI_DOUBLE, succ, 99,
                        &phero2, MAX_CITIES*MAX_CITIES, MPI_DOUBLE, pred, MPI_ANY_TAG,
                        MPI_COMM_WORLD, &status);
                MPI_Sendrecv( &best, 1, MPI_DOUBLE, succ, 98,
                        &best2, 1, MPI_DOUBLE, pred, MPI_ANY_TAG,
                        MPI_COMM_WORLD, &status);
                cout << best2 << " - " << best << endl;
                if(best2<best) {
                    best = best2;
                    cout << myid << " got phero from " << pred << endl;
                    memcpy(&phero, phero2, sizeof(phero));
                }
            }


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