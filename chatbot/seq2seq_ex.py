from seq2seq import *

exit_conditions = (":q", "quit", "exit")
while True:
    query = input("> ")
    if query in exit_conditions:
        break
    else:
        input_seq = make_predict_input(query)
        print(input_seq)
        sentence = generate_text(input_seq)
        print(sentence)



