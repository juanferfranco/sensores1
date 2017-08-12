#!/usr/bin/python3
"""
This program illustrates how to read information from a file and send it 
to an arduino's serial port.
"""
import serial
import sys

def getSerialOrNone(port,speed, timeout):
    try:
        return serial.Serial(port, speed,timeout=timeout)
    except:
        return None

def main():
    ser = getSerialOrNone('COM3',9600,1)
    if(ser != None):
        print('Serial port opened')
    else:
        print('Serial port not available')
        sys.exit(-1)

    # Open a file
    try:
        fileTestVectors = open('testVectors.txt', 'r')
        
        while(True):
            for line in fileTestVectors:
                print(line)
                lineEncoded = line.replace('\n','').encode()
                i = 0
                while i < len(lineEncoded):
                    byteToSend = lineEncoded[i] 
                    if lineEncoded[i] == 92:
                        byteToSend = int(line[i+2:i+4],16)
                        i = i + 3
                    ser.write(byteToSend.to_bytes(1,byteorder='big'))
                    i = i + 1
                
                response = ser.read(1)
                if len(response) == 0:
                    print('timeout')
                else:
                    #TODO: 1 packet was received and processed
                    #How to know if a vector fails or passes?
                    print(response.decode())
            break
    except:
        exc_type, exc_value, tb = sys.exc_info()
        print('Exception Type: ' + str(exc_type))
        print('Exception Value: ' + str(exc_value))
        print('Exception Value: ' + str(tb))
        sys.exit(-1)

if __name__ == '__main__':
    main()
