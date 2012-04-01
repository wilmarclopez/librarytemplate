/*
 * FrameworkTest.cpp
 *
 *  Created on: Mar 14, 2012
 *      Author: wil
 */

#include  <gtest/gtest.h>
#include "Framework.h"

TEST(FrameWorkTest,  initTest)
{

	class RanapMessageFactory: public MessageFactory
	{
	    public:
	        RanapMessageFactory(){}
	        ~RanapMessageFactory(){}
	        /**
	        *Method to get the message number
	        * @param dmxMsg a struct containing the message information
	        * @return the message number
	        */
	        int extractMessageNumber(const  DMXPacket* dmxMsg) const{
	            cout<< "extracting message number"<<endl;
	            return dmxMsg->header.messageNumber;
	        }
	    protected:
	    private:
	};
	class RanapBaseState: public State
		{
		    public:
		        RanapBaseState(){}
		        ~RanapBaseState(){}
		        /**
		        *Method to execute the processing of the message
		        * @param dmxMsg a struct containing the message information
		        */
		        void execute(const DMXPacket* dmxMsg) const{
		            cout<< "creating output message"<< endl;
		            DMXPacket* outputMsg= new DMXPacket;
		            outputMsg->header.messageNumber= 123;
		            cout<< "output message number is"<< outputMsg->header.messageNumber<<endl;
		            Framework::getInstance()->send(*outputMsg, "chKey", "destKey");


		        }
		        string getName(){
		        	return stateName;
		        }
		//        /**
		//        *Method to create the output message
		//        */
		//        virtual DMXPacket* createOutputMessage()=0;
		    protected:
		        string stateName;
		    private:

		};

		class DummyState1: public RanapBaseState
		{
		    public:
		        DummyState1(){
		            //ctor
		        	stateName="dummystate1";
		            cout<<"entered dummystate1"<<endl;
		        }
		    protected:
		    private:

		};

	class RanapStatesMap:public StatesMap
	{
	    public:
	        RanapStatesMap(){}
	        virtual ~RanapStatesMap(){}
	        /**
	        *Method to determine the state to be executed
	        * @param msgNo a integer representing the message number
	        * @return the state to be executed
	        */
	        virtual const  State* getState(int msgNo) const{
	            cout<< "returning the corresponding state for "<<msgNo<<endl;

	            switch (msgNo){
	       //         case 6523: return new DummyState1();
	                default:  return new DummyState1();
	            }
	        }
	    protected:
	    private:
	};

     RanapMessageFactory* rmf = new RanapMessageFactory();
     RanapStatesMap* rms=new RanapStatesMap();
	Framework::getInstance()->init(rmf,rms ,  "../build/config-sgsnRanapHr.INI");
	ASSERT_TRUE(Framework::getInstance()->instanceFlag);
	delete rmf;
	delete rms;
}
