import time
import keyboard
from arb_20 import question, current
from time import gmtime, strftime
import json, math

def hello(pos, last):
    #print ("hello")
    real = current()
    if (pos == "long"):
        if (real > last):
            result = 1
        else: result = -1
    
    if (pos == "short"):
        if (real < last):
            result = 1
        else: result = -1
    
    #prediction next price
    exp = question()
    exp = exp[0][0]
    if (exp > real):
        pos = "long"
    else: pos = "short"
    return pos, exp, result, real
    

if __name__ == "__main__":
    
    exp= 0
    prev=0
    pos="long"
    pre_pos = "long"
    gain =0
    total = 0
    deposit = 0
    rate=0
    leverage=10
    mm = ""
    file_path = "./balance.json"

    with open(file_path, "r") as json_file:
        json_data = json.load(json_file)
        gain = json_data['posts'][0]['gain']
        deposit = json_data['posts'][0]['deposit']
        total = json_data['posts'][0]['total']
        prev = json_data['posts'][0]['exp']
    
    print ("starting...")
    while True:
        if keyboard.is_pressed("q"):
            print("---- end -----")
            break
        mm = strftime("%M", gmtime())
        print (strftime("%H:%M:%S", gmtime()))
        if (mm == "01" or mm == "16" or mm == "31" or mm == "46"):
            pre_pos = pos
            pos, exp, result, last = hello(pos, prev)
            total +=1
            if (result == 1):
                gain += 1
            if (pre_pos != pos):
                prev=last
            rate = leverage*100*result*abs(last-prev)/prev
            deposit += 100000*leverage*result*abs(last-prev)/prev
            print ("winner:",gain)
            print ("return rate: {:.2f}%".format(rate))
            print ("total deposit: ",format(round(deposit),","))
            print ("position: ",pos)
            print ("expected price: ",exp)
            print ("total trial: ",total)
            data = {}
            data['posts'] = []
            data['posts'].append({
                "total": total,
                "exp":last,
                "deposit": round(deposit),
                "gain": gain
            })
            with open(file_path, 'w') as outfile:
                json.dump(data, outfile, indent=4)
        time.sleep(35)
        
        