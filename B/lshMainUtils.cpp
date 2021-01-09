//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include <sstream>
#include "lshMainUtils.h"

void checkArguments(LSH *lshT, LSH * lshN, int argc, char* argv[])                                   //checks program's command line arguments
{
    int num;

    //considers all inputs optional
    for (int i=1; i<argc; i+=2)
    {
        if (strcmp(argv[i], "-d") == 0)
        {
            lshT->setInputFile(argv[i+1]);
        }
        else if (strcmp(argv[i], "-i") == 0)
        {
            lshN->setInputFile(argv[i+1]);
        }
        else if (strcmp(argv[i], "-q") == 0)
        {
            lshT->setQueryFile(argv[i+1]);
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            lshN->setQueryFile(argv[i+1]);
        }
        else if (strcmp(argv[i], "-k") == 0)
        {
            assert(num = atoi(argv[i+1]));
            lshT->setK(num);
            lshT->reinitializeFamilyArray();          //reinitializes hash family array with new size k
            lshN->setK(num);
            lshN->reinitializeFamilyArray();          //reinitializes hash family array with new size k
        }
        else if (strcmp(argv[i], "-L") == 0)
        {
            assert(num = atoi(argv[i+1]));
            lshT->setL(num);
            lshT->reinitializeTableArray();           //reinitializes array of hash tables with new size L
            lshN->setL(num);
            lshN->reinitializeTableArray();           //reinitializes array of hash tables with new size L
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            lshT->setOutputFile(argv[i+1]);
            lshN->setOutputFile(argv[i+1]);
        }
        else
            errorExit(1, "Wrong argument", lshT, lshN, nullptr);
    }
}


void writeOutputQuery(LSH *lshN, LSH* lshT, NearestNeighbour *nnN, NearestNeighbour *nnT, ImageData * q_im)    //creates and writes a query in the output file
{
    FILE * fp = fopen((lshT->getOutputFile()).c_str(), "r+");                     //opens output file for writing
    if (!fp)
        fp = fopen(lshT->getOutputFile().c_str(), "w");

    //writes info for one query
    fprintf(fp, "Query: %d\n", q_im->getImageNumber());

    int i=0;
    fprintf(fp, "Nearest neighbor Reduced: %d\n", nnN->getNnResults()->begin()->second->getImageNumber());
    fprintf(fp, "Nearest neighbor LSH: %d\n", nnT->getNnResults()->begin()->second->getImageNumber());
    fprintf(fp, "Nearest neighbor True: %d\n", nnT->getNnResults()->begin()->second->getImageNumber());
    fprintf(fp, "distanceReduced: %f\n", nnN->getNnResults()->begin()->first);
    fprintf(fp, "distanceLSH: %f\n", nnT->getNnResults()->begin()->first);
    fprintf(fp, "distanceTrue: %f\n", nnT->getRealResults()->begin()->first);

    fclose(fp);
}


void writeOutputInfo(LSH * lsh, float tReduced, float tLSH, float tTrue, float afLSH, float afReduced) //prints rest data in output file
{
    FILE * fp = fopen((lsh->getOutputFile()).c_str(), "r+");                     //opens output file for writing

    fprintf(fp, "tReduced: %f\n", tReduced);
    fprintf(fp, "tLSH: %f\n",tLSH);
    fprintf(fp, "tTrue: %f\n", tTrue);
    fprintf(fp, "Approximation Factor LSH: %f\n",afLSH);
    fprintf(fp, "Approximation Factor Reduced: %f\n", afReduced);

    fclose(fp);
}


void clearFileNames(LSH * lsh)                                                          //clears all file names so if program runs again, it requests new ones
{
    lsh->setOutputFile("");
    lsh->setQueryFile("");
    lsh->setInputFile("");
}


void inputFileName(LSH * lsh, string type)                                              //sets a file name that the user inputs, depending on its type
{
    string path;

    cout << "Please input "<< type << " path" << endl;
    cin >> path;

    if (type == "dataset")
        lsh->setInputFile(path);
    else if (type == "query")
        lsh->setQueryFile(path);
    else if (type == "output")
        lsh->setOutputFile(path);
    else
        cout << "ERROR Wrong type" << endl;
}


