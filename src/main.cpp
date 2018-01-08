/*
 * main.cpp
 *
 *  Created on: 05-Jan-2018
 *      Author: pinaki
 */
#include <iostream>
#include <string.h>
#include "Fingerprint.h"
using namespace std;

void Initialize()
{
	Fingerprint SampleSound;
	SampleSound.CreateFingerPrint("Samplestream.wav",CREATE_FPRINT);
}

void TestMySoundfile(const char* filePath)
{
	Fingerprint TestSound;
	if(TestSound.DetectFileMatching(filePath))
		cout << "The File:" << filePath << " is matching with Samplestream.wav" << endl;
	else
		cout << "The File:" << filePath << " is not matching with Samplestream.wav" << endl;
}

int main(int argc, char* argv[])
{
	Initialize();
	string filePath;
	char answer;
	do
	{
	  cout << "Enter the filepath to compare with Samplestream.wav " << endl;
	  cin >> filePath;
	  cin.get();
	  cout << "Input wave file name to test: " << filePath << endl;
	  TestMySoundfile(filePath.c_str());
	  cout << "Do you want to continue ( 'y' or 'n'? )";
	  cin >> answer;
	}while(answer == 'y' || answer == 'Y');

	return 0;

}

