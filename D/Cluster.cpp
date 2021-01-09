//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "Cluster.h"


Cluster::Cluster()
{
    input_file = "";
    output_file = "";

    algorithm = new Algorithm(-1);
    complete = false;

    //k, L, N, R initialized to their default values
    num_clusters = -1;
    L = 3;
    k_lsh = 4;
    M = 10;
    k_cube = 3;
    probes = 2;
}


Cluster::~Cluster()
{
    delete algorithm;
}


/**getters and setters**/

void Cluster::setInputFile(const string &inputFile)
{
    input_file = inputFile;
}


void Cluster::setOutputFile(const string &outputFile)
{
    output_file = outputFile;
}

void Cluster::setL(int l)
{
    L = l;
}


int Cluster::getL() const
{
    return L;
}


const string &Cluster::getInputFile() const
{
    return input_file;
}


const string &Cluster::getOutputFile() const
{
    return output_file;
}


void Cluster::setKMedians(int kMedians)
{
    num_clusters = kMedians;
}


void Cluster::setKLsh(int kLsh)
{
    k_lsh = kLsh;
}


void Cluster::setKCube(int kCube)
{
    k_cube = kCube;
}


void Cluster::setM(int m)
{
    M = m;
}


void Cluster::setProbes(int probe)
{
    Cluster::probes = probe;
}


void Cluster::setConfigFile(const string &configFile)
{
    config_file = configFile;
}


void Cluster::setComplete(bool comp)
{
    Cluster::complete = comp;
}


const string &Cluster::getConfigFile() const
{
    return config_file;
}

void Cluster::setAlgorithm(Algorithm *algo)
{
    Cluster::algorithm = algo;
}


bool Cluster::isComplete() const
{
    return complete;
}


Algorithm *Cluster::getAlgorithm() const
{
    return algorithm;
}


int Cluster::getNumClusters() const
{
    return num_clusters;
}


void Cluster::setNumClusters(int numClusters)
{
    num_clusters = numClusters;
}
