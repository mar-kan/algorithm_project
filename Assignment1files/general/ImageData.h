//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <cstdlib>
#include <iostream>

class ImageData {                           //class stores one image's data

    int image_number;                       //unique number for each image, assigned when the image is read
    int dimension;                          //size of vector of image
    long long unsigned g;                   //result of g hash family before final mod with size of table

    unsigned char image[28*28];             //array of size dimension that stores each pixel of the image as a vector
                                            //couldn't pass unsigned char dynamically for some reason so we did it statically
public:
    ImageData(int, int, int);
    ~ImageData();

    int getImageNumber() const;
    int getDimension() const;
    unsigned char * getImage() const;
    long long unsigned getG() const;
    void setG(long long unsigned);
    void setImageBit(unsigned char, int);

};


#endif