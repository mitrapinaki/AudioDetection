/*
 * Fingerprint.cpp
 *
 *  Created on: 05-Jan-2018
 *      Author: pinaki
 */

#include "Fingerprint.h"
using namespace std;

int Fingerprint::fingerprint_amplitude =0;

Fingerprint::Fingerprint(){
	fftw_in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)* FRAME_SIZE);
	fftw_out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)* FRAME_SIZE);
	fftw_p = fftw_plan_dft_1d(FRAME_SIZE, fftw_in, fftw_out, FFTW_FORWARD, FFTW_ESTIMATE);

	hamming = (float*)malloc((FRAME_SIZE) * sizeof(float));
	assert(hamming != NULL);
	for (int i = 0; i<FRAME_SIZE; i++)
		hamming[i] = (float)(0.54 - 0.46*cos(2 * PI*i / (FRAME_SIZE - 1)));
}

void Fingerprint::CreateFingerPrint(const char *filename,int mode=0)
{
	Wav wav(filename);
	if (wav.GetSampleRate() != SAMPLE_RATE )
	{
		cout <<"The sample rate of this file is "<< wav.GetSampleRate() << endl;
		cout << "Files with sample rate " << SAMPLE_RATE << " are only processed. Skipping this file" << endl;
		return;
	}
	frame_num = (wav.GetDataSize()/wav.GetBlockAlign()-FRAME_SIZE)/FRAME_HOP+2;
	fseek(wav.fp, wav.GetBlockAlign(), SEEK_CUR);
	std::vector<int>  spectrum;
	spectrum.resize(frame_num * FRAME_HEIGHT);
	float max = 0;
	for (int i=0; i<frame_num; i++)
	{
		for (int j=0; j<FRAME_SIZE; j++)
		{
			fftw_in[j][0] = wav.GetSample() * hamming[j];  //hamming Window
			fftw_in[j][1] = 0;
		}

		fseek(wav.fp, (FRAME_HOP-FRAME_SIZE)*wav.GetBlockAlign(), SEEK_CUR);
		fftw_execute(fftw_p);
		for (int j=0; j<FRAME_HEIGHT; j++)
		{
				if (j<LOW_FREQ)
					spectrum[i] = 0;
				else
				{
					spectrum[i] = (float)sqrt(fftw_out[j][0]*fftw_out[j][0]+fftw_out[j][1]*fftw_out[j][1])/FRAME_SIZE;
					if(spectrum[i] > max)
						max = spectrum[i];
				}
		 }
	}
	if( mode == CREATE_FPRINT)
	{
		Fingerprint::fingerprint_amplitude = max;
	}
    else
	{
    	test_amplitude = max;
	}

}

bool Fingerprint::DetectFileMatching(const char* filePath)
{
	CreateFingerPrint(filePath,DETECT_FPRINT);
	cout << "Fingerprint Amplitude is " << Fingerprint::fingerprint_amplitude << endl;
	cout << "Test Amplitude is " << test_amplitude << endl;
	cout << "Deviation is " << abs(test_amplitude -Fingerprint::fingerprint_amplitude) << endl;
	cout << "Accepted Deviation is " << ACCEPTED_DEVIATION << endl;

	if((abs(test_amplitude - Fingerprint::fingerprint_amplitude)) < ACCEPTED_DEVIATION )
		return true;
	else
		return false;
}

Fingerprint::~Fingerprint()
{
	fftw_destroy_plan(fftw_p);
	fftw_free(fftw_in);
	fftw_free(fftw_out);
	assert(hamming!= NULL);
	free(hamming);
	hamming = NULL;
}


