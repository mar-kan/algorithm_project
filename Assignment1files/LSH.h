//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef LSH_H
#define LSH_H

#include <cstdio>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <map>
#include "general/HashTable.h"
#include "Algorithm.h"
#include "LSHashFunction.h"
#include "general/functions.h"

using namespace std;

class LSH: public Algorithm {                       //class stores all inputs and values needed for the LSH algorithm to run and the hash tables

    //all values inputed by user
    string input_file, query_file, output_file;
    int k, L, N, w;
    float R;

    HashTable ** hashTables;                        //array that contains all L hash tables
    LSHashFunction **hashFamily;                    //array that contains all hash functions

    int num_clusters; //qB

public:
    LSH();     //constructor for question A
    LSH(int);  //constructor for question B
    ~LSH();

    void reinitializeTableArray();
    void reinitializeFamilyArray();

    void initializeHashFamily(int);
    void initializeHashTables(int);
    void insertToAllHashTables(Dataset*);

    void FindNNN(map<float, ImageData*> *, ImageData*);
    void RangeSearch(map<float, ImageData*> *, ImageData*);

    void addCentroidToBucket(Centroid*, int);
    void assignment(ImageData*);

    void setInputFile(const string &inputFile);
    void setOutputFile(const string &outputFile);
    void setQueryFile(const string &queryFile);
    void setR(float r);
    void setN(int n);
    void setL(int l);
    void setK(int k);
    void setW(int W);

    const string &getInputFile() const;
    const string &getOutputFile() const;
    const string &getQueryFile() const;
    float getR() const;
    int getN() const;
    int getL() const;
    int getK() const;
    int getW() const;
};


#endif
