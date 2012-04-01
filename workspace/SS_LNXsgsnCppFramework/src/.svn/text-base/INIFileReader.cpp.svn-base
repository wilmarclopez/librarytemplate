/*
 * INIFileReader.cpp
 *
 *  Created on: Mar 6, 2012
 *      Author: Oliver.Tizon
 */

#include "INIFileReader.h"
/* #include "LBSException.hpp" */
#include <iostream>
#define MAX_RETRY_COUNT 6
using namespace std;
#include <stdio.h>
#include <cstdlib>
#include <sys/stat.h>
#include <string.h>
#include <fstream>
#include <iostream>

INIFileReader* INIFileReader::iniFileReader = NULL;
INIFileReader* INIFileReader::getIniFileReader() {
	if (iniFileReader == NULL)
		iniFileReader = new INIFileReader();
	return iniFileReader;
}
void INIFileReader::readConfigParameters(const char* iniFile) {
	FILE* in = fopen(iniFile, "r");
	if (!in) {
		// flag error
	}

	char buff[1024];
	while (fgets(buff, 1024, in)) {

		string line = buff;
		if ((line.length() > 2) && (line[0] != '#')) {
			string name;
			string value;
			split(line, name, value, '=');

			this->add(name, value);
		}
	}

	fclose(in);

}

INIFileReader::INIFileReader() {
}

INIFileReader::~INIFileReader() {
	iniFileReader = NULL;
}

void INIFileReader::add(string name, string value) {
	symbols[name] = value;
}

void INIFileReader::split(string in, string& left, string& right, char c) {
	size_t pos = in.find_first_of(c);
	if (pos == string::npos) {
		left = in;
		trim(left);
		right = "";
	} else if (pos <= 1) {
		left = "";
		right = in.substr(pos + 1, string::npos);
		trim(right);
	} else {
		left = in.substr(0, pos);
		trim(left);
		right = in.substr(pos + 1, string::npos);
		trim(right);
	}
}

void INIFileReader::trim(string& s) {
	while ((s.length() > 1) && ((s[0] == ' ') || (s[0] == '\t'))) {
		s = s.substr(1, string::npos);
	}
	while ((s.length() > 1) && ((s[s.length() - 1] == ' ')
			|| (s[s.length() - 1] == '\t') || (s[s.length() - 1] == '\n')
			|| (s[s.length() - 1] == '\r'))) {
		s = s.substr(0, s.length() - 1);
	}
	if ((s.length() > 1) && (s[0] == '"')) {
		s = s.substr(1, string::npos);
	}
	if ((s.length() > 1) && (s[s.length() - 1] == '"')) {
		s = s.substr(0, s.length() - 1);
	}
}

string INIFileReader::getStringParam(string name) {
	map<string, string>::iterator i = symbols.find(name);
	if (i == symbols.end()) {
		//string nullString = "";
		//(Logger::m_GetLogInstance())->logError("Param not found for key:%s",name.c_str());
		return "";
		//exit(4);
	}
	return i->second;
}

void INIFileReader::getStringParamAsCharPtr(string name, char *outParam) {
	string val = getStringParam(name);
	strcpy(outParam, val.c_str());
}

bool INIFileReader::getBoolParam(string name) {
	string val = getStringParam(name);

	if ((val == "yes") || (val == "Yes") || (val == "YES") || (val == "true")
			|| (val == "True") || (val == "TRUE") || (atoi(val.c_str()) == 1)) {
		return true;
	}

	return false;
}

unsigned int INIFileReader::getIntParam(string name) {
	string val = getStringParam(name);

	return atol(val.c_str());
}

/*
 * This API syncs up the ini file FROM/TO ATCAs OMU disk active package directory.
 *
 **/
