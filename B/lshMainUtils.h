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
#include "../Assignment1files/LSH.h"
#include "../Assignment1files/general/Dataset.h"
#include "../Assignment1files/general/functions.h"
#include "../Assignment1files/NearestNeighbour.h"

using namespace std;


void checkArguments(LSH *, LSH*, int, char*[]);
void clearFileNames(LSH *);
void inputFileName(LSH *, string);
void readInputFile(LSH *, Dataset *, string);
void readQueryFile(LSH *, Dataset *, string);

/** printOutputFile function was split in 2 new functions **/
void writeOutputQuery(LSH *, LSH*, NearestNeighbour *, NearestNeighbour*, ImageData*);
void writeOutputInfo(LSH * lsh, float tReduced, float tLSH, float tTrue, float afLSH, float afReduced);


#endif
