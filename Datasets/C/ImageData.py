class ImageData:
    image_num = -1
    dimension = -1
    image = []

    def __init__(self, num, dim, img):
        self.image_num = num
        self.dimension = dim
        self.image = img
