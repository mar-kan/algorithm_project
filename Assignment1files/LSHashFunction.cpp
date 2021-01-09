//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "LSHashFunction.h"


LSHashFunction::LSHashFunction(float W, int dim, int K)  //initializes s vector with randomly distributed floats between [0, w]
{
    d = dim;
    M = 2^(32/K);
    m = 4294967291;  //2^32 - 5;
    w = int(W);
    k = K;

    //uniformly distributed float generator
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, w);          //generates numbers between [0, w]

    //initializes vector and fills it with d Si uniformly distributed floats
    s = new vector<float>();
    for (int i=0; i<d; i++)
    {
        s->push_back(dis(gen));
    }
}


LSHashFunction::~LSHashFunction()
{
    s->clear();
    delete s;
}


long long unsigned LSHashFunction::Hash(ImageData *image)   //hashes an image through k*d hash functions chosen randomly from the hash family
{                                                  //returns result g for one hash table

    long long unsigned h[k];                       /**builds h(p) = ( a(d−1) + m·a(d−2) + ··· + m(d−1)· a0 ) modM  for each h **/
    for (int i=0; i<k; i++)
        h[k]=0;

    for (int i=0; i<k; i++)                        //hashes image k times
    {
        //calculates h for each hashing
        for (int j=0; j<d; j++)
        {
            float a = float((image->getImage()[d-j-1] - s->at(d-j-1))) / float(w);  /** calculate all a(j) = ( p(j)-s(j) )/w starting by the end**/

            h[i] += modular(int(a), m^j, M);       //adds everytime to h[i]: res = ( a * m^j ) % M
        }

        h[i] = int(h[i]) % M; //final h(i)
    }

    /** calculates amplified function result g and returns it**/
    long long unsigned g=0;
    for (int i=1; i<k; i++)
    {
        if (g==0)
            g = h[i];
        else
            g = g << 8 | h[i];
    }
    return g;
}