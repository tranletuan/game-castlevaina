
#include "Audio.h"

CSoundManager *dsound;
bool CAudio::m_isSoundOff = false;

CAudio::CAudio(HWND hWnd)
{
	HRESULT result;
	bool isInit_Audio;

	//create DirectSound manager object
	dsound = new CSoundManager();

	//initialize DirectSound
	result = dsound->Initialize(hWnd, DSSCL_PRIORITY);
	if (result != DS_OK)
		isInit_Audio = false;

	//set the primary buffer format
	result = dsound->SetPrimaryBufferFormat(2, 22050, 16);
	if (result != DS_OK)
		isInit_Audio = false;

	//return success
	isInit_Audio = true;
}

CSound* CAudio::LoadSound(char* filename)
{
	HRESULT result;

	//create local reference to wave data
	CSound *wave;

	//attempt to load the wave file
	result = dsound->Create(&wave, filename);
	if (result != DS_OK)
		return NULL;

	//return the wave
	return wave;
}

void CAudio::playSound(CSound *sound)
{
	sound->Play();
}

void CAudio::loopSound(CSound *sound)
{
	sound->Play(0, DSBPLAY_LOOPING);
}

void CAudio::stopSound(CSound *sound)
{
	sound->Stop();
}