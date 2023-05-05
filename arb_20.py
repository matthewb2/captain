from binance import Client
from tqdm.autonotebook import tqdm
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout, LSTM

def get_binance_data(ticker, interval='15m', start='20 Apr 2023', end=None):
  client = Client()
  intervals = {
      '15m': Client.KLINE_INTERVAL_15MINUTE,
      '1h':  Client.KLINE_INTERVAL_1HOUR,      
      '4h':  Client.KLINE_INTERVAL_4HOUR,
      '1d':  Client.KLINE_INTERVAL_1DAY
  }
  interval = intervals.get(interval, '4h')
#   print(f'Historical interval {interval}')
  klines = client.get_historical_klines(symbol=ticker, interval=interval, start_str=start, end_str=end)
  data = pd.DataFrame(klines)
  data.columns = ['open_time','open', 'high', 'low', 'close', 'volume','close_time', 'qav','num_trades','taker_base_vol','taker_quote_vol', 'ignore']
  data.index = [pd.to_datetime(x, unit='ms').strftime('%Y-%m-%d %H:%M:%S') for x in data.open_time]
  usecols=['open', 'high', 'low', 'close', 'volume', 'qav','num_trades','taker_base_vol','taker_quote_vol']
  data = data[usecols]
  data = data.astype('float')
  return data


def current():
    df = get_binance_data('ARBUSDT')
    close = df['close']
    return close[-1] #last element
    

def question():
    df = get_binance_data('ARBUSDT')

    #prepare data
    scaler = MinMaxScaler(feature_range=(0,1))
    scaled_data = scaler.fit_transform(df['close'].values.reshape(-1,1))

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
    model.fit(x_train, y_train, epochs=30, batch_size=30)


    #data = pdr.get_data_yahoo('^kq11', start='2023-01-02', end="2023-04-13")
    data = get_binance_data('ARBUSDT', '15m', '20 Apr 2023', '24 Apr 2023')
    #test_data = pdr.get_data_yahoo('^kq11', start='2023-02-13')
    test_data = get_binance_data('ARBUSDT', '15m', '24 Apr 2023')
    actual_prices = test_data['close'].values

    total_dataset = pd.concat((data['close'], test_data['close']), axis=0)

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
    #plt.show()

    #Predict Next Day

    real_data = [model_inputs[len(model_inputs)+1 - 20:len(model_inputs+1), 0]]
    real_data = np.array(real_data)
    real_data = np.reshape(real_data, (real_data.shape[0], real_data.shape[1],1))

    prediction = model.predict(real_data)
    prediction = scaler.inverse_transform(prediction)
    print(f"Prediction: {prediction}")
    print(test_data.tail())
    
    del model
    #keras.backend.clear_session()
    return prediction