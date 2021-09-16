# A. Bottleneck autoencoder

Bottleneck autoencoder that compresses vectors into smaller ones. Size for compression is inputed.

execution instructions: python3 reduce.py -d <dataset_path> -q <queryset_path> -od <output_dataset_filename> -oq <output_queryset_filename>
                                                                                                                         

# B. Manhattan distance

Search for the nearest neighbour of the images of the dataset using the Manhattan distance algorithm.

There are 4 searches implemented: 

      Heuristic searches for the original dimension dataset and the compressed one.
      Approximate searches for both dimensions.
    
compilation instructions: $ make 
execution instructions: $ ./search –d <input_file_original_space> -i <input_file_new_space> –q <query_file_original_space> -s <query_file_new_space> –k <int> -L <int> -ο <output_file>                                                                                                                         
    
# C. Earth mover's distance (EMD)   

Heuristic search for the 10 closest neighbours of each image of the dataset.

      
execution instructions: $ python3 search.py -d  Datasets/train-images-idx3-ubyte  –q  Datasets/t10k-images-idx3-ubyte  -l1  Datasets/train-labels-idx1-ubyte -l2 Datasets/t10k-labels-idx1-ubyte -o C_output.txt -EMD      
-------------------------------

For all the parts of the project the dataset used is the MNIST dataset of handwritten digits.

For the reduced dimensions, the datasets used are generated from part A of the project.
