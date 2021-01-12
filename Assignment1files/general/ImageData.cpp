//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "ImageData.h"


ImageData::ImageData(int num, int row, int col)
{
    image_number = num;
    dimension = row*col;
    g = -1;

    //image initialized here and set later
    image = new vector<unsigned char>(dimension);
}


ImageData::~ImageData()
{
    //delete image;
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
    ImageData::image->at(pos) = bit;
}


vector<unsigned char> *ImageData::getImage() const
{
    return image;
}


void ImageData::setDimension(int dim)
{
    this->dimension = dim;
}


