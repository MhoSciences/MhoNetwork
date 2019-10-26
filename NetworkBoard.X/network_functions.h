/* ************************************************************************** */
/** network_functions.h
 * This header file defines the functions that will be used to setup the network
 * portions as well as send and receive packets. 
 */

#ifndef NETWORK_FUNCTIONS_H 
#define NETWORK_FUNCTIONS_H
#define MAXPACKETLENGTH 128 //Needs to be a number that reflects a single second's worth of data
#define MAXBUFFERLENGTH 500

int dataBufferIndex;
char dataBuffer[MAXBUFFERLENGTH];

void _setupNetworkDefaults(); 
/* _setupNetworkDefauts
 * This functions takes in an array of long integers and then setups the static
 * header elements for any possible packet dependent on the device parameters set
 * by hardware inputs.
 * 
 * Input:   packetHeader - an array of longs that represent the static header 
 *          segments that will be sent for a packet
 *          packetFootre - an array of longs that represent the static footer
 *          segments that will be sent for a packet
 * 
 * Output:  status - an integer value from 0x00 to 0x01 indicating success or failure
 */

char _getHardwareAddress(char byteNum);
/* _getHardwareAddress
 * This functions takes in a value and returns the corresponding high or low hardware address byte 
 * 
 * Input:   byteNum - a char value indicating which hardware address byte value 
 *                    to provide
 * 
 * Output:  hardwareAddr - a char value of either the high or low portion of the
 *                         hardware address
 */

void _setupStaticPacketHeaderBytes(char packet[]);
/* _setupStaticPacketHeaderBytes
 * This function takes in a single packet and places the static byte values into
 * the appropriate bit places.
 * 
 * Input: packet - an array of five longs representing an available packet
 * 
 * Output: N/A
 */

void _setupStaticPacketFooterBytes(char packet[]);
/* _setupStaticPacketFooterBytes
 * This function takes in a single packet and places the static byte values into
 * the appropriate bit places.
 * 
 * Input: packet - an array of five longs representing an available packet
 * 
 * Output: N/A
 */

int sendPacket(char packet[]);
/* sendPacket
 * This function takes in a packet array and sends the data through the 
 * appropriate communications registers
 * 
 * Input: packet - an array of five longs representing an available packet
 * 
 * Output: status - an integer value from 0x00 to 0x01 indicating success or failure
 */

int receivePacket(char packet[]);
/* receivePacket
 * This function takes in a packet array and fills it given the communication
 * network protocols available
 * 
 * Input: packet - an array of chars representing an available packet
 * 
 * Output: status - an integer value from 0x00 to 0x01 indicating success or failure
 */

#endif /* NETWORK_FUNCTIONS_H */
