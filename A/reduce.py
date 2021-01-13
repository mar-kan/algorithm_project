import sys
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.python.keras import Input, Model
from tensorflow.python.keras.backend import set_session
from sklearn.model_selection import train_test_split
from tensorflow.python.keras.optimizer_v2.rmsprop import RMSprop
from sklearn.preprocessing import MinMaxScaler

from encoder import encoder
from decoder import decoder
from loadDataset import *
from output import *


def checkArguments():  # checks script's arguments
    if len(sys.argv) < 9:
        print('Too few arguments')
        exit(-1)

    dataset = ''
    queryset = ''
    output_dataset_file = ''
    output_query_file = ''

    for i in range(1, len(sys.argv), 2):
        if sys.argv[i] == '-d':
            dataset = sys.argv[i + 1]
        elif sys.argv[i] == '-q':
            queryset = sys.argv[i + 1]
        elif sys.argv[i] == '-od':
            output_dataset_file = sys.argv[i + 1]
        elif sys.argv[i] == '-oq':
            output_query_file = sys.argv[i + 1]
        else:
            print('Wrong arguments' + sys.argv[i])
            exit(-1)

    return dataset, queryset, output_dataset_file, output_query_file


def normalizeVectors(a, b, vectors):
    scaler = MinMaxScaler(feature_range=(a, b))
    scaler.fit(vectors)
    MinMaxScaler()
    vectors = scaler.transform(vectors)

    # round to integers
    return [[round(num) for num in vector] for vector in vectors]


def main():
    sess = tf.compat.v1.InteractiveSession()

    dataset, queryset, output_dataset_file, output_query_file = checkArguments()

    # reading datasets
    trainImages, numOfTrainImages = loadDataset(dataset)
    testImages, numOfTestImages = loadDataset(queryset)

    # normalization
    X_train = trainImages / 255.0
    X_test = testImages / 255.0

    # create input channel
    inChannel = 1
    x, y = 28, 28
    nn_input = Input(shape=(x, y, inChannel))

    answer = 'yes'
    while answer == 'yes':
        # user inputs hyperparameters
        print()
        print('Input number of convolutional layers')
        num_of_convs = int(input())
        print('Input size of convolutional filters')
        conv_filter_size = int(input())
        print('Input number of convolutional filters per layer')
        num_of_filters = int(input())
        print('Input number of epochs')
        epochs = int(input())
        print('Input batch size')
        batch_size = int(input())
        print('Input latent space size')
        latent_space = int(input())

        # nn is created
        autoencoder = Model(nn_input,
                            decoder(encoder(num_of_convs, num_of_filters, conv_filter_size, nn_input, latent_space),
                                    num_of_convs,
                                    conv_filter_size, num_of_filters), name='autoencoder')
        autoencoder.summary()

        autoencoder.compile(loss='mean_squared_error', optimizer=RMSprop())

        train_X, train_ground = train_test_split(X_train, test_size=0.5,
                                                 random_state=13)
        valid_X, valid_ground = train_test_split(X_test, test_size=0.5,
                                                 random_state=13)

        autoencoder_history = autoencoder.fit(train_X, train_ground, batch_size=batch_size, epochs=epochs, verbose=1,
                                              validation_data=(valid_X, valid_ground))

        # getting all outputs of last node of encoder (flattened vector)
        encoder_model = Model(nn_input,
                              encoder(num_of_convs, num_of_filters, conv_filter_size, nn_input, latent_space)[0],
                              name='encoder')
        train_outputs = encoder_model.predict(train_X)
        test_outputs = encoder_model.predict(valid_X)

        # normalizing outputs in [0, 25500]
        train_outputs = normalizeVectors(0, 25500, train_outputs)
        test_outputs = normalizeVectors(0, 25500, test_outputs)

        # creating and writing output files
        createOutputFile(output_dataset_file, 1, latent_space, train_outputs)
        createOutputFile(output_query_file, 1, latent_space, test_outputs)

        # user's choices
        print('Would you like to present the loss plots for these hyperparameters?')
        print('(Type yes or no)')
        if input() == 'yes':
            # plotting loss function
            ax = plt.subplot(1, 1, 1)
            ax.plot(autoencoder_history.history['loss'], 'b', label='Loss')
            ax.plot(autoencoder_history.history['val_loss'], 'g', label='Validation loss')
            ax.set_xlabel(r'Epoch')
            ax.set_ylabel(r'Loss')
            ax.legend(loc='upper right')
            plt.show()

        print('Would you like to save the model with these hyperparameters?')
        print('(Type yes or no)')
        if input() == 'yes':
            # saving model in current directory
            autoencoder.save(os.getcwd() + '/reducer.h5', overwrite=True)
            autoencoder.summary()

        print('Would you like to repeat the process with different hyperparameters?')
        print('(Type yes or no)')
        answer = input()

    sess.close()


if __name__ == "__main__":
    # config = tf.compat.v1.ConfigProto()
    # config.gpu_options.allow_growth = True
    # config.gpu_options.per_process_gpu_memory_fraction = 0.8

    # os.environ["CUDA_VISIBLE_DEVICES"] = "0"
    # config = tf.compat.v1.ConfigProto()
    # config.gpu_options.allow_growth = True
    # config.gpu_options.per_process_gpu_memory_fraction = 0.8
    # set_session(tf.compat.v1.Session(config=config))

    # device_name = tf.test.gpu_device_name()
    # if device_name != '/device:GPU:0':
    #    raise SystemError('GPU not found')
    #z print('GPU at : {}'.format(device_name))

    main()
