import sys
import time
import scipy

from loadDatasetBytes import *
from distance import *


def exactNN(trainSet, testSet, distType):  # translated function NearestNeighbour::ExactNN from assignment 1
    # for each query goes through the dataset and finds nearest neighbours.
    # stores them in a list of tuples[image_index, image]

    nn = []  # list with nearest neighbours
    start = time.time()

    k_distance = 1000.0
    for query in testSet:
        index = 0
        for entry in trainSet:
            if distType == 'EMD':
                distance = emd(query, entry)
            else:
                distance = manhattanDistance(query, entry)

            if distance < k_distance:
                nn.append([index, query])
                if distance > k_distance:
                    k_distance = distance

            index += 1

    end = time.time()
    return nn, (end - start)  # returns list of neighbours and time elapsed


def evaluateNeighbours(N, nn, trainLabels, testLabels):  # evaluates accuracy for N neighbours
    count = 0
    for neighbour in nn:
        if count > N:  # evaluates 10 nearest neighbours
            break

        print(neighbour)

        count += 1

    return count / N


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
    trainSet, numOfTrainImages = loadDataset(trainsetName)
    testSet, numOfTestImages = loadDataset(testsetName)

    trainLabels = loadLabelSet(trainLabelName)
    testLabels = loadLabelSet(testLabelName)

    print("Executing EMD")
    # nnEMD, timeEMD = exactNN(trainSet, testSet, 'EMD')

    print("Executing Manhattan")
    nnMan, timeMan = exactNN(trainSet, testSet, 'Manhattan')

    print("Evaluating")
    # accuracyEMD = evaluateNeighbours(10, nnEMD, trainLabels, testLabels)
    accuracyMan = evaluateNeighbours(10, nnMan, trainLabels, testLabels)

    # writing output file
    file = open(outputFile, "w+")
    file.write("Average Correct Search Results EMD: " + str(accuracyEMD))
    file.write("Average Correct Search Results MANHATTAN: " + str(accuracyMan))
    file.write("Time EMD: " + str(timeEMD))
    file.write("Time Manhattan: " + str(timeMan))
    file.close()


if __name__ == "__main__":
    main()
