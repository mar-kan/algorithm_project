//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "../Assignment1files/general/HashTable.h"
#include "../Assignment1files/LSH.h"
#include "lshMainUtils.h"
#include "../Assignment1files//general/Dataset.h"

int main(int argc, char * argv[])
{
    cout << "Running LSH program" << endl;
    string answer, path;

    //creates one LSH obj for each dimension
    auto * lshTrue = new LSH();
    auto * lshNew = new LSH();

    checkArguments(lshTrue, lshNew, argc, argv);            //checks program arguments/usr/bin/valgrind

    do  //runs algorithm at least once
    {
        if (lshTrue->getInputFile().empty())                //asks for input file name if none was given
            inputFileName(lshTrue, "dataset");

        //initializes datasets, one for each dimension
        auto *datasetTrue = new Dataset();
        auto *datasetNew = new Dataset();

        /** reading both data and query sets **/
        readInputFile(lshTrue, datasetTrue, "true");                //reads input file and inserts data in dataset
        readInputFile(lshNew, datasetNew, "new");


        if (lshTrue->getQueryFile().empty())                    //asks for query file name if none was given
            inputFileName(lshTrue, "query");

        if (lshTrue->getOutputFile().empty())                   //asks for output file name if none was given
            inputFileName(lshTrue, "output");


        /** prepare for algorithms **/
        lshTrue->initializeHashTables(datasetTrue->getNumOfImgs()/8);                         //initializes hash tables in LSH with size = num_of_images / 8
        lshNew->initializeHashTables(datasetNew->getNumOfImgs()/8);                         //initializes hash tables in LSH with size = num_of_images / 8

        cout << "True dim: Choosing W"<< endl;
        lshTrue->setW(40000/**datasetTrue->pickWLSH()**/);                                               //picks suitable W for the dataset and sets it in lsh
        cout << "Picked W = "<< lshTrue->getW() << endl;
        cout << "New dim: Choosing W"<< endl;
        lshNew->setW(datasetNew->pickWLSH());                                               //picks suitable W for the dataset and sets it in lsh
        cout << "Picked W = "<< lshNew->getW() << endl;

        lshTrue->initializeHashTables(datasetTrue->getNumOfImgs()/8);                         //initializes hash tables in LSH with size = num_of_images / 8
        lshTrue->initializeHashFamily(datasetTrue->getColumns()*datasetTrue->getRows());          //initializes hash family of dimension d
        lshNew->initializeHashTables(datasetNew->getNumOfImgs()/8);                         //initializes hash tables in LSH with size = num_of_images / 8
        lshNew->initializeHashFamily(datasetNew->getColumns()*datasetNew->getRows());          //initializes hash family of dimension d


        cout << "True dim: Inserting in all hash tables" << endl;
        lshTrue->insertToAllHashTables(datasetTrue);                                          //inserts all images of dataset in all the hash tables
        cout << "New dim: Inserting in all hash tables" << endl;
        lshNew->insertToAllHashTables(datasetNew);

        //reads query files
        readQueryFile(lshTrue, datasetTrue, "true");
        readQueryFile(lshNew, datasetNew, "new");

        float tTrue=0.0, tReduced=0.0, tLSH=0.0, distLSH=0.0, distReduced=0.0;

        //creates / overwrites output file
        FILE * fp = fopen(lshTrue->getOutputFile().c_str(), "w");
        fclose(fp);

        cout << "Executing algorithms" << endl;
        for (int i=0; i<datasetNew->getQueryCount(); i++)  //for each query image
        {
            //cout << "Processing query-"<< i << endl;

            /** executes all algorithms **/
            auto * nnNew = new NearestNeighbour(lshNew->getN());
            auto * nnTrue = new NearestNeighbour(lshTrue->getN());

            //cout << "Executing Approximate Nearest Neighbour Reduced" << endl;
            nnNew->ApproximateNNN(lshNew, "LSH", datasetNew->getQueryImagePos(i));

            //cout << "Executing Approximate Nearest Neighbour True" << endl;
            nnTrue->ApproximateNNN(lshTrue, "LSH", datasetTrue->getQueryImagePos(i));

            //cout << "Executing Exact Nearest Neighbour" << endl<<endl;
            nnTrue->ExactNNN(lshTrue, "LSH", datasetTrue->getQueryImagePos(i), datasetTrue);

            writeOutputQuery(lshNew,lshTrue, nnNew, nnTrue, datasetTrue->getQueryImagePos(i)); //writes output file

            tReduced = nnNew->getSecsAnn();
            tLSH = nnTrue->getSecsAnn();
            tTrue = nnTrue->getSecsReal();
            distLSH += nnTrue->getNnResults()->begin()->first;
            distReduced += nnNew->getNnResults()->begin()->first;

            delete nnNew;
            delete nnTrue;
        }

        float afLSH = distLSH / (float)datasetTrue->getQueryCount();
        float afReduced = distReduced / (float)datasetNew->getQueryCount();
        writeOutputInfo(lshTrue, tReduced, tLSH, tTrue, afLSH, afReduced);

        clearFileNames(lshTrue);                                //erases all file names to input new ones in each iteration
        delete datasetTrue;
        delete datasetNew;

        cout << "Would you like to repeat the process with a different file?" << endl;
        cin >> answer;

    }while (answer == "yes" || answer == "y");              //repeats while the user inputs 'yes' or 'y'

    delete lshTrue;
    //delete lshNew;
    cout << endl << "Exiting" << endl;
    exit(0);
}