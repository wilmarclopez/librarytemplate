#ifndef CONFIGMAP_H
#define CONFIGMAP_H
#include <map>
#include <string>
#include "ChannelConfiguration.h"
#include "DestinationConfiguration.h"

using namespace std;

typedef map<string, ChannelConfiguration> ChannelConfigMap;
typedef map<string, DestinationConfiguration> DestConfigMap;


#endif // CONFIGMAP_H_INCLUDED
