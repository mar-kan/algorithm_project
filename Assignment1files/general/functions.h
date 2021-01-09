//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/**includes general functions used by all the programs**/

#include <string>
#include <random>
#include "../Algorithm.h"

using namespace std;


void errorExit(int, string, Algorithm*, Algorithm*, Dataset*);
int reverseInt(int);
float getRandomFloat();
int randomIntGenerator(int, int);
long long modular(long long, long long, int);

#endif
