from math import sqrt

from scipy import optimize
import numpy as np
from ImageData import *


def createClusters(img, cluster_dim):
    # creates clusters[cluster_dim x cluster_dim] of image
    h, w = img.image.shape
    return (img.image.reshape(int(h // cluster_dim), cluster_dim, -1, cluster_dim)
            .swapaxes(1, 2)
            .reshape(-1, cluster_dim, cluster_dim))


def calculateWeights(clusters):
    # calculates weights
    w = []
    for img in clusters:
        s = 0
        for i in range(0, img.shape[0]):
            for j in range(0, img.shape[1]):
                s += img[i][j]
        w.append(s)

    return w


def groundDistance(coordinates1, coordinates2):
    # returns euclidean distance of 2 points[x,y]
    diffX = abs(coordinates1[0] - coordinates2[0])
    diffY = abs(coordinates1[1] - coordinates2[1])

    return sqrt((diffX * diffX) + (diffY * diffY))


def emd(image1, image2, cluster_dim):
    # creates clusters and weights of the 2 images
    clusters1 = createClusters(image1, cluster_dim)
    w1 = calculateWeights(clusters1)
    clusters2 = createClusters(image2, cluster_dim)
    w2 = calculateWeights(clusters2)

    # implementing EMD in every cluster and calculating distance and flow
    flow = []
    distance = []

    for i in range(0, len(clusters1)):
        # set which cluster will be the supplier and which the consumer
        if w1[len(clusters1 / 2)] > w2[len(clusters2 / 2)]:
            supplier = clusters1[len(clusters1 / 2)]
            consumer = clusters2[len(clusters2 / 2)]
        else:
            supplier = clusters2[len(clusters2) / 2]
            consumer = clusters1[len(clusters1 / 2)]


    optimize.linprog(
        c = flow * distance,
        A_ub=[[1, 1]],
        b_ub=[6],
        bounds=(1, 5),
        method='simplex'
    )
    return 1


def manhattanDistance(image1, image2):  # calculateManhattanDistance from exercise 1 translated
    dist = 0
    for i in range(0, image1.rows):
        for j in range(0, image1.columns):
            dist += abs(image1.image[i][j] - image2.image[i][j])

    return dist
