#ifndef PROCESS_H
#define PROCESS_H
#include "DMXPacket.h"
#include "MessageFactory.h"
#include "StatesMap.h"


/**
 *  Process class. This class encapsulates the entire processing of the message.
 */

class Process
{
    public:
        /**
        *Constructor for the process
        * @param messageFactory a reference to the messageFactory
        * @param statesMap a reference to the statesMap
        * @param dmxMsg a struct containing the message information        *
        */
        Process(const MessageFactory& messageFactory_, const StatesMap& statesMap_, const  DMXPacket* dmxMsg_);
        virtual ~Process();
         /**
        *Method to execute the process
        */
        void execute();
    protected:
    private:
    const MessageFactory& messageFactory;
    const StatesMap& statesMap;
    const DMXPacket* dmxMsg;

};

#endif // PROCESS_H
