//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef PROJECT_SILHOUETTE_H
#define PROJECT_SILHOUETTE_H

#include "general/HashTable.h"
#include "general/distance.h"
#include "general/ImageData.h"


class Silhouette {
    float silhouette;

public:
    Silhouette();
    ~Silhouette();

    void CalculateSilhouette(HashTable*);
};


#endif
