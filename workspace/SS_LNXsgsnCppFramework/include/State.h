#ifndef STATE_H
#define STATE_H
#include "DMXPacket.h"
#include <iostream>

using namespace std;

/**
 *  State class. This class process the message.
 */

class State
{
    public:
        State();
        virtual ~State();
        /**
        *Method to execute the processing of the message
        * @param dmxMsg a struct containing the message information
        */
        virtual void execute(const DMXPacket* dmxMsg) const=0;
    protected:
    private:
};

#endif // STATE_H
