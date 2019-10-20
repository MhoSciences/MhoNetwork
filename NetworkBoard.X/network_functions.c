/** network_functions.c
 * This file contains the contents for the functions declared in the 
 * network_functions header file
 */
#include"network_functions.h"

int global_data;

int _setupNetworkDefaults(char packetHeader[]){
    
    packetHeader[0] = 0x01; //SOH byte
    packetHeader[1] = 0x00; //DIDH: Destination hardware address high byte
    packetHeader[2] = 0x00; //DIDL: Destination hardware address low byte
    packetHeader[3] = 0x00; //DIDS: Destination software address
    packetHeader[3] = 0x00; //SIDH: Source hardware address high byte
    packetHeader[4] = 0x00; //SIDL: Source hardware address low byte
    packetHeader[5] = 0x00; //SIDS: Source ID software address
    packetHeader[6] = 0x00; //MEM: Memory available on hardware address
    packetHeader[7] = 0x00; //QUEUE: Available packet storage left
    packetHeader[8] = 0x00; //PRIORITY: Priority byte  
    packetHeader[9] = 0x00; //MSGH: Message count high byte
    packetHeader[10] = 0x00; //MSGL: Message count low byte
    packetHeader[11] = 0x00; //FLG: Flag byte
    packetHeader[12] = 0x02; //INSTR: a value from 0x00 to 0x1F indicating a specific instruction
    packetHeader[13] = 0x03; //ETX byte
    packetHeader[14] = 0x00; //CHKSUM1: First checksum byte
    packetHeader[15] = 0x00; //CHKSUM2: Second checksum byte
    packetHeader[16] = 0x04; //EOT byte
    
    return;
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