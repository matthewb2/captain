from binance import Client
import pandas as pd
import numpy as np
import time
import keyboard

import requests
 
def post_message(token, channel, text):
    response = requests.post("https://slack.com/api/chat.postMessage",
        headers={"Authorization": "Bearer "+token},
        data={"channel": channel,"text": text}
    )
    print(response)
 


def get_binance_data(ticker, interval='1m', start='22 May 2023', end=None):
  client = Client()
  klines = client.get_historical_klines(symbol=ticker, interval=interval, start_str=start, end_str=end)
  data = pd.DataFrame(klines)
  data.columns = ['open_time','open', 'high', 'low', 'close', 'volume','close_time', 'qav','num_trades','taker_base_vol','taker_quote_vol', 'ignore']
  data.index = [pd.to_datetime(x, unit='ms').strftime('%Y-%m-%d %H:%M:%S') for x in data.open_time]
  usecols=['open', 'high', 'low', 'close', 'volume', 'qav','num_trades','taker_base_vol','taker_quote_vol']
  data = data[usecols]
  data = data.astype('float')
  return data


def get_std_data(coin):
    df = get_binance_data(coin)

    #rows_count = df[df.columns[3]].count()

    vals = df['close'].tail(20).to_numpy()

    std = np.std(vals)
    #print(std)
    return std
    
#for row in array:

def get_last(coin):
    df = get_binance_data(coin)
    return df['close'].tail(1).to_numpy()[0]


if __name__ == "__main__":
    print ("starting...")
    #coin = 'ACHUSDT'
    #coin2 = 'BTCUSDT'
    cn = ['GALAUSDT', 'ACHUSDT', 'BTCUSDT', 'ARPAUSDT', 
            'XRPUSDT','GMTUSDT','SUIUSDT','KLAYUSDT']
    last ={}
    for coin in cn:
        last[coin] = get_last(coin)
    print(last)
    while True:
        if keyboard.is_pressed("q"):
            print("---- end -----")
            break
        for coin in cn:
            df=get_binance_data(coin)
            price = df['close'].tail(1).to_numpy()[0]
            std = get_std_data(coin)
            print("coin:{2} price: {0} std:{1}".format(price, std, coin.replace('USDT','')))
            myToken = "xoxb-5283584414615-5310812738449-qkMquccnnpmQsRp6UHu79qM8"
            message="{0} {1}".format(coin.replace('USDT',''), price)
            if (abs(last[coin]-price) > std*1.5):
                print("{0} {1}".format(coin, price))
                post_message(myToken,"#general",message)
            last[coin] = price
        time.sleep(20)
            
