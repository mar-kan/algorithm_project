import sys
import time
from loadDatasetBytes import *
from neighbour import *


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


def main():
    trainsetName, testsetName, trainLabelName, testLabelName, outputFile = checkArguments()

    # reading datasets and label sets
    print("Reading datasets")
    trainSet, numOfTrainImages = loadDataset(trainsetName)
    testSet, numOfTestImages = loadDataset(testsetName)

    trainLabels = loadLabelSet(trainLabelName)
    testLabels = loadLabelSet(testLabelName)

    accuracyEMD = 0
    accuracyMan = 0
    timeEMD = -1
    timeMan = -1

    print("Processing queries with EMD")
    for query in testSet:
        start = time.time()
        # find neighbours
        # nnEMD = exactNN(trainSet, testSet, 'EMD')
        # evaluate 10 nearest neighbours
        # accuracyEMD += evaluateNeighbours(10, nnEMD, trainLabels, testLabels)
        end = time.time()
        timeEMD = end - start
        break

    print("Processing queries with Manhattan Distance")
    for query in testSet:
        start = time.time()
        # find neighbours
        nnMan = exactNN(query, trainSet, 'Manhattan')
        # evaluate 10 nearest neighbours
        accuracyMan += evaluateNeighbours(10, query, nnMan, trainLabels, testLabels)

        end = time.time()
        timeMan = end - start
        #break

    # writing output file
    file = open(outputFile, "w+")
    file.write("Average Correct Search Results EMD: " + str(accuracyEMD) + '\n')  # / len(testSet)))
    file.write("Average Correct Search Results MANHATTAN: " + str(accuracyMan) + '\n')  # / len(testSet)))
    file.write("Time EMD: " + str(timeEMD) + '\n')
    file.write("Time Manhattan: " + str(timeMan) + '\n')
    file.close()

    print("Exiting")
    exit(0)


if __name__ == "__main__":
    main()
