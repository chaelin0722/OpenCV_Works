##-- AND logic with Neural Network (Multilayer perceptron)
##-- Created by Prof. Kim Byung-Gyu on 23 July, 2019
from keras.models import Sequential
from keras.layers import Dense
import matplotlib.pyplot as plt
import numpy
##-- fix random seed for reproducibility
seed = 7
numpy.random.seed(seed)
##-- load pima indians dataset
dataset = numpy.loadtxt("AND-gate.data.csv", delimiter=",")
##-- split into input (X) and output (Y) variables
X = dataset[:,0:2]
Y = dataset[:,2]
#print(X)
#print(Y)

##-- create model
# sequential network by adding
model = Sequential()
# input layer
model.add(Dense(2, input_dim=2, kernel_initializer='uniform', activation='sigmoid'))
# hidden layer
model.add(Dense(2, kernel_initializer='uniform', activation='sigmoid'))
# output layer 
model.add(Dense(1, kernel_initializer='uniform', activation='sigmoid'))
##-- Compile model
model.compile(loss='mean_squared_error', optimizer='adam', metrics=['accuracy'])
##-- Fit the model
history = model.fit(X, Y, validation_split=0.2, epochs=200, batch_size=1, verbose=0)
## list all data in history
#print(history.history['acc'])
#print(history.history['loss'])
#print(history.history['val_acc'])
#print(history.history['val_loss'])

##-- summarize history for accuracy
plt.plot(history.history['accuracy'])
plt.plot(history.history['val_accuracy'])
plt.title('model accuracy')
plt.ylabel('accuracy')
plt.xlabel('epoch')
plt.legend(['train', 'test'], loc='upper left')
plt.show()
##-- summarize history for loss
plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])
plt.title('model loss')
plt.ylabel('loss')
plt.xlabel('epoch')
plt.legend(['train', 'test'], loc='upper left')
plt.show()

##-- Actual test for the trained model --##
dataset_test = numpy.loadtxt("AND-gate-test.data.csv", delimiter=",")
x_test = dataset_test[:,0:2]
yhat = model.predict(x_test)

print('#-- X_tested --#')
print(x_test)
print('#-- Y_predicted --#')
print(yhat)
