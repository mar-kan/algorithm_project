//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include <time.h>
#include <iostream>
#include "Dataset.h"


Dataset::Dataset()                              //initializes the 2 vectors. parameters set later while reading input file
{
    //values set later when input file is read
    magic_number = -1;
    num_of_imgs = -1;
    rows = -1;
    columns = -1;

    //initialize list of images
    images = new vector<ImageData*>;            //stores all images of dataset
    query_list = new vector<ImageData*>;        //stores all images of queryset
}


Dataset::~Dataset()                             //deletes the 2 vectors
{
    vector<ImageData*>::iterator it;

    for (it=images->begin(); it!=images->end(); it++)
        delete (*it);
    for (it=query_list->begin(); it!=query_list->end(); it++)
        delete (*it);

    delete images;
    delete query_list;
}


void Dataset::insertImage(ImageData *image)     //inserts an image in dataset vector
{
    images->push_back(image);
}


void Dataset::insertQueryImage(ImageData *image) //inserts an image in queryset vector
{
    query_list->push_back(image);
}


float Dataset::pickWLSH()                        //picks best W for LSH algorithm by calculating mean manhattan distance of some images with the whole the dataset
{
    float sum= 0.0;
    int i,j;

    for(i=0;i<100;i++)
    {
        ImageData * img = images->at(random() % images->size());

        for (j=0; j<num_of_imgs; j++)                    //checks distance with each other image left in dataset
        {
            if (img->getImageNumber() == images->at(j)->getImageNumber())
                continue;

            sum += calculateManhattanDistance(img, images->at(j));
        }
    }

    return 4*(sum / float(num_of_imgs));
}


float Dataset::pickWCube()                      //picks best W for Hypercube algorithm by calculating mean manhattan distance of some images with the whole the dataset
{
    float sum= 0.0;
    int i,j;

    for(i=0;i<100;i++)
    {
        ImageData * img = images->at(random() % images->size());

        for (j=0; j<num_of_imgs; j++)                                      //checks distance with each other image in dataset
        {
            if (img->getImageNumber() == images->at(j)->getImageNumber())  //skips self
                continue;

            sum += calculateManhattanDistance(img, images->at(j));
        }
    }

    return 4*(sum / float(num_of_imgs));
}


/**getters and setters**/
void Dataset::setNumOfImgs(int numOfImgs)
{
    num_of_imgs = numOfImgs;
}


void Dataset::setRows(int row)
{
    Dataset::rows = row;
}


void Dataset::setColumns(int cols)
{
    Dataset::columns = cols;
}


void Dataset::setMagicNumber(int magicNumber)
{
    magic_number = magicNumber;
}


int Dataset::getNumOfImgs() const
{
    return num_of_imgs;
}


int Dataset::getRows() const
{
    return rows;
}


int Dataset::getColumns() const
{
    return columns;
}


ImageData* Dataset::getImagePos(int pos) const
{
    return images->at(pos);
}


ImageData* Dataset::getQueryImagePos(int pos) const
{
    return query_list->at(pos);
}


int Dataset::getQueryCount() const
{
    return query_list->size();
}
