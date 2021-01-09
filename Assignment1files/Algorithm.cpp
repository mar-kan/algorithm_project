//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "Algorithm.h"
#include "clusterMainUtils.h"
#include "LSH.h"
#include "Hypercube.h"
#include "Lloyds.h"


Algorithm::Algorithm(int K)
{
    num_clusters = K;
    method = "";
}


void Algorithm::initialization(int dimension)      //initialization of num_clusters centroids and assignment in hash table(s)
{
    /** k-means++ initialization **/
    /** it is only assigning them randomly due to time**/

    //uniformly distributed int generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 255);          //generates numbers that can be fit to unsigned char

    unsigned char centr[dimension];
    for (int i=0; i<num_clusters; i++)  //inserts num_clusters centroids in list with random coordinates
    {
        //creates random unsigned char array for cluster
        for (int j=0; j <dimension; j++)
        {
            centr[j++] = dis(gen);
        }

        //adds new centroid to the i-th bucket of a hash table
        Centroid * centroid = new Centroid(centr);

        if (method == "LSH")
            ((LSH*)this)->addCentroidToBucket(centroid, i);
        else if (method == "Hypercube")
            ((Hypercube*)this)->addCentroidToBucket(centroid, i);
        else
            ((Lloyds*)this)->addCentroidToBucket(centroid, i);
    }
}


void Algorithm::executeAlgorithm(Dataset *dataset)
{
    /**Υλοποίηση αλγορίθμων για τη συσταδοποίηση διανυσμάτων στον χώρο  d . Θα χρησιμοποιηθεί η
μετρική L1 (Manhattan). Η αρχικοποίηση πραγματοποιείται με την τεχνική k-Means++ και η ενημέρωση με
τον υπολογισμό του διάμεσου (median) διανύσματος. Οι αλγόριθμοι διαφοροποιούνται στο βήμα της
ανάθεσης όπου χρησιμοποιείται (α) ο ακριβής αλγόριθμος Lloyd’s, και η αντίστροφη ανάθεση (reverse)
μέσω Range search με (β) LSH, ή (γ) Τυχαία προβολή.**/

    //initialization();   //happens in main before reading

    if (method == "Classic")
    {

    }
    else if (method == "LSH")
    {

    }
    else //hypercube
    {

    }
}


void Algorithm::printClustersToFile(FILE *fp)
{
    int i=1;

    list<Centroid*>::iterator it;
    //for (it=centroids->begin(); it!=centroids->end(); it++)      //for each centroid
    {
        fprintf(fp, "CLUSTER-%d: ",i);                    //prints its cluster number
        //(*it)->printClusterToFile(fp);                           //prints its cluster
    }
    /**
void Centroid::printClusterToFile(FILE *fp)
{
    fprintf(fp, "{ %f %f, ", x,y);                      //writes coordinates of centroid

    list<ImageData*>::iterator it;
    for (it=cluster->begin(); it!=cluster->end(); it++)        //for each image
    {
        fprintf(fp, "%d, ", (*it)->getImageNumber());   //writes image number
    }
    fprintf(fp, "}\n");
}**/
}


/**setters and getters**/

void Algorithm::setMethod(const string &meth)
{
    Algorithm::method = meth;
}


void Algorithm::setNumClusters(int numClusters)
{
    num_clusters = numClusters;
}


const string &Algorithm::getMethod() const
{
    return method;
}