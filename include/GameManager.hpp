#ifndef GAMEMANGER_HPP
#define GAMEMANGER_HPP 

#include "MyContext.hpp"
#include "Util/BGM.hpp"
#include "Form/FormManger.hpp"

#include <memory>

constexpr auto BGMPath = MY_RESOURCE_DIR"/BGM/Ring08.wav";
constexpr auto ArialFontPath = MY_RESOURCE_DIR"/Font/arial.ttf";
constexpr auto BackgroundImagePath = MY_RESOURCE_DIR"/Image/Background/cat.jpg";
constexpr auto marioImagePath = MY_RESOURCE_DIR"/Image/Character/bee_1.png";

constexpr auto FormBackground = "Background";
constexpr auto FormOptions = "Options";
constexpr auto FormSetting = "Setting";

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

	inline std::shared_ptr<Util::BGM>& GetBGM() noexcept { return bgm; }

private:

	FormManger MyFM;

	std::shared_ptr<Util::BGM> bgm;
	bool endstate = false;

};


#endif // !GAMEMANGER_HPP


