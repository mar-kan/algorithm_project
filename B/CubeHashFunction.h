//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef CUBEHASHFUNCTION_H
#define CUBEHASHFUNCTION_H

#include <random>
#include <vector>
#include <map>
#include "../general/ImageData.h"
#include "../general/functions.h"
#include "LSHashFunction.h"

using namespace std;

class CubeHashFunction: public LSHashFunction {

    int d;                  //represents dimension and number of Si numbers
    int M, w, k;            //variables for the hashing
    long m;

    vector<float> *s;       //vector that includes floats Si for a hash function
    map<long long unsigned, char> *coin;  //map that stores paris of <h, 0 or 1>

public:
    CubeHashFunction(float W, int dim, int K);
    ~CubeHashFunction();

    unsigned char * HashCoin(ImageData*);
};


#endif
