from tensorflow import keras
import numpy as np

model = keras.models.load_model('cnn_state.pkg')

test_list = [15,44,31,8]
pred = model.predict(np.asarray(test_list).reshape(1,4,1))
print(test_list)
print(pred)

print([np.asarray(test_list).reshape(4,)[np.abs(np.asarray(test_list).reshape(4,) - i).argmin()] for i in list(pred[0])])
