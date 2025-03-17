#include "MyBGM.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <memory>
#include <iostream>

using namespace MyBGM;



void BGM::Play() noexcept {
	if (loop.load()) {
		PlayLoop();
	}
	else {
		PlayOnce();
	}
}

void BGM::PlayLoop() noexcept {
	if (doloop != nullptr && doloop->joinable())
	{
		Stop();
		doloop->join();
	}
	doloop = std::make_shared< std::thread>([&]() {
		this->exit.store(false);
		do
		{
			if (loop.load())
			{
				//puts("play audio");
				char command[256], retstr[64];
				sprintf(command, "open \"%s\" alias \"%s\"", filePath.c_str(), name.c_str());
				mciSendStringA(command, NULL, 0, NULL);
				if (pause.load()) {
					//puts("load audio");
					//std::cout << sprintf(command, "play \"%s\" from %d", name.c_str(), pausePosition) << pausePosition;
					sprintf(command, "play \"%s\" from %d", name.c_str(), pausePosition);
					mciSendStringA(command, NULL, 0, NULL);
					pause.store(false);
				}
				else
				{
					sprintf(command, "play \"%s\"", name.c_str());
					mciSendStringA(command, NULL, 0, NULL);
				}
				sprintf(command, "status \"%s\" length", name.c_str());
				mciSendStringA(command, retstr, sizeof(retstr), NULL);
				int len = atoi(retstr);
				do
				{
					sprintf(command, "status \"%s\" position", name.c_str());
					mciSendStringA(command, retstr, sizeof(retstr), NULL);
					pausePosition = (atoi(retstr));

				} while (!pause.load() && loop.load() && len > pausePosition);
				sprintf(command, "stop \"%s\"", name.c_str());
				mciSendStringA(command, retstr, sizeof(retstr), NULL);
				sprintf(command, "close \"%s\"", name.c_str());
				mciSendStringA(command, retstr, sizeof(retstr), NULL);
			}
		} while (!this->exit.load());
		//puts("exit loop");
		});

}

void BGM::PlayOnce() noexcept {
	if (doloop != nullptr && doloop->joinable())
	{
		Stop();
		doloop->join();
	}
	doloop = std::make_shared< std::thread>([&]() {
		this->exit.store(false);
		char command[256], retstr[64];
		sprintf(command, "open \"%s\" alias \"%s\"", filePath.c_str(), name.c_str());
		mciSendStringA(command, NULL, 0, NULL);

		sprintf(command, "play \"%s\"", name.c_str());
		mciSendStringA(command, NULL, 0, NULL);

		sprintf(command, "status \"%s\" length", name.c_str());
		mciSendStringA(command, retstr, sizeof(retstr), NULL);

		int len = atoi(retstr);

		do {
			sprintf(command, "status \"%s\" position", name.c_str());
			mciSendStringA(command, retstr, sizeof(retstr), NULL);

			pausePosition = (atoi(retstr));
		} while (!this->exit && len > pausePosition);
		sprintf(command, "stop \"%s\"", name.c_str());
		mciSendStringA(command, retstr, sizeof(retstr), NULL);

		sprintf(command, "close \"%s\"", name.c_str());
		mciSendStringA(command, retstr, sizeof(retstr), NULL);
		});
}

void BGM::RePlay() noexcept
{
	Stop();
	Play();
}

int MyBGM::GetVolume() noexcept {
	auto intptr = std::make_shared<DWORD>();
	waveOutGetVolume(NULL, intptr.get());
	return (*intptr & 0xf);
}

void MyBGM::SetVolume(int Volume) noexcept {
	unsigned long tmp = 0;
	for (int i = 0; i < 8; i++) {
		tmp <<= 4;
		tmp |= Volume;

	}
	waveOutSetVolume(NULL, tmp);
}

