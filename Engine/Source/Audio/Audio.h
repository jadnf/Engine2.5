#pragma once
#include <fmod.hpp>
#include <map>
#include <string>

class AudioClip;
class AudioSource;

class Audio {
public:
	Audio() = default;
	~Audio() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	bool AddSound(const std::string& name);
	bool PlaySound(const std::string& name);


	FMOD::System* m_audio{ nullptr };

	friend AudioClip;
	friend AudioSource;
protected:


private:
	std::map<std::string, FMOD::Sound*> m_sounds;
};