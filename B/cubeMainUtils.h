//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef CUBEMAINUTILS_H
#define CUBEMAINUTILS_H

#include <cstdio>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <string>
#include <bitset>
#include "Hypercube.h"
#include "NearestNeighbour.h"

using namespace std;


void checkArguments(Hypercube *, int, char*[]);
void createOutputFile(Hypercube *, NearestNeighbour *, ImageData*);
void clearFileNames(Hypercube *);
void inputFileName(Hypercube *, string);
void readInputFile(Hypercube *, Dataset *);
void readQueryFile(Hypercube *, Dataset *);

#endif
