import time

from ImageData import ImageData
from distance import *


def exactNN(query, trainSet, distType):  # translated function NearestNeighbour::ExactNN from assignment 1
    # for one query goes through the dataset and finds nearest neighbours.
    # stores them in a list of tuples [distance, ImageData]

    nn = []  # list with nearest neighbours
    start = time.time()

    k_distance = 1000.0
    for entry in trainSet:
        if distType == 'EMD':
            distance = emd(query, entry)
        else:
            distance = manhattanDistance(query, entry)

        if distance < k_distance:
            nn.append([distance, query])
        elif distance > k_distance:
            k_distance = distance

    end = time.time()
    return nn, (end - start)  # returns list of neighbours and time elapsed


def evaluateNeighbours(N, query, nn, trainLabels, testLabels):  # evaluates accuracy for N neighbours of a query
    correct = 0
    count = 0

    nn.sort(key=lambda x: x[0], reverse=True)   # sorts list of neighbours by distance
    for pairs in nn:
        #if count > N:  # evaluates N nearest neighbours
            #break

        print(str(testLabels[query.image_num]) + ", " + str(trainLabels[pairs[1].image_num]))
        if testLabels[query.image_num] == trainLabels[pairs[1].image_num]:
            correct += 1

        count += 1

    return correct / N
