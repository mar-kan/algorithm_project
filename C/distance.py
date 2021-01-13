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

    # implementing EMD in every cluster and calculating flow and distance
    flow = []
    distance = []
    cost = []
    w2_new = []
    for i in range(0, len(clusters1)):
        # either cluster could be the supplier or the consumer
        flow.append(abs(w1[i] - w2[i]) / 2)
        distance.append(
            groundDistance(clusters1[i][int(clusters1[i].shape[0] / 2)], clusters2[i][int(clusters1[i].shape[0] / 2)]))
        if w1[i] - w2[i] > 0:
            w2_new.append(int(w2[i] + flow[i]))
        else:
            w2_new.append(int(w2[i] - flow[i]))

    # setting up restrictions
    zeros = np.zeros(len(flow), dtype=int)

    Sf = 0
    for num in flow:
        Sf += num

    # fi >= 0
    Aub = []
    for i in range(0, len(flow)):
        zeros[i] = -1
        Aub.append(list(zeros))
        zeros[i] = 0
    Bub = zeros

    # Sf = w1i and Sf = w2i'
    Aeq = Aub + Aub
    Beq = w1 + w2_new

    # solving linear problem with simplex
    res = optimize.linprog(
        c=distance,  # y = flow * distance
        A_ub=np.array(Aub),
        b_ub=[Bub],
        A_eq=np.array(Aeq),
        b_eq=[Beq],
        bounds=(0, None),
        method='simplex'
    )

    return res.fun


def manhattanDistance(image1, image2):  # calculateManhattanDistance from exercise 1 translated
    dist = 0
    for i in range(0, image1.rows):
        for j in range(0, image1.columns):
            dist += abs(image1.image[i][j] - image2.image[i][j])

    return dist
