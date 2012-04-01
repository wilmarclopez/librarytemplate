#ifndef DESTINATIONCONFIGURATION_H
#define DESTINATIONCONFIGURATION_H
#include<string>
using namespace std;

typedef struct DestinationConfiguration_
{
    string host;
    string port;
    string computerId;
    string family;
    string processId;
    string focus;
}DestinationConfiguration;

#endif // DESTINATIONCONFIGURATION_H
