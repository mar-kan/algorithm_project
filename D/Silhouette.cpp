//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "Silhouette.h"


Silhouette::Silhouette()
{
    silhouette = -1;
}


Silhouette::~Silhouette()
{
    //nothing to do
}


void Silhouette::CalculateSilhouette(HashTable * table)
{
    float a,b,s=0.0, s_bucket=0.0;

    for(int i=0;i<=table->getSize(); i++)
    {
        //A distance of i to objects in same cluster
        //for(int j=0;j<table[i].getBucket()->;j++)
        {
            //a = calculateManhattanDistance() ;

            //B distance of i to near best neighbour cluster
            if(a>b)
                s += 1-(a/b) ;
            else if(a==b)
                s += 0 ;
            else
                s += (b/a)-1 ;
        }
    }
    //calculates average sillhouette
    silhouette = s / float(table->getSize()) ;
}