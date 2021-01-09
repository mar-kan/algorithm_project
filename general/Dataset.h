//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef DATA_H
#define DATA_H

#include <vector>
#include "ImageData.h"
#include "distance.h"

using namespace std;

class Dataset {                         //class Dataset includes all data read from the input file
                                        //including a list of all the images
    int magic_number;
    int num_of_imgs;
    int rows;
    int columns;

    vector<ImageData*> *images;           //vector that stores all images of the dataset
    vector<ImageData*> *query_list;       //stores images from query file

public:
    Dataset();
    ~Dataset();

    void insertImage(ImageData*);
    void insertQueryImage(ImageData*);

    float pickWLSH();
    float pickWCube();

    void setNumOfImgs(int numOfImgs);
    void setRows(int rows);
    void setColumns(int columns);
    void setMagicNumber(int magicNumber);

    int getNumOfImgs() const;
    int getRows() const;
    int getColumns() const;
    ImageData *getImagePos(int) const;
    ImageData *getQueryImagePos(int) const;
    int getQueryCount() const;
};


#endif
