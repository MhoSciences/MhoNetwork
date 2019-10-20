/** network_functions.c
 * This file contains the contents for the functions declared in the 
 * network_functions header file
 */
#include"network_functions.h"

void _setupNetworkDefaults(){
    dataBufferIndex = 0;
    for(dataBufferIndex; dataBufferIndex < MAXBUFFERLENGTH; dataBufferIndex++){
        dataBuffer[dataBufferIndex] = 0x00;
    }
    return;
}

char _getHardwareAddress(char byteNum){
    char highByte = 0x00; 
    char lowByte = 0x00;
    if(byteNum == 0x00){
        return lowByte;
    }   
    else{
        return highByte;
    }
}

int sendPacket(char packet[]){
   
}

int receivePacket(char packet[]){
    
}