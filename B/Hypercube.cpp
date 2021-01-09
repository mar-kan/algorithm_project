//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "Hypercube.h"


Hypercube::Hypercube(): Algorithm(-1)           //uses -1 for question A bc Algorithm is used for qB
{
    input_file = "";
    output_file = "";
    query_file = "";

    //k, L, N, R initialized to their default values
    k = 4;
    M = 5;
    probes = 2;
    N = 1;
    R = 1.0;

    //hash table is initialized later, when the size of the dataset is known

    //array initialized with default k size
    hashFamily = new CubeHashFunction*[k];
}


Hypercube::Hypercube(int K): Algorithm(K)
{
    num_clusters = K;

    //k, L, N, R initialized to their default values
    k = 4;
    M = 5;
    probes = 2;
    N = 1;
    R = 1.0;

    //hash table is initialized later, when the size of the dataset is known

    //array initialized with default k size
    hashFamily = new CubeHashFunction*[k];
}


Hypercube::~Hypercube()
{
    delete hashTable;
    delete[] hashFamily;
}


void Hypercube::reinitializeFamilyArray()              //deletes hash family array and initializes a new one with the new 'k' as its size
{
    delete[] hashFamily;
    hashFamily = new CubeHashFunction*[k];
}


void Hypercube::initializeHashFamily(int dim)         //initializes each hash function included in array
{
    for (int i=0; i<k; i++)
    {
        hashFamily[i] = new CubeHashFunction(w, dim, k);
    }
}


void Hypercube::initializeHashTable(int size)        //initializes hash table with size given
{
    hashTable = new HashTable(size);
}


void Hypercube::insertInHashTable(Dataset *dataset)   //inserts all images of vector in dataset in the L hashtables
{
    for (int i=0; i<dataset->getNumOfImgs(); i++)     //for each image
    {
        ImageData * image = dataset->getImagePos(i);

        //chooses random hash family
        int hf = randomIntGenerator(0, k);

        //hashes image and stores g
        unsigned char *f = hashFamily[hf]->HashCoin(image);
        //image->setG(g); hypercube doesnt need to save g

        //inserts image in hash table
        hashTable->InsertInTableCube(image, f);
    }
}


void Hypercube::FindNNN(map<float, ImageData*> *images_found, ImageData * query_img) //finds N nearest neighbours of query_img and inserts them in images_found vector
{
     /** inserts query image in hash table **/

     //chooses random hash family
     int hf = randomIntGenerator(0, k);

     //hashes query image and its stores g
     unsigned char * f = hashFamily[hf]->HashCoin(query_img);

     //insertion
     int bucket_pos = hashTable->InsertInTableCube(query_img, f);

     /** checks every item in that bucket **/
     hashTable->BucketNNSearch(images_found, query_img, bucket_pos, M, N);

     /** checks probes nearest buckets **/
     int descend = bucket_pos-1, ascend = bucket_pos+1, i=0;
     while (i < probes)
     {
         if (descend > 0)
         {
             hashTable->BucketNNSearch(images_found, query_img, descend, M, N);
            i++;
         }
         if (ascend < hashTable->getSize())
         {
             hashTable->BucketNNSearch(images_found, query_img, ascend, M, N);
             i++;
         }
         descend++;
         ascend++;
     }
}


void Hypercube::RangeSearch(map<float, ImageData*> *images_found, ImageData * query_img)
{

    /** inserts query image in each table **/
    //chooses random hash family
    int hf = randomIntGenerator(0, k);

    //hashes query image and its stores g
    unsigned char * f = hashFamily[hf]->HashCoin(query_img);

    //insertion
    int bucket_pos = hashTable->InsertInTableCube(query_img, f);

    /** checks every item in that bucket **/
    hashTable->BucketRangeSearch(images_found, query_img, bucket_pos, M, R);

    /** checks probes nearest buckets **/
    int descend = bucket_pos-1, ascend = bucket_pos+1, i=0;
    while (i < probes)
    {
        if (descend > 0)
        {
            hashTable->BucketRangeSearch(images_found, query_img, descend, M, R);
            i++;
        }
        if (ascend < hashTable->getSize())
        {
            hashTable->BucketRangeSearch(images_found, query_img, ascend, M, R);
            i++;
        }
        descend++;
        ascend++;
    }

}


void Hypercube::addCentroidToBucket(Centroid * centroid, int buck_pos)  //adds centroid to pos-th bucket of hash ta
{
    hashTable->getBucket(buck_pos)->setMyCentroid(centroid);
}


void Hypercube::assignment(ImageData *image)          //assigns image to hash table
{
    hashTable->AssignInTableCluster(image);
}


/**getters and setters**/

void Hypercube::setInputFile(const string &inputFile)
{
    input_file = inputFile;
}

void Hypercube::setQueryFile(const string &queryFile)
{
    query_file = queryFile;
}

void Hypercube::setOutputFile(const string &outputFile)
{
    output_file = outputFile;
}

void Hypercube::setK(int k)
{
    Hypercube::k = k;
}

void Hypercube::setM(int m)
{
    M = m;
}

void Hypercube::setN(int n)
{
    N = n;
}

void Hypercube::setR(float r)
{
    R = r;
}

void Hypercube::setProbes(int probes)
{
    Hypercube::probes = probes;
}

void Hypercube::setW(float W)
{
    w = W;
}

int Hypercube::getK() const
{
    return k;
}

int Hypercube::getM() const
{
    return M;
}

int Hypercube::getN() const
{
    return N;
}

float Hypercube::getR() const
{
    return R;
}

const string &Hypercube::getInputFile() const
{
    return input_file;
}

const string &Hypercube::getQueryFile() const
{
    return query_file;
}

const string &Hypercube::getOutputFile() const
{
    return output_file;
}


int Hypercube::getProbes() const
{
    return probes;
}

float Hypercube::getW() const
{
    return w;
}