void readInputFile(LSH * lsh, Dataset * dataset, string type)                       //reads input file and stores data read in the dataset
{
    ifstream in(lsh->getInputFile());

    //opens input file for input in binary form
    if(!in.is_open() || in.fail())
        errorExit(2, "Cannot open input file "+lsh->getInputFile(), lsh, nullptr, dataset);

    //reads input file
    int num;

    //reads and stores magic num in dataset
    in.read((char*)&num,sizeof(num));
    dataset->setMagicNumber(reverseInt(num));

    //reads and stores number of images in dataset
    in.read((char*)&num,sizeof(num));
    dataset->setNumOfImgs(reverseInt(num));

    //reads and stores num of rows in dataset
    in.read((char*)&num,sizeof(num));
    dataset->setRows(reverseInt(num));

    //reads and stores num of columns in dataset
    in.read((char*)&num,sizeof(num));
    dataset->setColumns(reverseInt(num));

    //reads and creates an object for every image
    for(int i=0;i<dataset->getNumOfImgs();i++)
    {
        //initializes new object for image
        auto * img = new ImageData(i, dataset->getRows(), dataset->getColumns());

        int count=0;
        //initialize array to store image to read
        for(int r=0;r<dataset->getRows();r++)
        {
            for(int c=0;c<dataset->getColumns();c++)
            {
                if (type == "true")
                {
                    unsigned char temp;
                    in.read((char*)&temp,sizeof(temp));
                    img->setImageBit(temp, count++);
                }
                else
                {
                    /** gets now 2 bits for each number **/
                    unsigned char temp1, temp2;
                    in.read((char*)&temp1,sizeof(temp1));
                    img->setImageBit(temp1, count++);
                    in.read((char*)&temp2,sizeof(temp2));
                    img->setImageBit(temp2, count++);
                }
            }
        }
        //inserts image in dataset image list
        dataset->insertImage(img);
    }

    //checks if file was read successfully
    if (!in.good() || in.fail())
        errorExit(3, "Error at reading input file", lsh, nullptr, dataset);

    in.close();              //closes file
}


void readQueryFile(LSH * lsh, Dataset * dataset, string type)                                        //reads query file and stores data read in the dataset
{
    //opens input file for input in binary form
    ifstream in(lsh->getQueryFile());
    if(!in.is_open() || in.fail())
        errorExit(4, "Cannot open query file", lsh, nullptr, dataset);


    //reads query file
    int num;

    //reads and stores magic num in dataset
    in.read((char*)&num,sizeof(num));
    dataset->setMagicNumber(reverseInt(num));

    //reads and stores number of images in dataset
    in.read((char*)&num,sizeof(num));
    dataset->setNumOfImgs(reverseInt(num));

    //reads and stores num of rows in dataset
    in.read((char*)&num,sizeof(num));
    dataset->setRows(reverseInt(num));

    //reads and stores num of columns in dataset
    in.read((char*)&num,sizeof(num));
    dataset->setColumns(reverseInt(num));

    //reads and creates an object for every image
    for(int i=0;i<dataset->getNumOfImgs();i++)
    {
        //initializes new object for image
        auto * img = new ImageData(i, dataset->getRows(), dataset->getColumns());

        int count=0;
        //initialize array to store image to read
        for(int r=0;r<dataset->getRows();r++)
        {
            for(int c=0;c<dataset->getColumns();c++)
            {
                unsigned char temp;
                in.read((char*)&temp,sizeof(temp));
                img->setImageBit(temp, count++);
            }
        }

        //inserts query image to query list of dataset
        dataset->insertQueryImage(img);
    }

    //checks if file was read successfully
    if (!in.good() || in.fail())
        errorExit(3, "Error at reading input file", lsh, nullptr, dataset);

    in.close();              //closes file
}