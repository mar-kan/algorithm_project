//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "LSH.h"


LSH::LSH():Algorithm(-1)                               //constructor for qA. uses -1 for question A bc class Algorithm is used for qB
{                                                      //initializes all essential parameters for lsh for NN
    input_file = "";
    output_file = "";
    query_file = "";

    //k, L, N, R initialized to their default values
    k = 4;
    L = 5;
    N = 1;
    R = 1.0;

    w=-1;   //w is set later, after reading input file

    //array initialized with default L size
    hashTables = new HashTable*[L];

    //array initialized with default k size
    hashFamily = new LSHashFunction*[k];
}


LSH::LSH(int K): Algorithm(K)                          //constructor for qB
{                                                      //initializes all essential parameters for lsh for clustering
    num_clusters = K;

    //k, L, N, R initialized to their default values
    k = 4;
    L = 5;
    N = 1;
    R = 1.0;

    w=-1;

    //array initialized with default L size
    hashTables = new HashTable*[L];

    //array initialized with default k size
    hashFamily = new LSHashFunction*[k];
}


LSH::~LSH()                                     //destroys with object dynamically allocated arrays
{
    for (int i=0; i<L; i++)
        delete hashTables[i];

    for (int i=0; i<k; i++)
        delete hashFamily[i];

    delete[] hashTables;
    delete[] hashFamily;
}


void LSH::initializeHashFamily(int dim)         //initializes each hash function included in array
{
    for (int i=0; i<k; i++)
    {
        hashFamily[i] = new LSHashFunction(w, dim, k);
    }
}


void LSH::reinitializeTableArray()              //deletes hash table array and initializes a new one with the new 'L' as its size
{
    delete[] hashTables;
    hashTables = new HashTable*[L];
}


void LSH::reinitializeFamilyArray()              //deletes hash family array and initializes a new one with the new 'k' as its size
{
    delete[] hashFamily;
    hashFamily = new LSHashFunction*[k];
}


void LSH::initializeHashTables(int size)        //initializes L hash tables in hashTables array with inputed size
{
    for (int i=0; i<L; i++)
    {
        hashTables[i] = new HashTable(size);
    }
}


void LSH::insertToAllHashTables(Dataset *dataset)   //inserts all images of vector in dataset in the L hashtables
{
    for (int i=0; i<dataset->getNumOfImgs(); i++)   //for each image
    {
        ImageData * image = dataset->getImagePos(i);

        for (int j=0; j<L; j++)                     //for each hash table
        {
            //chooses random hash family
            int hf = randomIntGenerator(0, k);

            //hashes image and stores g
            long long unsigned g = hashFamily[hf]->Hash(image);
            image->setG(g);

            //inserts image in j-th hash table
            hashTables[j]->InsertInTableLSH(image, g);
        }
    }
}


void LSH::FindNNN(map<float, ImageData*> *images_found, ImageData * query_img) //finds N nearest neighbours of query_img and inserts them in images_found vector
{
    for (int i=0; i<L; i++)                         //for each hash table
    {
        /** inserts query image in each table **/
        //chooses random hash family
        int hf = randomIntGenerator(0, k);

        //hashes query image and its stores g
        long long unsigned g = hashFamily[hf]->Hash(query_img);
        query_img->setG(g);

        //insertion
        int bucket_pos = hashTables[i]->InsertInTableLSH(query_img, g);

        /** checks every item in that bucket **/
        hashTables[i]->BucketNNSearch(images_found, query_img, bucket_pos, L, N);
    }
}


void LSH::RangeSearch(map<float, ImageData*> *images_found, ImageData * query_img)
{
    for (int i=0; i<L; i++)                         //for each hash table
    {
        /** inserts query image in each table **/
        //chooses random hash family
        int hf = randomIntGenerator(0, k);

        //hashes query image and its stores g
        long long unsigned g = hashFamily[hf]->Hash(query_img);
        query_img->setG(g);

        //insertion
        int bucket_pos = hashTables[i]->InsertInTableLSH(query_img, g);

        /** checks every item in that bucket **/
        hashTables[i]->BucketRangeSearch(images_found, query_img, bucket_pos, L, R);
    }
}


/** Question B **/
void LSH::addCentroidToBucket(Centroid * centroid, int buck_pos)
{
    //adds centroid to all LSH hash tables

    for (int i=0; i<L; i++)
        hashTables[i]->getBucket(buck_pos)->setMyCentroid(centroid);
}


void LSH::assignment(ImageData *image)          //assigns image to all L hash tables
{
    for (int i=0; i<L; i++)
    {
        hashTables[i]->AssignInTableCluster(image);
    }
}


/**getters and setters**/

void LSH::setInputFile(const string &inputFile)
{
    input_file = inputFile;
}

void LSH::setQueryFile(const string &queryFile)
{
    query_file = queryFile;
}

void LSH::setOutputFile(const string &outputFile)
{
    output_file = outputFile;
}

void LSH::setK(int K)
{
    LSH::k = K;
}

void LSH::setL(int l)
{
    L = l;
}

void LSH::setN(int n)
{
    N = n;
}

void LSH::setR(float r)
{
    R = r;
}

void LSH::setW(int W)
{
    w = W;
}

int LSH::getK() const
{
    return k;
}

int LSH::getL() const
{
    return L;
}

int LSH::getN() const
{
    return N;
}

float LSH::getR() const
{
    return R;
}

const string &LSH::getInputFile() const
{
    return input_file;
}

const string &LSH::getQueryFile() const
{
    return query_file;
}

const string &LSH::getOutputFile() const
{
    return output_file;
}

int LSH::getW() const
{
    return w;
}