//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef NEARESTNEIGHBOUR_H
#define NEARESTNEIGHBOUR_H

#include <map>
#include "../general/ImageData.h"
#include "LSH.h"
#include "Hypercube.h"

using namespace std;


class NearestNeighbour {

    map<float, ImageData*> * nnResults;                       //map that stores an image data object and its distance with the query image. stores all nearest neighbours
    map<float, ImageData*> * rangeResults;                    //same as above. stores all range search result images
    map<float, ImageData*> * realResults;                     //same as above. stores all exact nn result images

    float secs_ann, secs_real;

public:
    NearestNeighbour(int);
    ~NearestNeighbour();

    void ExactNNN(Algorithm*, string, ImageData*, Dataset*);
    void ApproximateNNN(Algorithm*, string, ImageData*);
    void RangeSearch(Algorithm*, string, ImageData*);

    map<float, ImageData *> *getNnResults() const;
    map<float, ImageData *> *getRangeResults() const;

    float getSecsAnn() const;
    float getSecsReal() const;

    void setSecsAnn(float secsAnn);

    map<float, ImageData *> *getRealResults() const;
};


#endif
