//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "ImageData.h"


ImageData::ImageData(string img, int num, int row, int col)
{
    image_number = num;
    dimension = row*col;
    g = -1;

    //image set later
}


ImageData::~ImageData()
{
    //nothing to delete manually
}


/**setters and getters**/

int ImageData::getImageNumber() const
{
    return image_number;
}

int ImageData::getDimension() const
{
    return dimension;
}


unsigned char * ImageData::getImage() const
{
    return (unsigned char *)(image);
}


long long unsigned ImageData::getG() const
{
    return g;
}


void ImageData::setG(long long unsigned G)
{
    ImageData::g = G;
}


void ImageData::setImageBit(unsigned char bit, int pos)
{
    ImageData::image[pos] = bit;
}

