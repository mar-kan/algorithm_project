import numpy as np
from ImageData import ImageData
from distance import *


def exactNN(query, trainSet, distType, cluster_dim):  # translated function NearestNeighbour::ExactNN from assignment 1
    # for one query goes through the dataset and finds nearest neighbours.
    # stores them in a list of tuples [distance, ImageData]

    nn = []  # list with nearest neighbours
    k_distance = 10000.0
    for entry in trainSet:
        if distType == 'EMD':
            distance = emd(query, entry, cluster_dim)
            if distance == -1:
                continue
        else:
            distance = manhattanDistance(query, entry)

        if distance < k_distance:
            nn.append([distance, entry])
        else:
            k_distance = distance

    return nn  # returns list of neighbours


def evaluateNeighbours(N, query, nn, trainLabels, testLabels):  # evaluates accuracy for N neighbours of a query
    correct = 0
    count = 0

    nn.sort(key=lambda x: x[0], reverse=False)  # sorts list of neighbours by distance
    for pairs in nn:
        if count >= N:  # evaluates N nearest neighbours
            break

        if testLabels[query.image_num] == trainLabels[pairs[1].image_num]:
            correct += 1

        count += 1

    return correct / N
