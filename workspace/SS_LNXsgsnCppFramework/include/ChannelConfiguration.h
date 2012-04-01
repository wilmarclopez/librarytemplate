#ifndef CHANNELCONFIGURATION_H
#define CHANNELCONFIGURATION_H
#include <string>
using namespace std;

typedef struct ChannelConfiguration_
{
	string channelClass;
	string dataProcessorClass;
    string type;
    int capacity;
    string family;
    string processId;
    string focus;
    int port;
}ChannelConfiguration;

#endif // CHANNELCONFIGURATION_H
