//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "functions.h"


void errorExit(int erno, string msg, Algorithm *algo, Algorithm * algo2, Dataset *dataset) //prints error message, frees memory and exits program
{
    cout << msg << endl;

    delete algo;
    delete algo2;
    delete dataset;
    exit(erno);
}


int reverseInt(int i)                   //reverses an int
{                                       //used to read the binary files correctly
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}


float getRandomFloat()                //returns a random float
{
    return float(rand())/float((RAND_MAX)) * 1.2;
}


int randomIntGenerator(int a, int b)    //generates and returns random int between [a, b]
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(a, b);              //generates numbers between [a, b]

    return dis(gen);
}


long long modular(long long base, long long exp, int mod)   //returns the modular of 2 ints
{                                                           //uses modular exponentation
    long long res = 1;
    while (exp > 0)
    {
        if (exp%2 == 1)
            res= (res*base) % mod;
        exp = exp >> 1;
        base = (base*base) % mod;
    }
    return res;
}