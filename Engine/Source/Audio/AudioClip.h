#pragma once
#include "Resource/Resource.h"
#include "Audio.h"

class AudioSource;

class AudioClip : public Resource
{
public:
	AudioClip() = default;
	~AudioClip();

	bool Create(std::string name, ...) override;
	bool Load(const std::string& filename, class Audio& audio);

	friend Audio;
	friend AudioSource;

private:
	FMOD::Sound * m_sound{ nullptr };
};
