#!/usr/bin/python3
#This script objective is to pilot the orderfor the light switch according to the light captor

import paho.mqtt.client as mqtt


def orderlight(info):
    a=0
    global reflight
    for i in range (2,len(info)-1):
        a=a*10+int(info[i])
    print(a)
    client.publish("light/order",a<reflight)
        

def raffraichirref():
    ref=open("/home/user/SSDinvite/PythonScript/ref.txt","r")
    refvalue=ref.read()
    ref.close()
    refvalue=refvalue.split("\n")
    reflight=int(refvalue[0])
    return reflight





def on_connect(client, userdata, flags, rc): #resultat de connexion
    print("Connected with result code "+str(rc))
    



def on_message(client, userdata, msg):      #action effectuer lors de la recpetion d'un message
    info=str(msg.payload)
    #print(msg.topic+" "+info)
    orderlight(info)


    
client = mqtt.Client(client_id="Pylight")
client.on_connect = on_connect
client.on_message = on_message

client.connect("localhost", 1883, 60)


client.subscribe("light/value") #recupere l'information de l'état des lumières

reflight=raffraichirref()







client.loop_forever()






client.loop_forever()
