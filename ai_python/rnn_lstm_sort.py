import numpy as np

# Keras
from keras.utils import to_categorical
from keras.models import Model
from keras.layers import Input
from keras.layers import LSTM
from keras.layers import Dense


n_features = 50
n_steps_in = 6
n_steps_out = 6

# returns train, inference_encoder and inference_decoder models
def models(n_input, n_output, n_units):
    """
    Create models for encoder-decoder neural network

    Parameters
    ----------
    n_input : int
        Length of input sequence, e.g number of integers to sort
    n_output : int
        Length of output sequence, e.g number of integers sorted
    n_units : int
        Cells to create in the encoder and decoder models

    Returns
    -------
    model, encoder_model, decoder_model
    """
    # training encoder
    encoder_inputs = Input(shape=(None, n_input))
    encoder = LSTM(n_units, return_state=True)
    encoder_outputs, state_h, state_c = encoder(encoder_inputs)
    encoder_states = [state_h, state_c]

    
    # training decoder
    decoder_inputs = Input(shape=(None, n_output))
    decoder_lstm = LSTM(n_units, return_sequences=True, return_state=True)
    decoder_outputs, _, _ = decoder_lstm(decoder_inputs, initial_state=encoder_states)
    decoder_dense = Dense(n_output, activation='softmax')
    decoder_outputs = decoder_dense(decoder_outputs)
    model = Model([encoder_inputs, decoder_inputs], decoder_outputs)

    # inference encoder
    encoder_model = Model(encoder_inputs, encoder_states)

    # inference decoder
    decoder_state_input_h = Input(shape=(n_units,))
    decoder_state_input_c = Input(shape=(n_units,))
    decoder_states_inputs = [decoder_state_input_h, decoder_state_input_c]
    decoder_outputs, state_h, state_c = decoder_lstm(decoder_inputs, initial_state=decoder_states_inputs)
    decoder_states = [state_h, state_c]
    decoder_outputs = decoder_dense(decoder_outputs)
    decoder_model = Model([decoder_inputs] + decoder_states_inputs, [decoder_outputs] + decoder_states)

    return model, encoder_model, decoder_model

train, encoder, decoder = models(n_features, n_features, 128)
train.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])

def generate_sequence(length, max_number):
    """
    Generate a sequence of random numbers

    Parameters
    ----------
    length : int
        Length of the sequence
    max_number : int
        Maximum number value

    Returns
    -------
    sequence
    """
    sequence = np.random.randint(max_number, size=length)
    return sequence
def one_hot_decode(encoded_seq):
    """
    Decode a one hot encoded string

    Parameters
    ----------
    encoded_seq : int
        Length of the sequence

    Returns
    -------
    sequence decoded
    """
    return [np.argmax(vector) for vector in encoded_seq]
def generate_dataset(n_input, max_number, n_samples):
    """
    Generate a number of sequences to use to train a model

    Parameters
    ----------
    n_input : int
        Length of input sequence, e.g number of integers to sort
    max_number : int
        Maximum number value
    n_samples : int
        Number of samples to generate

    Returns
    -------
    X1, X2, y
        Train and target datasets
    """
    X1, X2, y = list(), list(), list()
    for _ in range(n_samples):
        # generate source sequence
        source = generate_sequence(n_input, max_number)
        # define target sequence
        target = sorted(source)
        # create padded input target sequence
        target_in = [0] + target[:-1]
        # encode
        src_encoded = to_categorical(source, num_classes=max_number)
        tar_encoded = to_categorical(target, num_classes=max_number)
        tar2_encoded = to_categorical(target_in, num_classes=max_number)
        # store
        X1.append(src_encoded)
        X2.append(tar2_encoded)
        y.append(tar_encoded)

    return np.array(X1), np.array(X2), np.array(y)

n_samples = 1
X1, X2, y = generate_dataset(n_steps_in, n_features, n_samples)
print(X1.shape, X2.shape, y.shape)
print('X1=%s, X2=%s, target=%s' % (one_hot_decode(X1[0]), one_hot_decode(X2[0]), one_hot_decode(y[0])))

n_samples = 50000
X1, X2, y = generate_dataset(n_steps_in, n_features, n_samples)
print(X1.shape, X2.shape, y.shape)

train.fit([X1, X2], y, epochs=1)

def predict_sequence(encoder, decoder, source, n_steps, max_number):
    """
    Predict target sequence given 

    Parameters
    ----------
    encoder : model
        Encoder when making a prediction for a sequence
    decoder : model
        Decoder when making a prediction for a sequence
    source : array
        Encoded sequence
    n_steps: int
        Number of numbers to predict
    max_number : int
        Maximum number value for reshape

    Returns
    -------
    list with the target sequence predicted
    """
    # encode
    state = encoder.predict(source)
    # start of sequence input
    target_seq = np.array([0.0 for _ in range(max_number)]).reshape(1, 1, max_number)
    
    # collect predictions
    output = list()
    for t in range(n_steps):
        # predict next char
        yhat, h, c = decoder.predict([target_seq] + state)
        # store prediction
        output.append(yhat[0,0,:])
        # update state
        state = [h, c]
        # update target sequence
        target_seq = yhat
    return np.array(output)

total, correct = 100, 0
for _ in range(total):
    X1, X2, y = generate_dataset(n_steps_in, n_features, 1)
    target = predict_sequence(encoder, decoder, X1, n_steps_out, n_features)
    if np.array_equal(one_hot_decode(y[0]), one_hot_decode(target)):
        correct += 1
print('Accuracy: %.2f%%' % (float(correct)/float(total)*100.0))

for _ in range(10):
	X1, X2, y = generate_dataset(n_steps_in, n_features, 1)
	target = predict_sequence(encoder, decoder, X1, n_steps_out, n_features)
	print('Input=%s target=%s, prediction=%s' % (one_hot_decode(X1[0]), one_hot_decode(y[0]), one_hot_decode(target)))
    