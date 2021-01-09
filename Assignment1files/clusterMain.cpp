//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "general/HashTable.h"
#include "clusterMainUtils.h"
#include "Cluster.h"
#include "LSH.h"
#include "Hypercube.h"
#include "Lloyds.h"

using namespace std;


int main(int argc, char * argv[])
{
    cout << "Running Clustering program" << endl;

    srand(time(NULL));

    string answer, path;
    auto * cluster = new Cluster();
    
    checkArguments(cluster, argc, argv);                //checks program arguments

    //initializes suitable method's hash table(s)
    if (cluster->getAlgorithm()->getMethod() == "LSH")
    {
        LSH * lsh = (LSH*)cluster->getAlgorithm();
        lsh->initializeHashTables(cluster->getNumClusters());
        lsh->initializeHashFamily(cluster->getNumClusters());
    }
    else if (cluster->getAlgorithm()->getMethod() == "Hypercube")
    {
        Hypercube * cube = (Hypercube*)cluster->getAlgorithm();
        cube->initializeHashTable(cluster->getNumClusters());
        cube->initializeHashFamily(cluster->getNumClusters());
    }
    //no need for else. Lloyds' hash table is initialized in its constructor

    auto *dataset = new Dataset();                      //initializes dataset
    readInputFile(cluster, dataset);                    //reads input file and inserts data in clusters
    readConfigFile(cluster);                            //reads config file and updates values of cluster

    cluster->getAlgorithm()->executeAlgorithm(dataset); //algorithm execution
    createOutputFile(cluster);                          //writes output file

    //frees reserved memory
    delete dataset;
    delete cluster;

    cout << endl << "Exiting" << endl;
    exit(0);
}