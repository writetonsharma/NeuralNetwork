
import numpy
import matplotlib.pyplot
import cv2


data_file = open("../Data/mnist_train_100.csv", 'r')
data_list = data_file .readlines()
data_file .close()

all_values = data_list [0].split(',')
image_array = numpy.asfarray( all_values [1:]).reshape((28,28))
#cv2.namedWindow( "test", cv2.WINDOW_NORMAL);
matplotlib.pyplot.imshow(image_array , cmap='Greys', interpolation='None')
matplotlib.pyplot.show()
#cv2.waitKey(0);