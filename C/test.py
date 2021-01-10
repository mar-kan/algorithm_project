import sys
import time
import scipy


sys.path.insert(0, '../')
from A.loadDataset import *


def emd(a, b):
    earth = 0
    earth1 = 0
    diff = 0
    s = len(a)
    su = []
    diff_array = []
    for i in range(0, s):
        diff = a[i] - b[i]
        diff_array.append(diff)
        diff = 0
    for j in range(0, s):
        earth = (earth + diff_array[j])
        earth1 = abs(earth)
        su.append(earth1)
    emd_output = sum(su) / (s - 1)
    print(emd_output)


def checkArguments():
    if len(sys.argv) < 12:
        print('Too few arguments')
        exit(-1)

    flag = False

    trainSet = ''
    testSet = ''
    trainLabels = ''
    testLabels = ''
    outputFile = ''

    for i in range(1, len(sys.argv), 2):
        if sys.argv[i] == '-d':
            trainSet = sys.argv[i + 1]
        elif sys.argv[i] == '-q':
            testSet = sys.argv[i + 1]
        elif sys.argv[i] == '-l1':
            trainLabels = sys.argv[i + 1]
        elif sys.argv[i] == '-l2':
            testLabels = sys.argv[i + 1]
        elif sys.argv[i] == '-o':
            outputFile = sys.argv[i + 1]
        elif sys.argv[i] == '-EMD':
            flag = True
        else:
            print('Wrong arguments' + sys.argv[i])
            exit(-1)

    if not flag:
        print('Wrong arguments')
        exit(-1)

    return trainSet, testSet, trainLabels, testLabels, outputFile


def exactNNN(Algorithm* algo, string method, ImageData *query_img, Dataset *dataset) //executes exact nearest neighbor for query_img. stores results in realResults
    {                                                                                 //also computes real time
const clock_t begin_time = clock();
int insertions=0;

float k_distance = 1000.0;  //stores max distance inserted in map
for (int i=0; i<dataset->getNumOfImgs(); i++)                       //traverses dataset's vector with all the images
{
float distance = calculateManhattanDistance(query_img, dataset->getImagePos(i));
if (distance < k_distance)
{
realResults->insert(pair<float, ImageData*>(distance, dataset->getImagePos(i)));
insertions++;
if (distance > k_distance)
k_distance = distance;
}

if (method == "LSH")
{
//if (insertions/10 > ((LSH*)algo)->getL())                                //function returns if inserted much data
//break;
}
else
{
//if (insertions/10 > ((Hypercube*)algo)->getM())                          //function returns if it inserted much data
//break;
}
}
secs_real = float(clock() - begin_time) / CLOCKS_PER_SEC;
}


def main():
    trainsetName, testsetName, trainLabelName, testLabelName, outputFile = checkArguments()

    # reading datasets and label sets
    trainSet, numOfTrainImages = loadDataset(trainsetName)
    testSet, numOfTestImages = loadDataset(testsetName)

    trainLabels = loadLabelSet(trainLabelName)
    testLabels = loadLabelSet(testLabelName)

    nn = [] # list with nearest neighbours


    start = time.time()
    for query in testSet:
        for entry in trainSet:
            dist = emd(query, entry)


    end = time.time()
    print(end - start)

    # emd()

    # scipy.optimize.linprog()

    # writing output file
    file = open(outputFile, "w+")
    file.write("Average Correct Search Results EMD: <double>")
    file.write("Average Correct Search Results MANHATTAN: <double> ")
    file.write("Time EMD: "+str(end - start))
    file.close()


if __name__ == "__main__":
    main()
