import scipy


def emd(a, b):  # (image1 , image2):

    # scipy.optimize.linprog()

    return 1


def manhattanDistance(image1, image2):  # calculateManhattanDistance from exercise 1 translated
    dist = 0
    for i in range(0, image1.dimension):
        if image1.image[i] > image2.image[i]:
            dist += image1.image[i] - image2.image[i]
        else:
            dist += image2.image[i] - image1.image[i]

    return dist
