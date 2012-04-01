#include <cstdlib>
#include "Framework.h"

Framework::Framework()
{
    iniFileReader_ = INIFileReader::getIniFileReader();
}

Framework::~Framework()
{
    instanceFlag = false;
	if(iniFileReader_ != NULL)
	{
		iniFileReader_ = NULL;
	}
}

bool Framework::instanceFlag = false;

Framework* Framework::framework = NULL;

Framework* Framework::getInstance()
{
    if(! instanceFlag)
    {
        framework = new Framework();
        instanceFlag = true;
        cout<< "framework instantiated"<<endl;
        return framework;
    }
    else
    {
    	cout<< "get current framework instance"<<endl;
    return framework;
    }
}


void Framework::init(const MessageFactory* messageFactory, const StatesMap* statesMap, const char* configFileName)
{
	cout << "framework initiated" << endl;
	ChannelConfigMap chConfigMap;
		DestConfigMap destConfigMap;

	loadConfig(configFileName, &chConfigMap, &destConfigMap);
	DMXPacket* dmxMsg = new DMXPacket;
	dmxMsg->header.messageNumber = 6523;
	int poolSize = 4;
	cout << "received message with message number"
			<< dmxMsg->header.messageNumber << endl;
	Process proc(*messageFactory, *statesMap, dmxMsg);
	ProcessExecutor procExe(poolSize);
	procExe.submit(&proc);




}

int Framework::loadConfig(const char* filename, ChannelConfigMap* chConfigMap, DestConfigMap* destConfigMap)
{
	cout << "entering loadConfig" << endl;
    iniFileReader_->readConfigParameters(filename);

    // parse config file and assign to struct
    // UDP CHANNEL
    //ChannelConfiguration* udpChannel = (ChannelConfiguration*)malloc(sizeof(ChannelConfiguration));
    ChannelConfiguration* udpChannel = new ChannelConfiguration();
    string channelId = iniFileReader_->getStringParam("UDP_CHANNEL_ID");

    udpChannel->channelClass = iniFileReader_->getStringParam("UDP_CHANNEL_CLASS");
    udpChannel->dataProcessorClass = iniFileReader_->getStringParam("UDP_CHANNEL_DATA_PROC_CLASS");
    udpChannel->type = iniFileReader_->getStringParam("UDP_CHANNEL_TYPE");
    udpChannel->capacity = iniFileReader_->getIntParam("UDP_CHANNEL_CAPACITY");
    udpChannel->port = iniFileReader_->getIntParam("UDP_CHANNEL_PORT");
        // insert key and struct to map
    chConfigMap->insert(std::make_pair(channelId, *udpChannel));
    // parse config file and assign to struct
    // DMX CHANNEL
    ChannelConfiguration* dmxChannel = new ChannelConfiguration();
    channelId = iniFileReader_->getStringParam("DMX_CHANNEL_ID");

    dmxChannel->channelClass.assign(iniFileReader_->getStringParam("DMX_CHANNEL_CLASS"));
    dmxChannel->dataProcessorClass.assign(iniFileReader_->getStringParam("DMX_CHANNEL_DATA_PROC_CLASS"));
    dmxChannel->type.assign(iniFileReader_->getStringParam("UDP_CHANNEL_TYPE"));
    dmxChannel->capacity = iniFileReader_->getIntParam("DMX_CHANNEL_CAPACITY");
    dmxChannel->family = iniFileReader_->getStringParam("DMX_CHANNEL_FAMILY");
    dmxChannel->processId = iniFileReader_->getStringParam("DMX_CHANNEL_PROCESS_ID");
    dmxChannel->focus = iniFileReader_->getStringParam("DMX_CHANNEL_FOCUS");

    // insert key and struct to map
    chConfigMap->insert(std::make_pair(channelId, *dmxChannel));

    // parse config file and assign to struct
    // CLI CHANNEL
    ChannelConfiguration* cliChannel = new ChannelConfiguration();
	channelId = iniFileReader_->getStringParam("DMX_CHANNEL_ID");

	cliChannel->channelClass.assign(iniFileReader_->getStringParam("CLI_CHANNEL_CLASS"));
	cliChannel->dataProcessorClass.assign(iniFileReader_->getStringParam("CLI_CHANNEL_DATA_PROC_CLASS"));
	cliChannel->type.assign(iniFileReader_->getStringParam("CLI_CHANNEL_TYPE"));
	cliChannel->capacity = iniFileReader_->getIntParam("CLI_CHANNEL_CAPACITY");
	cliChannel->port = iniFileReader_->getIntParam("CLI_CHANNEL_PORT");

    // insert key and struct to map
    chConfigMap->insert(std::make_pair(channelId, *cliChannel));

    //"0" DESTINATION
    DestinationConfiguration* zeroDestination = new DestinationConfiguration();
    string destinationId = iniFileReader_->getStringParam("0_DESTINATION_ID");

    zeroDestination->host.assign(iniFileReader_->getStringParam("0_DESTINATION_HOST"));
    zeroDestination->port = iniFileReader_->getIntParam("0_DESTINATION_PORT");

    destConfigMap->insert(std::make_pair(destinationId, *zeroDestination));

    //TRHR DESTINATION
    DestinationConfiguration* trHrDestination = new DestinationConfiguration();
	destinationId = iniFileReader_->getStringParam("TRHR_DESTINATION_ID");

	trHrDestination->host.assign(iniFileReader_->getStringParam("TRHR_DESTINATION_HOST"));
	trHrDestination->port = iniFileReader_->getIntParam("TRHR_DESTINATION_PORT");

	destConfigMap->insert(std::make_pair(destinationId, *trHrDestination));

    //A66 DESTINATION
    DestinationConfiguration* a66Destination = new DestinationConfiguration();
	destinationId = iniFileReader_->getStringParam("A66_DESTINATION_ID");

	a66Destination->computerId.assign(iniFileReader_->getStringParam("A66_COMPUTER_ID"));
	a66Destination->family.assign(iniFileReader_->getStringParam("A66_FAMILY"));
	a66Destination->processId.assign(iniFileReader_->getStringParam("A66_PROCESS_ID"));
	a66Destination->focus.assign(iniFileReader_->getStringParam("A66_FOCUS"));

	destConfigMap->insert(std::make_pair(destinationId, *a66Destination));

	//CLI DESTINATION
	DestinationConfiguration* cliDestination = new DestinationConfiguration();
	destinationId = iniFileReader_->getStringParam("CLI_DESTINATION_ID");

	cliDestination->host.assign(iniFileReader_->getStringParam("CLI_DESTINATION_HOST"));
	cliDestination->port = iniFileReader_->getIntParam("CLI_DESTINATION_PORT");

	destConfigMap->insert(std::make_pair(destinationId, *cliDestination));

	return 0;
}

 void Framework::send(DMXPacket data, const string& chKey, const string& destKey)
 {
	 cout<<"output message with message number "<< data.header.messageNumber<<" sent"<<endl;
 }
