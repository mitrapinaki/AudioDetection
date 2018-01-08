/*
 * Wav.h
 *  Read the format of wav file and fill the structure
 *
 *  Created on: 05-Jan-2018
 *      Author: pinaki
 */

#ifndef WAV_H_
#define WAV_H_
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

struct wav_struct{
	char		riff_id[5];
	uint32_t	size0;
	char		wave_fmt[9];
	uint32_t	size1;
	uint16_t	fmttag;
	uint16_t	channel;
	uint32_t	sample_per_sec;
	uint32_t	byte_per_sec;
	uint16_t	block_align;
	uint16_t	bit_per_sample;
	char		data_id[5];
	uint32_t	size2;
};

class Wav{
private:
	wav_struct wav_info;

public:
	FILE *fp;
	int data_offset;
	Wav(const char *filename);
	~Wav();
	uint32_t GetDataSize();
	uint16_t GetBlockAlign();
	uint32_t GetSampleRate();
	int16_t  GetSample();
};


#endif /* WAV_H_ */
