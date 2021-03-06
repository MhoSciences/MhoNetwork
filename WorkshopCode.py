import serial
import binascii
import time

def writeValues(Port,DataToWrite):
    return Port.write(DataToWrite);            

def readValues(Port, AmountToRead):
    return Port.read(AmountToRead);

def printSeparator():
    print("-----------------------------------------------")
    return;

def openPortV1():
    #Demonstration of a port being opened through setters

    #Create blank serial object
    OpenPort = serial.Serial();

    #Set the name of the port being used
    OpenPort.port = "/dev/ttyUSB0";

    #Set the baudrate for the port
    OpenPort.baudrate = 9600;

    #Set the amount of time for read()
    #to wait to receive a byte
    OpenPort.timeout = 1.0;

    #Set the number of bytes to be expected
    OpenPort.bytesize = serial.EIGHTBITS;

    #Set the parity to be used
    OpenPort.parity = serial.PARITY_EVEN;

    #Set the number of stop bits to be expected
    OpenPort.stopbits = serial.STOPBITS_ONE;
    
    return OpenPort;

def openPortV2():
    
    #Demonstration of a port being opened through constructor 
    OpenPort = serial.Serial("/dev/ttyUSB0", 1000000, 
                             serial.EIGHTBITS, 
                             serial.PARITY_EVEN, 
                             serial.STOPBITS_ONE, 1.0);
    
    return OpenPort;

def main():
    OpenPort = openPortV2();

    print("Port: ",OpenPort.name)

    #if(OpenPort.is_open == False):
        #OpenPort.open();
    
    printSeparator();
    
    ValuesToWrite = [16];
    while True:
        for k in range(len(ValuesToWrite)):
            writeValues(OpenPort, [16]);
            
        #print();
        time.sleep(0.5)
            #Demonstration of port being closed

    OpenPort.close();
            
    return;

main()

#use usb-devices to determine if the device is connected
#Changing to different bit modes will print differing values, could be used to print ASCII
