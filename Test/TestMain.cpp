/*

 * TestMain.cpp
 *
 *  Created on: 07-Jan-2018
 *      Author: pinaki
 */

#include "../include/Fingerprint.h"
using namespace std;

void Test_Initialize()
{
	Fingerprint SampleSound;
	SampleSound.CreateFingerPrint("files/Original/Samplestream.wav",CREATE_FPRINT);
}

void Test_TestMySoundfile(const char* filePath)
{
	Fingerprint TestSound;
	if(TestSound.DetectFileMatching(filePath))
		cout << "The File:" << filePath << " is matching with Samplestream.wav" << endl;
	else
		cout << "The File:" << filePath << " is not matching with Samplestream.wav" << endl;
}


int main()
{

	cout << "------------ UNIT TEST SUITE ----------------------" << endl;
	Test_Initialize();

	cout << "------------ POSITIVE CASES ----------------------" << endl;
	cout << "**** Following 4 files should MATCH with Samplestream.wav with deviation < " << ACCEPTED_DEVIATION << " ****" <<endl;

	Test_TestMySoundfile("files/human_voice/2023873236_02262015_065751.wav");
	Test_TestMySoundfile("files/human_voice/9732420871_02192015_080209.wav");
	Test_TestMySoundfile("files/human_voice/9732420871_02192015_080299.wav");
	Test_TestMySoundfile("files/human_voice/9732420871_02192015_990204.wav");

	cout << "------------ NEGATIVE CASES ----------------------" << endl;
	cout << "**** Following 4 files shoTuld NOT MATCH with Samplestream.wav with deviation > " << ACCEPTED_DEVIATION << " ****" <<endl;

	Test_TestMySoundfile("files/human_voice_not_matching/2154414628_02252015_101419.wav");
	Test_TestMySoundfile("files/human_voice_not_matching/3017354341_02192015_061559.wav");
	Test_TestMySoundfile("files/machine_voice/7176308827_02212015_082411.wav");
	Test_TestMySoundfile("files/machine_voice/7577283680_02242015_091209.wav");

	cout << "------------ NEGATIVE CASES + IMPROPER FILE ----------------------" << endl;
	cout << "**** Following file with sample rate other than 8000 should not be processed " << endl;
	Test_TestMySoundfile("files/Original/Samplestream_44100.wav");

	return 0;
}



