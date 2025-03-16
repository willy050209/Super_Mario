#include "MyBGM.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <SDL_mixer.h>


void MyBGM::Play() noexcept {
	std::wstring command;
	switch (state)
	{
	case MyBGM::State::null:
		command = L"open \"" + filePath + L"\" alias " + name;
		mciSendStringW(command.c_str(), NULL, 0, NULL);
		command = L"Play " + name;
		break;
	case MyBGM::State::play:
		break;
	case MyBGM::State::pause:
		command = L"resume " + name;
		break;
	default:
		return;
		break;
	}
	state = State::play;
	mciSendStringW(command.c_str(), NULL, 0, NULL);
	//chageVolume();
}

void MyBGM::Pause() noexcept
{
	std::wstring command;

	switch (state)
	{
	case MyBGM::State::null:
		return;
	case MyBGM::State::play:
		command = L"pause " + name;
		break;
	case MyBGM::State::pause:
	default:
		return;
	}
	state = State::pause;
	mciSendStringW(command.c_str(), NULL, 0, NULL);
}

void MyBGM::Stop() noexcept
{
	std::wstring command;
	command = L"stop " + name;
	mciSendStringW(command.c_str(), NULL, 0, NULL);
	command = L"close " + name;
	mciSendStringW(command.c_str(), NULL, 0, NULL);
}

void MyBGM::RePlay() noexcept
{

}

//void MyBGM::chageVolume() noexcept {
//	std::wstring command = L"setaudio " + name + L" volume to " + std::to_wstring(1000);
//	mciSendStringW(command.c_str(), NULL, 0, NULL);
//	auto sss = (((unsigned int)Volume & 0x0000ffff) | ((unsigned int)Volume << 16));
//	//waveOutSetVolume(0, (((unsigned int)Volume & 0x0000ffff) | ((unsigned int)Volume << 16)));
//	//waveOutSetVolume(name.c_str(),)
//	waveOutSetVolume(0, 1717986918);
//}