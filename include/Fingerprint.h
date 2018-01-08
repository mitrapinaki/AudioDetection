/*
 * Fingerprint.h
 *
 *  Created on: 05-Jan-2018
 *      Author: pinaki
 */

#ifndef FINGERPRINT_H_
#define FINGERPRINT_H_

#include <iostream>
#include <math.h>
#include <fftw3.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include "Wav.h"

#define FRAME_SIZE 512
#define FRAME_HEIGHT FRAME_SIZE/2
#define FRAME_HOP 256
#define LOW_FREQ 20
#define PI 3.1415926
#define DETECT_FPRINT 0
#define CREATE_FPRINT 1
#define ACCEPTED_DEVIATION 50
#define SAMPLE_RATE 8000

class Fingerprint{
private:
	fftw_complex *fftw_in, *fftw_out;
	fftw_plan fftw_p;
	float *hamming;
	int frame_num =0;
	static int fingerprint_amplitude;
	int test_amplitude=0;

public:
	Fingerprint();
	~Fingerprint();

	/*Convert the time domain data to frequency domain and find the
	 * maximum amplitude. The maximum amplitude of desired flile is chosen
	 * as the fingerprint(fingerprintamplitude) value and the other files
	 * are measured with this value.
	 * PARAM:
	 * filename: The wav file to process
	 * MODE : CREATE_FPRINT(test file)   DETECT_FPRINT(sample file)
	 */
	void CreateFingerPrint(const char *filename,int mode);

	/* PARAM: The input file(test file) is compared against the sample file
	 * OUTPUT
	 * TRUE: The input files is matched with the sample file
	 * FALSE:The input files does not matched with the sample file
	 */
	bool DetectFileMatching(const char *filename);

};

#endif /* FINGERPRINT_H_ */
