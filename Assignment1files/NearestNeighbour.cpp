//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "NearestNeighbour.h"


NearestNeighbour::NearestNeighbour(int n)
{
    nnResults = new map<float, ImageData*>();
    rangeResults = new map<float, ImageData*>();
    realResults = new map<float, ImageData*>();

    secs_real = 0;
    secs_ann = 0;
}


NearestNeighbour::~NearestNeighbour()
{
    delete nnResults;
    delete rangeResults;
    delete realResults;
}


void NearestNeighbour::ExactNNN(Algorithm* algo, string method, ImageData *query_img, Dataset *dataset) //executes exact nearest neighbor for query_img. stores results in realResults
{                                                                                 //also computes real time
    const clock_t begin_time = clock();
    int insertions=0;

    float k_distance = 1000.0;  //stores max distance inserted in map
    for (int i=0; i<dataset->getNumOfImgs(); i++)                       //traverses dataset's vector with all the images
    {
        float distance = calculateManhattanDistance(query_img, dataset->getImagePos(i));
        if (distance < k_distance)
        {
            realResults->insert(pair<float, ImageData*>(distance, dataset->getImagePos(i)));
            insertions++;
        }
        if (distance > k_distance)
            k_distance = distance;
    }
    secs_real = float(clock() - begin_time) / CLOCKS_PER_SEC;
}


void NearestNeighbour::ApproximateNNN(Algorithm* algo, string method, ImageData *query_img)  //executes approximate nearest neighbor for query_img. stores results in NN
{                                                                      //also calculates ann time
    const clock_t begin_time = clock();

    if (method == "LSH")
        ((LSH*)algo)->FindNNN(nnResults, query_img);
    else
        ((Hypercube*)algo)->FindNNN(nnResults, query_img);

    secs_ann = float(clock() - begin_time) / CLOCKS_PER_SEC;
}


/*void NearestNeighbour::RangeSearch(Algorithm* algo, string method, ImageData *query_img) //executes range search for query_img. stores results in rangeResults
{
    if (method == "LSH")
        ((LSH*)algo)->RangeSearch(rangeResults, query_img);
    else
        ((Hypercube*)algo)->RangeSearch(rangeResults, query_img);
}*/


/** setters and getters **/
map<float, ImageData *> * NearestNeighbour::getNnResults() const
{
    return nnResults;
}


map<float, ImageData *> * NearestNeighbour::getRangeResults() const
{
    return rangeResults;
}


float NearestNeighbour::getSecsAnn() const
{
    return secs_ann;
}


float NearestNeighbour::getSecsReal() const
{
    return secs_real;
}


void NearestNeighbour::setSecsAnn(float secsAnn)
{
    secs_ann = secsAnn;
}


map<float, ImageData *> *NearestNeighbour::getRealResults() const {
    return realResults;
}
