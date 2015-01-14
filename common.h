
#ifndef MY_HEADER_H
#define MY_HEADER_H

#define pi 3.14159265358979323846

//Initial Definiton of the problem

#define MAX_CITIES 1000
#define MAX_DIST 500
#define MAX_TOUR (MAX_CITIES * MAX_DIST)
#define MAX_ANTS 32

//Ant algorithm problem parameters

#define ALPHA 1.0
#define BETA 5.0 //This parameter raises the weight of distance over pheromone
#define RHO 0.5 //Evapouration rate
#define QVAL 100
#define MAX_TOURS 10
#define MAX_TIME (MAX_TOURS * MAX_CITIES)
#define INIT_PHER (1.0/MAX_CITIES)

//runtime Structures and global variables

struct cityType {
    int    id, plz;
    double lat, lon;
    char   name[100];
};

struct antType {
    int curCity, nextCity, pathIndex;
    int tabu[MAX_CITIES];
    int path[MAX_CITIES];
    double tourLength;
};

extern cityType cities[MAX_CITIES];
extern antType ants[MAX_ANTS];

extern double dist[MAX_CITIES][MAX_CITIES];
extern double phero[MAX_CITIES][MAX_CITIES];

extern double best;
extern int bestIndex;


double deg2rad(double deg);
double rad2deg(double rad);
double distance(double lat1, double lon1, double lat2, double lon2, char unit);
void init();
void restartAnts();
double antProduct(int from, int to);
int selectNextCity(int ant);
int simulateAnts();
void updateTrails();
void emitDataFile(int bestIndex);


#endif