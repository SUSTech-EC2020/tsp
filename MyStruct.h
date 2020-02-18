#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
using namespace std;

#ifdef _WIN32
#include <hash_map>
#else
#include <unordered_map>
using namespace std;
#define hash_map unordered_map
#endif

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

#ifdef _WIN32
#define MKDIR(a) _mkdir((a))
#else
#define MKDIR(a) mkdir((a),0777)
#endif


typedef struct Vertice
{
	int idx;
	double x;
	double y;
}Vertice;

typedef struct TSP
{
	int nbVertices;
	double totalTCost; //total cost of the tasks
	Vertice *vertices/*[VNUM]*/;
}TSP;

typedef struct Individual
{
	// TODO
}Individual;