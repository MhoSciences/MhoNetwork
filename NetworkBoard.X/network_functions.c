/** network_functions.c
 * This file contains the contents for the functions declared in the 
 * network_functions header file
 */
#include"network_functions.h"

int global_data;

int _setupNetworkDefaults(char packetHeader[]){
    
    packetHeader[0] = 0x01; //SOH byte
    packetHeader[1] = _getHardwareAddress(0x01); //HIDH: Hardware address high byte
    packetHeader[2] = _getHardwareAddress(0x00); //HIDL: Hardware address low byte
    packetHeader[3] = 0x00; //SIDH: Software Address high byte
    packetHeader[4] = 0x00; //SIDL: Software Address low byte
    packetHeader[5] = 0x00; //QUEUE: Available packet storage left
    packetHeader[6] = 0x00; //PRIORITY: Priority byte  
    packetHeader[7] = 0x00; //MSGH: Message count high byte
    packetHeader[8] = 0x00; //MSGL: Message count low byte
    packetHeader[9] = 0x00; //FLG: Flag byte
    packetHeader[10] = 
}

char _getHardwareAddress(char byteNum){
    char highByte = 0x00; 
    char lowByte = 0x00;
    if(byteNum == 0x00){
        return highByte;
    }   
    else{
        return lowByte;
    }
}

int sendPacket(long packet[]){
   
}

int receivePacket(long packet[]){
    
}