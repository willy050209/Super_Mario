#ifndef GAMEMANGER_HPP
#define GAMEMANGER_HPP 

#include "MyContext.hpp"
#include "Util/BGM.hpp"
#include "Form/FormManger.hpp"
#include "MyBGM.hpp"
#include "FilePath.hpp"

#include <memory>

constexpr auto FormBackground = "Background";
constexpr auto FormOptions = "Options";
constexpr auto FormSetting = "Setting";
constexpr auto FormTitel = "Titel";
constexpr auto Form_1_1 = "Form_1_1";
constexpr auto Form_1_1_Pipe = "Form_1_1_Pipe";
constexpr auto Form_1_2 = "Form_1_2";

class GameManager
{

public:
	GameManager() = default;
	~GameManager() = default;

	void init() noexcept;

	void Update(std::shared_ptr<Core::Context>&) noexcept;

	void End() noexcept;

	inline bool isEnd() const noexcept { return endstate; }

	inline FormManger& GetFormManger() noexcept { return MyFM; }

	inline bool GetRestart() const noexcept { return m_Restart; }

	inline const glm::vec2& GetCheckPointPos() const noexcept {
		return checkPointPos;
	}

	inline const int& GetHP() const noexcept { return HP; }

	inline const int& GetPoint() const noexcept { return point; }

	inline void addPoint(const int& val) noexcept { point += val; }
	inline void addPoint(int&& val) noexcept { point += val; }

	inline void IncHP() noexcept { ++HP; }

	inline void DecHP() noexcept { --HP; }

	//inline std::shared_ptr<Util::BGM>& GetBGM() noexcept { return bgm; }
	
	inline void SetRestart(bool val) noexcept { m_Restart = val; }

	inline void SaveCheckPointPos(const glm::vec2& pos) noexcept {
		checkPointPos = pos;
	}

	bool pause{ false };
	std::shared_ptr<Util::BGM> bgm;

private:

	FormManger MyFM;

	int HP = 3;
	int point = 0;
	//std::vector<std::shared_ptr<MyBGM::BGM>> bgms;
	bool endstate = false;
	bool m_Restart = false;
	glm::vec2 checkPointPos;
};


#endif // !GAMEMANGER_HPP


