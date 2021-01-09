//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "cubeMainUtils.h"
#include "lshMainUtils.h"


void checkArguments(Hypercube *cube, int argc, char* argv[])                                   //checks program's command line arguments
{
    int num;

    //considers all inputs optional
    for (int i=1; i<argc; i+=2)
    {
        if (strcmp(argv[i], "-d") == 0)
        {
            cube->setInputFile(argv[i+1]);
        }
        else if (strcmp(argv[i], "-q") == 0)
        {
            cube->setQueryFile(argv[i+1]);
        }
        else if (strcmp(argv[i], "-k") == 0)
        {
            assert(num = atoi(argv[i+1]));
            cube->setK(num);
            cube->reinitializeFamilyArray();        //if k changes, resizes hash family array
        }
        else if (strcmp(argv[i], "-M") == 0)
        {
            assert(num = atoi(argv[i+1]));
            cube->setM(num);
        }
        else if (strcmp(argv[i], "-probes") == 0)
        {
            assert(num = atoi(argv[i+1]));
            cube->setProbes(num);
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            cube->setOutputFile(argv[i+1]);
        }
        else if (strcmp(argv[i], "-N") == 0)
        {
            assert(num = atoi(argv[i+1]));
            cube->setN(num);
        }
        else if (strcmp(argv[i], "-R") == 0)
        {
            float r;
            assert(r = atof(argv[i+1]));
            cube->setR(r);
        }
        else
            errorExit(1, "Wrong argument", cube, nullptr);
    }
}


void createOutputFile(Hypercube *cube, NearestNeighbour *nn, ImageData * q_im)   //creates and writes output file
{
    FILE * fp = fopen((cube->getOutputFile()).c_str(), "w");              //opens output file for writing

    //writes every info required
    fprintf(fp, "Query: %d\n", q_im->getImageNumber());

    int i=0;
    map<float, ImageData*>::iterator it;
    for (it=nn->getRealResults()->begin(); it!=nn->getRealResults()->end(); it++)
    {
        if (i == cube->getN()-1) //outputs only N neighbours
            break;

        fprintf(fp, "Nearest neighbor-%d: %d\n",++i, it->second->getImageNumber());
        fprintf(fp, "distanceHypercube: %f\n", it->first);
        fprintf(fp, "distanceTrue: %f\n", nn->getRangeResults()->begin()->first);
    }
    fprintf(fp, "Hypercube: %f\n", nn->getSecsReal());
    fprintf(fp, "tTrue: %f\n", nn->getSecsReal());

    fprintf(fp, "R-near neighbors: \n");
    for (it=nn->getRangeResults()->begin(); it!=nn->getRangeResults()->end(); it++)
    {
        fprintf(fp, "%d\n", it->second->getImageNumber());
    }
    fprintf(fp, "\n");
    fclose(fp);
};


void clearFileNames(Hypercube * cube)                                                          //clears all file names so if program runs again, it requests new ones
{
    cube->setOutputFile("");
    cube->setQueryFile("");
    cube->setInputFile("");
}


void inputFileName(Hypercube * cube, string type)                                              //sets a file name that the user inputs, depending on its type
{
    string path;

    cout << "Please input "<< type << " path" << endl;
    cin >> path;

    if (type == "dataset")
        cube->setInputFile(path);
    else if (type == "query")
        cube->setQueryFile(path);
    else if (type == "output")
        cube->setOutputFile(path);
    else
        cout << "ERROR Wrong type" << endl;
}


void readInputFile(Hypercube * cube, Dataset * dataset)                                   //reads input file and stores data read in the dataset
{
    //opens input file for input in binary form
    ifstream in(cube->getInputFile());
    if(!in.is_open() || in.fail())
        errorExit(2, "Cannot open input file", cube, dataset);

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

    //initializes hash table in Hypercube with size = num_of_images / 8
    cube->initializeHashTable(dataset->getNumOfImgs()/8);

    //reads and creates an object for every image
    for(int i=0;i<dataset->getNumOfImgs();i++)
    {
        //initialize array to store image to read
        unsigned char *image = new unsigned char[dataset->getRows()*dataset->getColumns()];
        int pos=0;

        for(int c=0;c<dataset->getColumns();c++)
        {
            for(int r=0;r<dataset->getRows();r++)
            {
                unsigned char temp=0;
                in.read((char*)&temp,sizeof(temp));
                image[pos++] = temp;                 //builds image here
            }
        }

        //inserts image to all hash tables and in dataset image list
        auto * img = new ImageData(i, dataset->getRows(), dataset->getColumns());
        dataset->insertImage(img);
    }

    //checks if file was read successfully
    if (!in.good() || in.fail())
        errorExit(3, "Error at reading input file", cube, dataset);

    in.close();              //closes file
}


void readQueryFile(Hypercube * cube, Dataset * dataset)                                        //reads query file and stores data read in the dataset
{
    //opens input file for input in binary form
    ifstream in(cube->getQueryFile());
    if(!in.is_open() || in.fail())
        errorExit(4, "Cannot open query file", cube, dataset);


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
        //initialize array to store image to read
        unsigned char image[dataset->getRows()*dataset->getColumns()];
        int pos=0;

        for(int c=0;c<dataset->getColumns();c++)
        {
            for(int r=0;r<dataset->getRows();r++)
            {
                unsigned char temp=0;
                in.read((char*)&temp,sizeof(temp));
                image[pos++] = temp;                 //builds image here
            }
        }

        //inserts query image to query list of dataset
        //dataset->insertQueryImage(new ImageData(i, dataset->getRows(), dataset->getColumns(), image));
    }

    //checks if file was read successfully
    if (!in.good() || in.fail())
        errorExit(3, "Error at reading input file", cube, dataset);

    in.close();              //closes file
}