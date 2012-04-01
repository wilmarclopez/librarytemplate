#ifndef DMXPACKET_H
#define DMXPACKET_H

#define BODY_SIZE 4098

/**
*   DMX header that identifies the message type and other info without
* ever needing to deduce na body first.
*/
typedef struct DMXHeader_
{
    int messageNumber;
}DMXHeader;

/**
*   Data type returned and received by the CommunicationServices.
*   All data received are DMX packets regardless of transpo protocol.
*/
typedef struct DMXPacket_
{
    DMXHeader header;
    unsigned char body[BODY_SIZE];
}DMXPacket;

#endif // DMXPACKET_H
