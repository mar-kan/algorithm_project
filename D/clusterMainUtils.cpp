//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include <sstream>
#include "clusterMainUtils.h"
#include "Cluster.h"
#include "Lloyds.h"
#include "../B/LSH.h"
#include "../B/Hypercube.h"


void checkArguments(Cluster *cluster, int argc, char* argv[])                                   //checks program's command line arguments
{
    int num;

    //considers all inputs except complete mandatory
    if (argc < 9)
        errorExit(1, "Too few arguments", cluster, nullptr);

    for (int i=1; i<argc; i+=2)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            cluster->setInputFile(argv[i+1]);
        }
        else if (strcmp(argv[i], "-c") == 0)
        {
            cluster->setConfigFile(argv[i+1]);
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            cluster->setOutputFile(argv[i+1]);
        }
        else if (strcmp(argv[i], "-complete") == 0)
        {
            cluster->setComplete(true);
            i--;    //to move correctly in the next step, because loop increases i by 2
        }
        else if (strcmp(argv[i], "-m") == 0)
        {
            string method = argv[i+1];
            auto * algorithm = new Algorithm(cluster->getNumClusters());

            //sets method of algorithm
            if (method == "Classic" || method == "classic")
                algorithm->setMethod("Classic");
            else if (method == "LSH")
                algorithm->setMethod("LSH");
            else if (method == "Hypercube" || method == "hypercube")
                algorithm->setMethod("Hypercube");
            else
                errorExit(2, "Wrong method", cluster, nullptr);

            cluster->setAlgorithm(algorithm);
        }
        else
            errorExit(3, "Wrong argument", cluster, nullptr);
    }
}


void createOutputFile(Cluster *cluster)                                                     //creates and writes output file
{
    FILE * fp = fopen((cluster->getOutputFile()).c_str(), "w");                      //opens output file for writing

    //writes every info required

    fprintf(fp, "Algorithm: %s \n", cluster->getAlgorithm()->getMethod().c_str());

    for (int i=0; i<cluster->getNumClusters(); i++)
    {
        fprintf(fp, "CLUSTER-%d: \n",i+1); /*size: <int>, centroid: πίνακας με τις συντεταγμένες του centroid}*/
    }

    fprintf(fp, "clustering_time: \n"/*<double> seconds <<*/);
    fprintf(fp, "Silhouette: \n"/* [s1,...,si,...,sΚ, stotal] << */);
    /* si=average s(p) of points in cluster i, stotal=average s(p) of points in
dataset */

    /* Optionally with command line parameter –complete */
    if (cluster->isComplete())
        cluster->getAlgorithm()->printClustersToFile(fp);

    fclose(fp);
};


void readInputFile(Cluster * cluster, Dataset * dataset)                                //reads input file and stores data read in the dataset
{                                                                                       //and inserts every image read in all the hash tables
    //opens input file for reading
    ifstream in(cluster->getInputFile());
    if(!in.is_open() || in.fail())
        errorExit(4, "Cannot open input file", cluster, dataset);

    //reads input file
    int num;

    //reads and stores magic num in dataset
    in.read((char*)&num,sizeof(num));
    dataset->setMagicNumber(reverseInt(num));

    //reads and stores number of images in dataset
    in.read((char*)&num,sizeof(num));
    dataset->setNumOfImgs(reverseInt(num));

    //reads and stores num of rows in dataset
    in.read((char*)&num,sizeof(num));
    dataset->setRows(reverseInt(num));

    //reads and stores num of columns in dataset
    in.read((char*)&num,sizeof(num));
    dataset->setColumns(reverseInt(num));

    /**initializes centroids with k-means++**/
    cluster->getAlgorithm()->initialization(dataset->getColumns()*dataset->getRows());

    //reads and creates an object for every image
    for(int i=0;i<dataset->getNumOfImgs();i++)
    {
        //initializes new object for image
        auto * img = new ImageData(i, dataset->getRows(), dataset->getColumns());

        int count=0;
        //initialize array to store image to read
        for(int r=0;r<dataset->getRows();r++)
        {
            for(int c=0;c<dataset->getColumns();c++)
            {
                unsigned char temp;
                in.read((char*)&temp,sizeof(temp));
                img->setImageBit(temp, count++);
            }
        }

        //assigns image to its centroid (bucket)
        if (cluster->getAlgorithm()->getMethod() == "Classic")
        {
            Lloyds * lloyds = ((Lloyds*)cluster->getAlgorithm());
            lloyds->assignment(img);
        }
        else if (cluster->getAlgorithm()->getMethod() == "LSH")
        {
            LSH * lsh = ((LSH*)cluster->getAlgorithm());
            lsh->assignment(img);
        }
        else
        {
            Hypercube * cube = ((Hypercube*)cluster->getAlgorithm());
            cube->assignment(img);
        }
    }

    //checks if file was read successfully
    if (!in.good() || in.fail())
        errorExit(5, "Error at reading input file", cluster, dataset);

    in.close();              //closes input file
}


void readConfigFile(Cluster * cluster)
{
    /** had trouble reading conf file with the strings, so we used one with the ints values only**/

    //opens config file for reading
    ifstream in(cluster->getInputFile());
    if(!in.is_open() || in.fail())
        errorExit(6, "Cannot open config file", cluster, nullptr);

    //reads config file
    int num;
    string line,str;

    //reads and sets num of clusters in cluster and algorithm
    in.read((char*)&num,sizeof(num));
    cluster->setNumClusters(reverseInt(num));
    cluster->getAlgorithm()->setNumClusters(reverseInt(num));

    //reads and sets L in cluster
    in.read((char*)&num,sizeof(num));
    cluster->setL(reverseInt(num));

    //reads and sets K in cluster and lsh
    in.read((char*)&num,sizeof(num));
    cluster->setKLsh(reverseInt(num));
    ((LSH*)cluster->getAlgorithm())->setK(reverseInt(num));

    //reads and sets M in cluster and cube
    in.read((char*)&num,sizeof(num));
    cluster->setM(reverseInt(num));
    ((Hypercube*)cluster->getAlgorithm())->setM(num);

    //reads and sets L in cluster
    in.read((char*)&num,sizeof(num));
    cluster->setKCube(reverseInt(num));
    ((Hypercube*)cluster->getAlgorithm())->setK(num);

    //reads and sets probes in cluster and cube
    in.read((char*)&num,sizeof(num));
    cluster->setProbes(reverseInt(num));
    ((Hypercube*)cluster->getAlgorithm())->setProbes(num);

    //checks if file was read successfully
    if (!in.good() || in.fail())
        errorExit(7, "Error at reading config file", cluster, nullptr);

    in.close();              //closes file
}


void errorExit(int erno, string msg, Cluster *cluster, Dataset *dataset) //prints error message, frees memory and exits program
{
    cout << msg << endl;

    delete cluster;
    delete dataset;

    exit(erno);
}