#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H
#include "DMXPacket.h"

/**
 *  Message Factory class. This class responsible for getting the message number.
 */

class MessageFactory
{
    public:
        MessageFactory();
        virtual ~MessageFactory();
        /**
        *Method to get the message number
        * @param dmxMsg a struct containing the message information
        * @return the message number
        */
        virtual int extractMessageNumber(const  DMXPacket* dmxMsg) const = 0;
    protected:
    private:
};

#endif // MESSAGEFACTORY_H
