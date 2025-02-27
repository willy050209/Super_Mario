#include "GameManager.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"

#include <memory>

constexpr auto BGMPath = MY_RESOURCE_DIR"\\BGM\\Ring08.wav";
constexpr auto ArialFontPath = MY_RESOURCE_DIR"\\Font\\arial.ttf";
constexpr auto BackgroundImagePath = MY_RESOURCE_DIR"\\Image\\Background\\cat.jpg";
constexpr auto marioImagePath = MY_RESOURCE_DIR"\\Image\\Character\\bee_1.png";

void GameManager::init() noexcept
{

	bgm = std::make_shared<Util::BGM>(BGMPath);
	bgm->SetVolume(64);// 0~128
	
	background = std::make_shared<ImageObject>(BackgroundImagePath,-10);

	mario = std::make_shared<Mario>(marioImagePath);
	mario->SetPosition({ 0,300 });

	text = std::make_shared<TextObject>(ArialFontPath, 20, "Text Output Example(Font = Arial)", Util::Color::FromName(Util::Colors::YELLOW), 10);
	text->SetPosition({ -400,300 });

	m_Root.AddChild(text);
	m_Root.AddChild(background);
	m_Root.AddChild(mario);
	bgm->Play();
}

void GameManager::Update() noexcept
{
	if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE)) {
		End();
	}
	mario->behavior();
	m_Root.Update();
}

void GameManager::End() noexcept
{
	endstate = true;
}
