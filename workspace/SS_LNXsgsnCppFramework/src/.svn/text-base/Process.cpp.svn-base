#include "Process.h"


Process::Process(const MessageFactory& messageFactory_, const StatesMap& statesMap_, const  DMXPacket* dmxMsg_):messageFactory(messageFactory_), statesMap(statesMap_)
{
    this->dmxMsg=dmxMsg_;

}

Process::~Process()
{
    //dtor
}
void Process::execute()
{
	cout<< "process execution started"<<endl;
    int msgNo= messageFactory.extractMessageNumber(dmxMsg);
    statesMap.getState(msgNo)->execute(dmxMsg);
}
