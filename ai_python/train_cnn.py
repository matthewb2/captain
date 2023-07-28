from __future__ import print_function
import keras
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense, Dropout, Flatten
from keras.layers import Conv1D, MaxPooling1D, Reshape
from keras.callbacks import ModelCheckpoint
from keras.models import model_from_json
from keras import backend as K

import numpy as np

n = 100000
x_train = np.zeros((n,4))
for i in range(n):
    x_train[i,:] = np.random.permutation(50)[0:4]

x_train = x_train.reshape(n, 4, 1)
y_train = np.sort(x_train, axis=1).reshape(n, 4,)

n = 1000
x_test = np.zeros((n,4))
for i in range(n):
    x_test[i,:] = np.random.permutation(50)[0:4]

x_test = x_test.reshape(n, 4, 1)
y_test = np.sort(x_test, axis=1).reshape(n, 4,)

print(x_test[0][0].T)
print(y_test[0])

input_shape = (4,1)

model = Sequential()
model.add(Conv1D(32, kernel_size=(2),
                 activation='relu',
                 input_shape=input_shape,
                 padding='same'))

model.add(Conv1D(64, (2), activation='relu', padding='same'))
model.add(MaxPooling1D(pool_size=(2)))
model.add(Reshape((64,2)))

model.add(Conv1D(32, (2), activation='relu', padding='same'))
model.add(MaxPooling1D(pool_size=(2)))

model.add(Flatten())
model.add(Dense(4))

model.compile(loss=keras.losses.mean_squared_error,
              optimizer=keras.optimizers.Adadelta(),
              metrics=['accuracy'])

epochs = 10
batch_size = 128
# Fit the model weights.
history = model.fit(x_train, y_train,
          batch_size=batch_size,
          epochs=epochs,
          verbose=1,
          validation_data=(x_test, y_test))
          


model.save('cnn_state.pkg')

