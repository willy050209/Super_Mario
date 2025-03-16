#ifndef GAMEMANGER_HPP
#define GAMEMANGER_HPP 

#include "MyContext.hpp"
#include "Util/BGM.hpp"
#include "Form/FormManger.hpp"
#include "MyBGM.hpp"

#include <memory>

constexpr auto BGMPath = MY_RESOURCE_DIR"/BGM/Ring08.wav";
constexpr auto MyFontPath = MY_RESOURCE_DIR"/Font/112590005.ttf";
constexpr auto ArialFontPath = MY_RESOURCE_DIR"/Font/arial.ttf";
constexpr auto BackgroundImagePath = MY_RESOURCE_DIR"/Image/Background/cat.jpg";
constexpr auto marioImagePath = MY_RESOURCE_DIR"/super mario/Mario/frame0.png";
constexpr auto Background_1_1_ImagePath = MY_RESOURCE_DIR"/super mario/Maps/SuperMarioBrosMap1-1BG.png";
constexpr auto BlockImagePath = MY_RESOURCE_DIR"/super mario/1-1/BrickBlockBrown.png";
constexpr auto QuestionBlockPath = MY_RESOURCE_DIR"/super mario/QuestionBlock/frame0.png";

constexpr auto FormBackground = "Background";
constexpr auto FormOptions = "Options";
constexpr auto FormSetting = "Setting";
constexpr auto FormTitel = "Titel";
constexpr auto Form_1_1 = "Form_1_1";

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

	inline std::shared_ptr<Util::BGM>& GetBGM() noexcept { return bgm; }
	
	inline void SetRestart(bool val) noexcept { m_Restart = val; }

private:

	FormManger MyFM;

	std::shared_ptr<Util::BGM> bgm;
	std::vector<std::shared_ptr<MyBGM>> bgms;
	bool endstate = false;
	bool m_Restart = false;
};


#endif // !GAMEMANGER_HPP


