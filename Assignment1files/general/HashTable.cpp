//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "HashTable.h"


Bucket::Bucket()                                                //initializes empty bucket list
{
    bucketList = new list<ImageData*>();
    myCentroid = nullptr;
}


Bucket::~Bucket()                                               //deletes bucket list
{
    list<ImageData*>::iterator it;
    //for (it=bucketList->begin(); it!=bucketList->end(); it++)
        //delete (*it);

    delete bucketList;
    delete myCentroid;
}


void Bucket::InsertInBucket(ImageData *image)                   //creates new BucketEntry and inserts it in Bucket. creates new Bucket if needed.
{
    bucketList->push_back(image);
}


HashTable::HashTable(int s)                                     //initializes empty hash table with size = s
{
    size = s;
    table = new Bucket*[size];

    for (int i=0; i<size; i++)
        table[i] = new Bucket();                         //initializes new bucket if needed
}


HashTable::~HashTable()                                         //deletes whole hash table
{
    for (int i=0; i<size; i++)
        delete table[i];

    delete[] table;
}


int HashTable::InsertInTableLSH(ImageData *image, long long unsigned g) //inserts new image in hash table
{
    int hash_num = HashNewEntry(g);
    if (hash_num < 0)   //for the debugging
    {
        cout << "Invalid hash_num" << endl;
        return -1;
    }

    if (!table[hash_num])
        table[hash_num] = new Bucket();                         //initializes new bucket if needed

    table[hash_num]->InsertInBucket(image);                     //inserts in bucket

    return hash_num;                                            //returns position of bucket where image was inserted
}


int HashTable::InsertInTableCube(ImageData *image, unsigned char *f) //inserts new image in hash table
{
    int hash_num;
    if (f)
        hash_num = int(*f);
    else
        hash_num = random()%size;
                //hashes in bucket with vertex num = f
    if (hash_num < 0 || hash_num > size) //for debugging
    {
        cout << "problematic hash_num - f"<< endl;
        return -1;
    }

    if (!table[hash_num])
        table[hash_num] = new Bucket();                         //initializes new bucket if needed

    table[hash_num]->InsertInBucket(image);                     //inserts in bucket

    return hash_num;                                            //returns position of bucket where image was inserted
}


int HashTable::AssignInTableCluster(ImageData *image)
{
    /** assigns image to centroid with min l1 distance **/

    /*int min_dist = 100000;
    int pos=0, dist;
    for (int i=0; i<size; i++)
    {
        //if ((dist = table[i]->getMyCentroid()->getCentroid() - image->getImage()) < min_dist)
        {
            min_dist = dist;
            pos = i;
        }
    }
    table[pos]->InsertInBucket(image);
    return pos;*/
    return 0;
}


int HashTable::HashNewEntry(long long unsigned g)               //final hash with size of table
{
    return g % size;
}


void HashTable::BucketNNSearch(map<float, ImageData*> *images_found, ImageData *query_img, int pos, int L, int N) //executes ann algorithm in bucket
{
    float k_distance = 10000.0;  //stores max distance inserted in map
    int insertions=0;

    list<ImageData*>::iterator it;
    for (it=table[pos]->getBucketList()->begin(); it!=table[pos]->getBucketList()->end(); it++)     //traverses all entries of bucket
    {
        if ((*it)->getImageNumber() == query_img->getImageNumber()) //skips itself (it has been added in the bucket)
            continue;

        float distance = calculateManhattanDistance(query_img, *it);
        if (images_found->size() == (float)N)                              //if list 'full'
        {
            if (distance < k_distance)                              //deletes last element if this distance is better
                images_found->erase(N); //erases last element of map
            else
                continue;

            k_distance = distance;
        }
        images_found->insert(pair<float, ImageData*>(distance, *it)); //inserts in results' map
        insertions++;

        if (insertions/10 >= L)                             //function returns if it inserted much data
            return;
    }
}


void HashTable::BucketRangeSearch(map<float, ImageData*> *images_found, ImageData *query_img, int pos, int L, float R)   //executes range search algorithm in bucket
{
    int insertions=0;
    list<ImageData*>::iterator it;
    for (it=table[pos]->getBucketList()->begin(); it!=table[pos]->getBucketList()->end(); it++)     //traverses all entries of bucket
    {
        if ((*it)->getImageNumber() == query_img->getImageNumber()) //skips itself (it has been added in the bucket)
            continue;

        float distance = calculateManhattanDistance(query_img, *it);
        if (distance < R)
        {
            images_found->insert(pair<float, ImageData*>(distance, *it)); //inserts in results' map
            insertions++;
        }

        if (insertions/10 >= L)                             //function returns if it inserted much data
            return;
    }
}


/**setters and getters**/

int HashTable::getSize() const
{
    return size;
}


list<ImageData *>*Bucket::getBucketList() const
{
    return bucketList;
}


int Bucket::getBucketListSize() const
{
    return bucketList->size();
}


Centroid *Bucket::getMyCentroid() const
{
    return myCentroid;
}


void Bucket::setMyCentroid(Centroid *centroid)
{
    Bucket::myCentroid = myCentroid;
}


Bucket * HashTable::getBucket(int pos) const
{
    return table[pos];
}
