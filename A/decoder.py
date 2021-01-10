import numpy as np
from tensorflow.python.keras.layers import BatchNormalization, Conv2D, UpSampling2D, Dense, Reshape, \
    Conv2DTranspose, Dropout


def decoder(encoder_out, num_of_convs, conv_filter_size, num_of_filters):
    # decoder with <num_of_convs> layers

    conv = encoder_out[0]
    encoded_shape = encoder_out[1]

    # creates 1st layers to decompress the image
    conv = Dense(np.prod(encoded_shape[1:]))(conv)
    conv = Dropout(rate=0.9, seed=0.8, input_shape=encoded_shape)(conv)
    conv = Reshape((encoded_shape[1], encoded_shape[2], encoded_shape[3]))(conv)

    # creates the rest layers
    i = 0
    while i < num_of_convs - 2:
        if i == num_of_convs - 3 and i != 0:
            conv = Conv2DTranspose(conv_filter_size, (num_of_filters, num_of_filters), activation='relu',
                                   padding='same')(up)
        else:
            conv = Conv2DTranspose(conv_filter_size, (num_of_filters, num_of_filters), activation='relu',
                                   padding='same')(conv)

        conv = BatchNormalization()(conv)
        conv = Conv2DTranspose(conv_filter_size, (num_of_filters, num_of_filters), activation='relu', padding='same')(
            conv)
        conv = BatchNormalization()(conv)

        # up sampling only in last and 2nd from last layers
        if i >= num_of_convs - 4:
            up = UpSampling2D((2, 2))(conv)

        conv_filter_size = int(conv_filter_size / 2)
        i += 1

    if num_of_convs <= 2:
        up = UpSampling2D((2, 2))(conv)

    # creates last layer
    decoded = Conv2D(1, (conv_filter_size, conv_filter_size), activation='sigmoid', padding='same')(up)
    return decoded
