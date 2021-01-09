//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "CubeHashFunction.h"

CubeHashFunction::CubeHashFunction(float W, int dim, int K): LSHashFunction(W, dim, K)  //initializes s vector with randomly distributed floats between [0, w]
{
    d = dim;
    M = 2^(32/K);
    m = 4294967291;  //2^32 - 5;
    w = W;
    k = K;

    //uniformly distributed float generator
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, w);          //generates numbers between [0, w]

    //initializes vector and fills it with d Si uniformly distributed floats
    s = new vector<float>();
    coin = new map<long long unsigned, char>();

    for (int i=0; i<d; i++)
    {
        s->push_back(dis(gen));
    }
}


CubeHashFunction::~CubeHashFunction()
{
    delete s;
    delete coin;
}


unsigned char* CubeHashFunction::HashCoin(ImageData *image)  //hashes an image through k*d hash functions chosen randomly from the hash family
{                                                  //returns result g for one hash table

    unsigned char *f = nullptr;                    //builds hash num here

    long long unsigned *h;                         /**builds h(p) = ( a(d−1) + m·a(d−2) + ··· + m(d−1)· a0 ) modM  for each h **/
    for (int i=0; i<k; i++)
        h[k]=0;

    for (int i=0; i<k; i++)                        //hashes image k times
    {
        //calculates h for each hashing
        for (int j=0; j<d; j++)
        {
            //float a = float((image->getImage()[d-j-1] - s->at(d-j-1))) / float(w);  /** calculate all a(j) = ( p(j)-s(j) )/w starting by the end**/

            //h[i] += modular(int(a), m^j, M);       //adds everytime to h[i]: res = ( a * m^j ) % M
        }

        //h[i] = int(h[i]) % M; //final h(i)

        /**maps h[i] to 0 or 1**/
        /*if (coin->find(h[i]) != coin->end())       // if h already mapped, gets its value
            f[i] = coin->at(h[i]);
        else
        {
            //uniformly distributed int generator
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dis(0, 1);          //generates 0 or 1

            f[i] = dis(gen);                                     //maps it randomly

            //coin->insert(pair<long long int, char>(h[i], f[i])); //inserts new pair in map*/
        //}
    }
    return f;
}