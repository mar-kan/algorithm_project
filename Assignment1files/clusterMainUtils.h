//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef CLUSTERMAINUTILS_H
#define CLUSTERMAINUTILS_H

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
#include "Cluster.h"
#include "general/Dataset.h"
#include "general/functions.h"
using namespace std;


void checkArguments(Cluster *,int, char*[]);
void createOutputFile(Cluster *);
void inputFileName(Cluster *, string);
void readInputFile(Cluster *, Dataset *);
void readConfigFile(Cluster *);

void errorExit(int, string, Cluster*, Dataset*);      //different here because cluster does not represent an algorithm

#endif
