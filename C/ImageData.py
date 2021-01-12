import numpy as np


class ImageData:
    image_num = -1
    rows = -1
    columns = -1
    image = []

    def __init__(self, num, rows, cols, img):
        self.image_num = num
        self.rows = rows
        self.columns = cols
        self.image = np.array(img, dtype=int)
