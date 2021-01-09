//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "distance.h"
#include "functions.h"

#include <iostream>
using namespace std;
int calculateManhattanDistance(ImageData *im1, ImageData *im2)          //returns L1 distance of 2 images
{
    int dist=0;
    for (int i=0; i<im1->getDimension(); i++)
    {
        if (im1->getImage()[i] > im2->getImage()[i])
            dist |= im1->getImage()[i] - im2->getImage()[i];
        else
            dist |= im2->getImage()[i] - im1->getImage()[i];
    }
    return dist;
}


int calculateHammingDistance(ImageData *im1, ImageData *im2)
{
    int dist=0;
    for (int i=0; i<im1->getDimension(); i++)       // checks each bit of the 2 images separately
    {
        if ((im1->getImage()[i] ^ im2->getImage()[i]) != 0) //if its different increments distance
            dist++;
    }
    return dist;
}


int calculateEuclidianDistance(ImageData *i1, ImageData *i2)          //returns L2 distance of 2 images
{
    float dist = 0.0;
    for (int i=0; i<i1->getDimension(); i++)
    {
        //dist += (i1->getImagePos(i) - i2->getImagePos(i))^2;
    }
    return dist;
}