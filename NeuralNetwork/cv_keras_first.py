## Visualize training history
from keras.models import Sequential
from keras.layers import Dense
import matplotlib.pyplot as plt
import numpy
## fix random seed for reproducibility
seed = 7
numpy.random.seed(seed)
## load pima indians dataset
dataset = numpy.loadtxt("pima-indians-diabetes.data.csv", delimiter=",")
## split into input (X) and output (Y) variables
X = dataset[:,0:8]
Y = dataset[:,8]
#print(X)
#print(Y)
## create model
# 선형적으로 차원을 쌓아 모델을 만듦
model = Sequential()
# input layer
model.add(Dense(12, input_dim=8, kernel_initializer='uniform', activation='relu'))
# hidden layer
model.add(Dense(8, kernel_initializer='uniform', activation='relu'))
# output layer 
model.add(Dense(1, kernel_initializer='uniform', activation='sigmoid'))
## Compile model
model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])
## Fit the model
history = model.fit(X, Y, validation_split=0.33, epochs=150, batch_size=10, verbose=0)
## list all data in history
#print(history.history['acc'])
#print(history.history['loss'])
#print(history.history['val_acc'])
#print(history.history['val_loss'])
## summarize history for accuracy
plt.plot(history.history['accuracy'])
plt.plot(history.history['val_accuracy'])
plt.title('model accuracy')
plt.ylabel('accuracy')
plt.xlabel('epoch')
plt.legend(['train', 'test'], loc='upper left')
plt.show()
## summarize history for loss
plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])
plt.title('model loss')
plt.ylabel('loss')
plt.xlabel('epoch')
plt.legend(['train', 'test'], loc='upper left')
plt.show()
