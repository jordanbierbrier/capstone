import serial
import time

print("Start")
port="COM5" 
bluetooth=serial.Serial(port, 9600)#Start communications with the bluetooth unit
print("Connected")
bluetooth.flushInput() #This gives the bluetooth a little kick
for i in range(50):
	bluetooth.write(b"ack")#These need to be bytes not unicode, plus a number
	input_data=bluetooth.readline()#This reads the incoming data. 
	print(input_data.decode())#These are bytes coming in so a decode is needed
	#time.sleep(0.1) #A pause between bursts
bluetooth.write(b"Door bell")#These need to be bytes not unicode, plus a number
bluetooth.close() #Otherwise the connection will remain open until a timeout which ties up the
print("Done")