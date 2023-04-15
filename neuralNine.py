# LSTM for international airline passengers problem with regression framing
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import pandas_datareader as web
import datetime as dt

from sklearn.preprocessing import MinMaxScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout, LSTM


# load test data
import mpu.pd
from pandas_datareader import data as pdr
import yfinance as yfin

yfin.pdr_override()

df = pdr.get_data_yahoo('^ks11', start='2022-06-20')

#training_set = df.iloc[:,4:5].values

#prepare data
scaler = MinMaxScaler(feature_range=(0,1))
scaled_data = scaler.fit_transform(df['Close'].values.reshape(-1,1))

prediction_days = 20

x_train = []
y_train = []


for x in range(prediction_days, len(scaled_data)):
    x_train.append(scaled_data[x -prediction_days:x, 0])
    y_train.append(scaled_data[x, 0])
    

x_train = np.array(x_train)
y_train = np.array(y_train)


print(np.array(x_train).shape)

x_train = np.reshape(x_train, (x_train.shape[0], x_train.shape[1],1))


#build model
model = Sequential()

model.add(LSTM(units=10, return_sequences=True, input_shape=(x_train.shape[1], 1)))
model.add(Dropout(0.2))
model.add(LSTM(units=10, return_sequences=True))
model.add(Dropout(0.2))
model.add(LSTM(units=10))
model.add(Dropout(0.2))
model.add(Dense(units=1))

model.compile(optimizer='adam', loss='mean_squared_error')
model.fit(x_train, y_train, epochs=25, batch_size=32)


test_data = pdr.get_data_yahoo('^ks11', start='2022-06-20')
data = pdr.get_data_yahoo('^ks11', start='2023-01-01')
actual_prices = test_data['Close'].values

total_dataset = pd.concat((data['Close'], test_data['Close']), axis=0)

model_inputs= total_dataset[len(total_dataset) - len(test_data) - 20:].values
model_inputs= model_inputs.reshape(-1,1)
model_inputs = scaler.transform(model_inputs)

#Make predictions on test data

x_test = []

for x in range(20, len(model_inputs)):
    x_test.append(model_inputs[x-20:x, 0])
    

x_test = np.array(x_test)

x_test = np.reshape(x_test, (x_test.shape[0], x_test.shape[1], 1))

predicted_prices = model.predict(x_test)
predicted_prices = scaler.inverse_transform(predicted_prices)

plt.plot(actual_prices, color="black", label="actual")
plt.plot(predicted_prices, color="green", label="predicted")
plt.show()
