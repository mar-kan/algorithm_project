//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef HYPERCUBE_H
#define HYPERCUBE_H

#include <cstdio>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include "general/HashTable.h"
#include "Algorithm.h"
#include "CubeHashFunction.h"

using namespace std;

class Hypercube: public Algorithm  {

    string input_file, query_file, output_file;
    int k, M, N, probes;
    float R, w;

    int num_clusters; //B

    HashTable * hashTable;
    CubeHashFunction **hashFamily;                    //array that contains all hash functions

public:
    Hypercube();        //constructor for question A
    Hypercube(int);     //constructor for qB
    ~Hypercube();

    void reinitializeFamilyArray();
    void initializeHashFamily(int);

    void initializeHashTable(int);
    void insertInHashTable(Dataset*);

    void FindNNN(map<float, ImageData*> *, ImageData*);
    void RangeSearch(map<float, ImageData*> *, ImageData*);

    void addCentroidToBucket(Centroid*, int);
    void assignment(ImageData*);

    void setInputFile(const string &inputFile);
    void setOutputFile(const string &outputFile);
    void setQueryFile(const string &queryFile);
    void setR(float r);
    void setN(int n);
    void setM(int m);
    void setK(int k);
    void setProbes(int probes);
    void setW(float W);

    const string &getInputFile() const;
    const string &getOutputFile() const;
    const string &getQueryFile() const;
    float getR() const;
    int getN() const;
    int getM() const;
    int getK() const;
    int getProbes() const;
    float getW() const;
};


#endif
