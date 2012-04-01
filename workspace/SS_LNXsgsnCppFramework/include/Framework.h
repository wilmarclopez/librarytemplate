#ifndef FRAMEWORK_H
#define FRAMEWORK_H
#include <string>
#include "DMXPacket.h"
#include "ConfigMap.h"
#include "ProcessExecutor.h"
#include "INIFileReader.h"
#include <iostream>
#include "../include/ChannelConfiguration.h"
#include "../tools/gtest/include/gtest/gtest_prod.h"
using namespace std;

/**
 *  Framework class. Singleton class to launch the framework.
 */

class Framework {
public:
	/**
	 * a private constructor.
	 * details
	 */
	Framework();
	~Framework();
	/**
	 * Method to get the  intance of the singleton class.
	 * @return  pointer to the singleton framework class
	 */
	static Framework* getInstance();

	/**
	 *  Method to launch the framework.
	 * @param messageFactory reference to the messageFactory
	 * @param statesMap reference to the statesMap
	 * @param configFileName reference to the configuration file
	 */
	void init(const MessageFactory* messageFactory, const StatesMap* statesMap,
			const char* configFileName);

	/**
	 *  Method to send the output message to its destination.
	 * @param data the message to be sent
	 * @param chKey an identifier for the channel to be used
	 * @param destKey  an identifier for the destination of the message
	 */
	void send(DMXPacket data, const string& chKey, const string& destKey);



protected:
private:
	FRIEND_TEST(FrameWorkTest,  initTest);
	/**
	 * a private variable.
	 * used as a flag to keep track if the class has already been instantiated
	 */
	static bool instanceFlag;

	/**
	 * a private variable.
	 * holder of the instance of the class
	 */
	static Framework *framework;

	/**
	 * a private variable.
	 * pointer to the instance of the messageFactory
	 */
	const MessageFactory* msgFactory;

	/**
	 * a private variable.
	 * pointer to the instance of the statesMap
	 */
	const StatesMap* statesMap;

	/**
	 * a private variable.
	 * the process Executor manages the execuiton of threads
	 */
	ProcessExecutor procExecutor;

	/**
	 * a private variable.
	 * an instance of the class that handles the channels
	 */
	// CommunicationServices commServices;

	INIFileReader* iniFileReader_;
	/**
		 *  Method to load and parse the configuration file.
		 * @param filename the name of the configuration file
		 * @param chConfigMap the map of channel configurations
		 * @param destConfigMap  the map of destination configurations
		 */
	int loadConfig(const char* filename, ChannelConfigMap* chConfigMap,
				DestConfigMap* destConfigMap);

};

#endif // FRAMEWORK_H
