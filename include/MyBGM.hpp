#ifndef MYBGM_HPP
#define MYBGM_HPP

#include <string>
#include <atomic>
#include <thread>

#pragma comment(lib, "winmm.lib")
namespace MyBGM {
	/// <summary>
	/// Get Volume value (0 ~ F)
	/// </summary>
	/// <returns></returns>
	int GetVolume() noexcept;

	/// <summary>
	/// Set Volume value (0 ~ F)
	/// </summary>
	/// <param name="Volume"></param>
	void SetVolume(int Volume) noexcept;

	class BGM {
	public:
		enum class State {
			null,
			play,
			pause
		};

		BGM(const std::string& name) : name(name) {}

		BGM(const std::string& name, const std::string& filePath) : name(name), filePath(filePath), state(State::null) {}

		BGM(const BGM& other) = delete;

		BGM(BGM&& other) = delete;

		BGM() = delete;

		~BGM() {
			if (doloop->joinable()) {
				(doloop)->join();
			}
		}

		inline const int& GetLoop() const noexcept { return loop.load(); }

		inline const std::string& GetFilePath() const noexcept { return filePath; }

		inline const bool& isPause() const noexcept { return pause.load(); }

		inline const bool& isPlay() const noexcept { return start.load(); }

		inline void SetLoop(bool isloop) noexcept { loop.store(isloop); }

		inline void SetFilePath(const std::string& filePath) noexcept { this->filePath = filePath; }

		inline void SetFilePath(std::string&& filePath) noexcept { this->filePath = filePath; }


		void Play() noexcept;

		inline void Pause() noexcept {
			pause.store(true);
			start.store(false);
			// loop.store(false);
		}

		inline void Resum() noexcept {
			// pause.store(false);
			start.store(true);
		}

		void Stop() noexcept {
			exit.store(true);
			loop.store(false);
		}

		void RePlay() noexcept;


	private:
		void PlayLoop() noexcept;

		void PlayOnce() noexcept;

		std::string filePath = "", name = "";
		State state = State::null;
		std::atomic_bool loop{ true }, pause{ false }, exit{ false }, start{ false };
		int pausePosition{ 0 };
		std::shared_ptr<std::thread> doloop{ nullptr };
	};
}



#endif // !MYBGM_HPP
