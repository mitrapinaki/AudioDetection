/*
 * Wav.cpp
 *
 *  Created on: 05-Jan-2018
 *      Author: pinaki
 */


#include "Wav.h"

Wav::Wav(const char *filename)
{
	fp = fopen(filename, "rb");
	assert(fp != NULL);
	fread(wav_info.riff_id, 1, 4, fp);
	wav_info.riff_id[4] = '\0';
	fread(&wav_info.size0, 4, 1, fp);
	fread(wav_info.wave_fmt, 1, 8, fp);
	wav_info.wave_fmt[8] = '\0';
	fread(&wav_info.size1, 4, 1, fp);
	fread(&wav_info.fmttag, 2, 1, fp);
	fread(&wav_info.channel, 2, 1, fp);
	fread(&wav_info.sample_per_sec, 4, 1, fp);
	fread(&wav_info.byte_per_sec, 4, 1, fp);
	fread(&wav_info.block_align, 2, 1, fp);
	fread(&wav_info.bit_per_sample, 2, 1, fp);
	if (wav_info.size1 == 0x10){
		fread(wav_info.data_id, 1, 4, fp);
		wav_info.data_id[4] = '\0';
		fread(&wav_info.size2, 4, 1, fp);
	}
	else{
		fseek(fp, 6, SEEK_CUR);
		uint32_t offset;
		fread(&offset, 4, 1, fp);
		fseek(fp, offset, SEEK_CUR);
		fread(wav_info.data_id, 1, 4, fp);
		wav_info.data_id[4] = '\0';
		fread(&wav_info.size2, 4, 1, fp);
	}
	data_offset = wav_info.size0 + 8 - wav_info.size2;
}

Wav::~Wav()
{
	fclose(fp);
}
int16_t Wav::GetSample()
{
	int16_t s1;
	fread(&s1, 2, 1, fp);
	return s1;
}
uint32_t Wav::GetDataSize()
{
	return wav_info.size2;
}
uint16_t Wav::GetBlockAlign()
{
	return wav_info.block_align;
}
uint32_t Wav::GetSampleRate()
{
	return wav_info.sample_per_sec;
}