bool INIFileReader::syncINIFileWithOMU(const char * fromFileName,
	const char * toOmuFileName) {
	char verifyBuff[256];
	memset(verifyBuff, 0, 256);
	char cp1Buff[256];
	memset(cp1Buff, 0, 256);
	char cp2Buff[256];
	memset(cp2Buff, 0, 256);
	const char * cpCmd = "lnx-dxfile-cp";
	int result = -1;
	FILE *copy_ini_file_subprocess_fp = NULL;
	char buffer[256];
	memset(buffer, 0, 256);

	//attempt to copy the ini files to the OMU disk package directory
	//if the ini file is already present in the OMU , then lnx-dxfile-cp will throw an error
	//before executing the IPDU to OMU copy command , we need to redirect the
	//stderr to stdout
	if (fromFileName != NULL && toOmuFileName != NULL) {
		sprintf(cp1Buff, "%s %s omu:ASWDIR/%s 2>&1", cpCmd, fromFileName,
				toOmuFileName);
		sprintf(verifyBuff,
				"%s: remote file \'omu:ASWDIR/%s\' already exists\n", cpCmd,
				toOmuFileName);
		sprintf(cp2Buff, "%s -f omu:ASWDIR/%s %s 2>&1", cpCmd, toOmuFileName,
				fromFileName);
	} else {
		cout << "Invalid file name for copying to/from omu" << endl;
		return false;
	}

	if ((copy_ini_file_subprocess_fp = popen(cp1Buff, "r")) == NULL) {
		cout << "Failed to run command " << cp1Buff << endl;
	} else { //popen got executed successfully . Read whether it has produced any error . If the
		//error is "lnx-dxfile-cp: remote file 'OMU:<Module Name>.ini' already exists"
		while (fgets(buffer, sizeof(buffer), copy_ini_file_subprocess_fp)) {
			if (strcmp(buffer, verifyBuff) == 0) {
				//This is a valid error since OMU package directory is already having <Module Name>.ini file.
				cout << "File " << toOmuFileName
						<< " already exists in omu package disk." << endl;
				result = 0;
			}
		}
	}

	//Close the file descriptor opend by popen
	if (pclose(copy_ini_file_subprocess_fp) < 0) {
		cout << "WARNING:Couldn't close the file descriptor opend by pipe\n"
				<< endl;
	}

	//Now copy the ini file back from OMU package directory to IPDU
	if ((result == 0) && (system(cp2Buff) < 0)) {
		cout << "Failed to do forced copy file from omu:" << toOmuFileName
				<< " to " << fromFileName << endl;
	}

	return validate_And_Retry(fromFileName, cp2Buff);
}

bool INIFileReader::fileExists(const char * filename) {
	fstream fin;

	fin.open(filename, ios::in);

	if (fin.is_open()) {
		fin.close();
		return true;
	}

	fin.close();
	return false;
}

bool INIFileReader::isCorrupted(const char * fromFileName,
		const string& inilastline) {
	std::ifstream ifs(fromFileName);

	std::string line;

	while (std::getline(ifs, line)) {
		if (inilastline.compare(line) == 0) {
			printf("file is not corrupted...\n");
			return false;
		}
	}
	printf("file is corrupted..hence retry will be done...\n");
	return true;
}

bool INIFileReader::validate_And_Retry(const char * fromFileName,
		const char* cp2Buff) {
	int retrycount = 0;
	string
			inilastline =
					"#####THIS SHOULD BE THE LAST LINE. ADD FIELDS ABOVE THIS LINE. DONOT DELETE THIS LINE#####";
	bool flagforvalidateinisuccess = false;

	char dos2unix[256];
	memset(dos2unix, 0, 256);
	sprintf(dos2unix, "dos2unix %s 2>&1", fromFileName);

	while (!flagforvalidateinisuccess && (retrycount < MAX_RETRY_COUNT)) {

		system(dos2unix);

		if ((fileExists(fromFileName)) && (isCorrupted(fromFileName,
				inilastline))) {
			printf(
					"file exists and its corrupted..so retrying will be done to max 5 Times...\n");
			system(cp2Buff);
			printf("RETRY COUNT IS: %d \n", retrycount);
			retrycount++;
			//	if(!isCorrupted(fromFileName,inilastline))
			//	flagforvalidateinisuccess = true;
		} else if (!fileExists(fromFileName)) {
			printf("%s File doest not exist\n", fromFileName);
			//	return;
			system(cp2Buff);
			flagforvalidateinisuccess = true;
		} else
			flagforvalidateinisuccess = true;

	}

	if (retrycount == MAX_RETRY_COUNT) {
		printf("%s is corrupted even after retries.\n", fromFileName);
		return false;
	} else
		printf("file exists and its not corrupted..so no retries \n");

	return true;
}

