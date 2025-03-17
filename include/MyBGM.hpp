#ifndef MYBGM_HPP
#define MYBGM_HPP

#include <string>

#pragma comment(lib, "winmm.lib")

class MyBGM {
public:

	enum class State
	{
		null,play,pause
	};

	MyBGM(const std::wstring& name):name(name){}

	MyBGM(const std::wstring& name,const std::wstring& filePath):name(name), filePath(filePath),state(State::null) {}

	MyBGM(const MyBGM& other) = delete;

	MyBGM(MyBGM&& other) = delete;

	MyBGM() = delete;

	inline const int& GetLoop() const noexcept { return loop; }

	inline void SetLoop(bool isloop) noexcept { loop = isloop; }

	inline void SetFilePath(const std::wstring& filePath) noexcept { this->filePath = filePath; }
	inline void SetFilePath(std::wstring&& filePath) noexcept { this->filePath = filePath; }

	inline const std::wstring& GetFilePath() const noexcept { return filePath; }

	void Play() noexcept;

	void Pause() noexcept;

	void Stop() noexcept;

	void RePlay() noexcept;


private:
//#ifdef UNICODE
//#define M_UNICODE
//	std::string filePath = "", name = "";
//#else
//	std::string filePath = "", name = "";
//#endif // UNICODE

	std::wstring filePath = L"", name = L"";
	State state = State::null;
	bool loop = false;

	//void chageVolume() noexcept;
};


#endif // !MYBGM_HPP
