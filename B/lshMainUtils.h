//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef LSHFUNCTIONS_H
#define LSHFUNCTIONS_H

#include <cstdio>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <string>
#include <cerrno>
#include <bitset>
#include "LSH.h"
#include "../general/Dataset.h"
#include "../general/functions.h"
#include "NearestNeighbour.h"
using namespace std;


void checkArguments(LSH *, LSH*, int, char*[]);
void writeOutputQuery(LSH *, NearestNeighbour *, ImageData*, string);
void clearFileNames(LSH *);
void inputFileName(LSH *, string);
void readInputFile(LSH *, Dataset *, string);
void readQueryFile(LSH *, Dataset *, string);
void writeOutputInfo(LSH * lsh, float tReduced, float tLSH, float tTrue, float afLSH, float afReduced);

#endif
