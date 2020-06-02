#!/usr/bin/python3
#This script objective is to pilot the order with the value obtained from the captor

import paho.mqtt.client as mqtt
from inotify_simple import INotify, flags
from datetime import datetime

def lightTreat(info,ind):
    global ref
    a=int(info[2:-1])
    msg=a<ref[ind]
    return msg

def tempTreat(info,ind):
    global ref
    a=float(info[2:-1])
    msg=ref[101+ind]-a
    return msg

def motionTreat():
    

def orderIssue(info,subject):
    heure=str(datetime.now().time())
    h=int(heure[0:2])*100+int(heure[3:5])
    if subject[:5]=='light':
        if h>ref[112] and h<ref[113] :
            msg=lightTreat(info,int(subject[5:]))
        else :
            msg=False
    elif subject[:4]=='temp':
        msg=tempTreat(info,int(subject[4:]))
    elif subject[:6]=='motion':
        if h<ref[112] or h > ref[113]:
            if info=='1':
                msg=True
            else
                msg=False
        else 
            msg=False
            
    client.publish('order/'+subject,msg)
              
    
    

def strToValue(subject):
    val=0
    for i in subject:
        val=val+ord(i)
    return val    

def raffraichirref():
    global ref
    ref.clear()
    refFile=open("/home/user/SSDinvite/PythonScript/ref.txt","r")
    refvalue=refFile.read()
    refFile.close()
    refvalue=refvalue.split("\n")
    for i in refvalue:
        if i !='':
            ref.append(float(i))
            


def on_connect(client, userdata, flags, rc): #resultat de connexion
    print("Connected with result code "+str(rc)+"\n")
    
def on_message(client, userdata, msg):      #action effectuer lors de la recpetion d'un message
    info=str(msg.payload)
    orderIssue(info,str(msg.topic)[6:])


#execution of code
inotify = INotify()
watch_flags = flags.MODIFY #only survey the modification
wd = inotify.add_watch('/home/user/SSDinvite/PythonScript/ref.txt', watch_flags) #specify the path of folder or file to watch


client = mqtt.Client(client_id="Pylight")
client.on_connect = on_connect
client.on_message = on_message

client.username_pw_set("system", password="modif")

client.connect("localhost", 1883, 60)
client.loop_start()


client.subscribe("value/#") #recupere l'information de l'état des lumières

ref=[]
raffraichirref()


while(1):
    for event in inotify.read():
        raffraichirref()
        print(ref)

client.loop_stop(force=False)
