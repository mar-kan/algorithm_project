//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <map>
#include <list>
#include "../general/ImageData.h"
#include "distance.h"
#include "../D/Centroid.h"

using namespace std;


class Bucket {                                  //represents a bucket of a hash table

    list<ImageData*>* bucketList;               //list of a bucket of the hash table

    Centroid * myCentroid;                      //represents the centroid of the bucket. is used only in qB

public:
    Bucket();
    ~Bucket();

    void InsertInBucket(ImageData*);

    list<ImageData *>*getBucketList() const;
    int getBucketListSize() const;
    Centroid *getMyCentroid() const;
    void setMyCentroid(Centroid *);
};


class HashTable {                               //represents a hash table with size[size]

    int size;
    Bucket ** table;

public:
    HashTable(int);
    ~HashTable();

    int InsertInTableLSH(ImageData*, long long unsigned);
    int InsertInTableCube(ImageData*, unsigned char *);
    int AssignInTableCluster(ImageData*);
    int HashNewEntry(long long unsigned);

    void BucketNNSearch(map<float, ImageData*> *, ImageData *, int, int, int);
    void BucketRangeSearch(map<float, ImageData*> *, ImageData *, int, int, float);

    int getSize() const;
    Bucket * getBucket(int) const;
};

#endif