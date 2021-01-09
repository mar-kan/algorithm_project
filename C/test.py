import sys
import scipy
from ortools.linear_solver import pywraplp
import numpy as np
from scipy.spatial.distance import cdist

from ctypes import cdll
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
    if len(sys.argv) < 10:
        print('Too few arguments')
        exit(-1)

    flag = False

    trainSet = ''
    testSet = ''
    trainLabels = ''
    testLabels = ''

    for i in range(1, len(sys.argv), 2):
        if sys.argv[i] == '-d':
            trainSet = sys.argv[i + 1]
        elif sys.argv[i] == '-q':
            testSet = sys.argv[i + 1]
        elif sys.argv[i] == '-l1':
            trainLabels = sys.argv[i + 1]
        elif sys.argv[i] == '-l2':
            testLabels = sys.argv[i + 1]
        elif sys.argv[i] == '-EMD':
            flag = True
        else:
            print('Wrong arguments' + sys.argv[i])
            exit(-1)

    if not flag:
        print('Wrong arguments')
        exit(-1)

    return trainSet, testSet, trainLabels, testLabels


def main():
    trainset, testset, trainLabel, testLabel = checkArguments()

    # reading datasets and label sets
    trainSet, numOfTrainImages = loadDataset(trainset)
    testSet, numOfTestImages = loadDataset(testset)

    trainLabels = loadLabelSet(trainLabel)
    testLabels = loadLabelSet(testLabel)

    lib = cdll.LoadLibrary('../searchLib.so')

    # emd()

    # scipy.optimize.linprog()


if __name__ == "__main__":
    main()
