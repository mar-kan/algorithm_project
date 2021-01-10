from tensorflow.python.keras.layers import BatchNormalization, MaxPooling2D, Conv2D, Flatten, Dense, Dropout
from tensorflow.keras import backend as K


def encoder(num_of_convs, num_of_filters, conv_filter_size, input_img, latent_dim):
    # encoder with <num_of_convs> layers

    conv = None

    # creates 1st n-2 layers
    i = 0
    while i < int(num_of_convs) - 2:
        if i == 0:
            conv = Conv2D(conv_filter_size, (num_of_filters, num_of_filters), activation='relu', padding='same')(
                input_img)
        elif i == 3:
            conv = Conv2D(conv_filter_size, (num_of_filters, num_of_filters), strides=(2, 2), activation='relu',
                          padding='same')(conv)
        else:
            conv = Conv2D(conv_filter_size, (num_of_filters, num_of_filters), activation='relu', padding='same')(conv)
        conv = BatchNormalization()(conv)
        conv = Conv2D(conv_filter_size, (num_of_filters, num_of_filters), activation='relu', padding='same')(conv)
        conv = BatchNormalization()(conv)

        # max pooling only after 1st 2nd layers
        if i == 0 or i == 1:
            pool = MaxPooling2D(pool_size=(2, 2))(conv)
            conv = Dropout(rate=0.9, seed=0.8, input_shape=(K.int_shape(pool),))(pool)

        conv_filter_size *= 2
        i += 1

    # stores last layer's shape
    encoded_shape = K.int_shape(conv)

    if i > 2:  # ignores if last layer was a dropout layer
        conv = Dropout(rate=0.9, seed=0.8, input_shape=(K.int_shape(conv),))(conv)

    # creates last 2 layers
    conv = Flatten()(conv)
    encoded = Dense(latent_dim)(conv)

    return encoded, encoded_shape
