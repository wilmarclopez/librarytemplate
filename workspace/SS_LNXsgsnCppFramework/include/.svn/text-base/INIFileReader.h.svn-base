/*
 * INIFileHeader.h
 *
 *  Created on: Mar 6, 2012
 *      Author: Oliver.Tizon
 */

#ifndef INIFILEHEADER_H_
#define INIFILEHEADER_H_

#include <string>
#include <map>
using namespace std;

class INIFileReader {

public:

	//bool flagforvalidateinisuccess;


	virtual ~INIFileReader();

	virtual void readConfigParameters(const char* inifile);

	//get String Param
	string getStringParam(string name);

	//get String Param
	void getStringParamAsCharPtr(string name, char *outParam);

	//get Interger Param
	unsigned int getIntParam(string name);

	//get bool param
	bool getBoolParam(string name);

	//get the symbol map
	inline map<string, string>& getSymbols() {
		return symbols;
	}

	static int retrycount;
	static string inilastline;

	static INIFileReader* iniFileReader;
	static INIFileReader* getIniFileReader();

	static bool syncINIFileWithOMU(const char * fromFileName,
			const char * toOmuFileName);

	static bool validate_And_Retry(const char * fromFileName,
			const char* cp2Buff);
	static bool isCorrupted(const char * fromFileName,
			const string& inilastline);

	static bool fileExists(const char * filename);

protected:

	INIFileReader();
	//INIFileReader(string inifile);
	//helper functions for parsing
	void add(string name, string value);
	void split(string in, string& left, string& right, char c);
	void trim(string& s);

	//ini group symbol map
	map<string, string> symbols;

};

#endif /* INIFILEHEADER_H_ */
