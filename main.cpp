#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include "Utils.h"
#include "MyStruct.h"

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

#define PRINT_RSLT 1

char inputPath[100] = "./instances";
char tspFiles[10][100] =
{
  "wi29",
  "dj38",
  "qa194",
  };

// Setting by default
int timeBudget = 30; // time budget in seconds
int beginIdx = 0;
int endIdx = 0;
int nbTrials = 1;
char resPath[100] = "./res";

int main(int argc, char* argv[])
{
    // Read arguments
    string _argValue;
    if(Utils::getStrArgValue(argc, argv, "timeBudget", _argValue))
    {
        timeBudget = stoi(_argValue);
    }
    if(Utils::getStrArgValue(argc, argv, "begin_index", _argValue))
    {   
        beginIdx = stoi(_argValue);
    }
    if(Utils::getStrArgValue(argc, argv, "end_index", _argValue))
    {   
        endIdx = stoi(_argValue);
    }
    if(Utils::getStrArgValue(argc, argv, "run_times", _argValue))
    {   
        nbTrials = stoi(_argValue);
    }
    if(Utils::getStrArgValue(argc, argv, "res_path", _argValue))
    {   
        strcpy(resPath, _argValue.c_str());
    }

    for (int inst = beginIdx; inst <= endIdx; inst++)//for each instance
    {
        char filename[100];
        strcpy(filename, inputPath);
        strcat(filename, "/");
        strcat(filename, tspFiles[inst]);
        strcat(filename, ".tsp");
        
        strcat(resPath, "/");
        MKDIR(resPath);
        strcat(resPath, tspFiles[inst]);
        strcat(resPath, "/");
        #ifdef PRINT_RSLT
        cout << "Input filename is " << filename << endl;
        cout << "Output results folder is " << resPath << endl;
        #endif

        // Read input instances
        fstream fin;
        fin.open(filename, ios::in|ios::binary);
        if (!fin)
        {
            cout << "Can't open file " << filename  << endl;
            exit(0);
        }
        TSP tsp;
        char dummyString[200];
        int dummyInt;
        double dummyDouble[2];
        fin.getline(dummyString, 200);
        int lineNum = 0;
        while(!fin.eof())
        {
            fin >> dummyString;
            if (strcmp(dummyString, "DIMENSION")==0)
            {
                fin >> dummyString;
                fin >> tsp.nbVertices;
            } 
            else if (strcmp(dummyString, "NODE_COORD_SECTION")==0)
            {
                tsp.vertices = new Vertice[tsp.nbVertices];
                for (int i=0; i<tsp.nbVertices; i++)
                {
                    fin.getline(dummyString, 100);
                    fin >> dummyString;
                    fin >> tsp.vertices[i].x;
                    fin >> tsp.vertices[i].y;
                }
            }
            else
            {
                continue;
            }
        }
        fin.close();
        #ifdef PRINT_RSLT
        cout << "Input instance: " << tspFiles[inst] << " of " << tsp.nbVertices << "cities, coordinates are:" << endl;
        for (int i=0; i<=tsp.nbVertices; i++)
        {
                cout << tsp.vertices[i].x << " " << tsp.vertices[i].y << endl;
        }
        #endif
        #ifdef PRINT_RSLT
        cout << "solving instance: " << tspFiles[inst] << endl;
        #endif

        int genCounter;
        double totalTime;
        double duration;
        double avgGenTime;
        clock_t beginTime;
        for (int r = 1; r <= nbTrials; r++)
        {
            totalTime = 0;
            duration = 0;
            avgGenTime = 0;
            beginTime = clock();
            for (int iter = 0; /*iter < MAXITERATIONS*/; iter++)
            {
                // TODO your algorithm



                // Timing
                clock_t currTime = clock();
                duration = (double)(currTime - beginTime) / (double) CLOCKS_PER_SEC;
                double avgGenTime = duration / (double) iter;
                if (duration>timeBudget || (timeBudget-duration)<avgGenTime)
                {
                    // TODO record results: 
                    // time, iteration number, solution(s), fitness value(s), obj value(s)
                    totalTime += duration;
                    break;
                }
            }
        }

    }
    return 0;
}
       
