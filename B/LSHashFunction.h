//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef LSHASHFUNCTION_H
#define LSHASHFUNCTION_H

#include <random>
#include <vector>
#include "../general/ImageData.h"
#include "../general/functions.h"
using namespace std;

class LSHashFunction {

    int d;                  //represents dimension and number of Si numbers
    int M, w, k;            //variables for the hashing
    long m;

    vector<float> *s;       //vector that includes floats Si for a hash function

public:
    LSHashFunction(float, int, int);
    ~LSHashFunction();

    long long unsigned Hash(ImageData*);
};


#endif
