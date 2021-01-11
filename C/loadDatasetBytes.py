import numpy as np

from ImageData import ImageData


# translated dataset reading from exercise 1 and converted all bytes to ints
def loadDataset(full_path):
    file = open(full_path, "rb")

    magic_number = int.from_bytes(file.read(4), byteorder='big')
    num_of_images = int.from_bytes(file.read(4), byteorder='big')
    rows = int.from_bytes(file.read(4), byteorder='big')
    columns = int.from_bytes(file.read(4), byteorder='big')

    images = []  # stores all images
    for i in range(0, num_of_images):
        img = []
        count = 0
        for r in range(0, rows):
            for c in range(0, columns):
                img.append(int.from_bytes(file.read(1), byteorder='big'))

        image = ImageData(count, rows*columns, img)
        images.append(image)
        count += 1

    return images, num_of_images


def loadLabelSet(full_path):
    file = open(full_path, "rb")

    magic_number = int.from_bytes(file.read(4), byteorder='big')
    num_of_images = int.from_bytes(file.read(4), byteorder='big')

    labels = []  # stores all images
    for i in range(0, num_of_images):
        label = int.from_bytes(file.read(1), byteorder='big')
        labels.append(label)

    return labels
