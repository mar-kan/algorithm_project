//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef CLUSTER_H
#define CLUSTER_H

#include <string>
#include <cstdio>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include "Algorithm.h"

using namespace std;

class Cluster {

    string input_file, output_file, config_file;
    int num_clusters, L, k_lsh, k_cube, M, probes;
    bool complete;
    Algorithm * algorithm;

public:
    Cluster();
    ~Cluster();

    void I();

    void setInputFile(const string &inputFile);
    void setOutputFile(const string &outputFile);
    void setAlgorithm(Algorithm *algorithm);
    void setL(int l);
    void setProbes(int probes);
    void setM(int m);
    void setKCube(int kCube);
    void setKLsh(int kLsh);
    void setKMedians(int kMedians);
    void setConfigFile(const string &configFile);
    void setComplete(bool complete);
    void setNumClusters(int numClusters);

    const string &getInputFile() const;
    const string &getOutputFile() const;
    int getNumClusters() const;
    int getL() const;
    const string &getConfigFile() const;
    bool isComplete() const;
    Algorithm *getAlgorithm() const;
};


#endif
