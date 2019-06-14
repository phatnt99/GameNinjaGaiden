
#include "Sound.h"

Sound* Sound::__Instance = NULL;

Sound::Sound()
{
	Init();
	LoadResourceSound();
}



void Sound::LoadResourceSound()
{
	//for Ninja
	AddSound(eSound::jump, "Resources/sound/jump.wav");
	AddSound(eSound::katana, "Resources/sound/katana.wav");
	AddSound(eSound::touchEnemy, "Resources/sound/touchEnemy.wav");
	AddSound(eSound::touchboss, "Resources/sound/touchboss.wav");
	AddSound(eSound::soundCollectItem, "Resources/sound/collectitem.wav");
	AddSound(eSound::loselife, "Resources/music/loselife.wav");
	//for weapon
	AddSound(eSound::millstar, "Resources/sound/millstar.wav");
	AddSound(eSound::throwingstar, "Resources/sound/throwingstar.wav");
	AddSound(eSound::firewheel, "Resources/sound/firewheel.wav");
	AddSound(eSound::timefreez, "Resources/sound/timefreez.wav");
	//for enemy
	AddSound(eSound::bum, "Resources/sound/bum.wav");
	AddSound(eSound::bumboss, "Resources/sound/bumboss.wav");
	AddSound(eSound::threeshot, "Resources/sound/threeshot.wav");
	AddSound(eSound::oneshot, "Resources/sound/oneshot.wav");
	AddSound(eSound::bosstouchbrick, "Resources/sound/bosstouchbrick.wav");

	//for Map
	AddSound(eSound::musicState1, "Resources/music/stage3_1.wav");
	AddSound(eSound::musicState2, "Resources/music/stage3_2.wav");
	AddSound(eSound::musicState3, "Resources/music/stage3_3.wav");

	AddSound(eSound::warningtime, "Resources/sound/warningtime.wav");
	AddSound(eSound::remainingtime, "Resources/sound/remainingtime.wav");

}

bool Sound::isPlaying(eSound type)
{
	return _ArrSound[type]->IsSoundPlaying();
}

void Sound::StopAll()
{
	for (auto& x : _ArrSound)
	{
		if (x.second->IsSoundPlaying())
			x.second->Stop();
	}
}


void Sound::AddSound(eSound type, LPTSTR filename)
{
	CSound *wave;
	HRESULT result = dsound->Create(&wave, filename);
	if (result != DS_OK)
	{
		return;
	}
	_ArrSound[type] = wave;
}

void Sound::Play(eSound type, bool isLoop, LONG lVolume)
{
	_ArrSound[type]->Play(0, isLoop, lVolume);
	//DSBPLAY_LOOPING             0x00000001 -> int = 1

}

void Sound::Stop(eSound type)
{
	_ArrSound[type]->Stop();
}



void Sound::Init()
{
	dsound = new CSoundManager();
	dsound->Initialize(Game::GetInstance()->GetWindowHandle(), DSSCL_PRIORITY);
	dsound->SetPrimaryBufferFormat(2, 22050, 16);
}

Sound * Sound::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new Sound();
	return __Instance;
}