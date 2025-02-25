#include "GameManager.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"

#include <memory>

constexpr auto BGMPath = MY_RESOURCE_DIR"\\BGM\\bgmtest.wav";
constexpr auto BackgroundImagePath = MY_RESOURCE_DIR"\\Image\\Background\\cat.jpg";
constexpr auto marioImagePath = MY_RESOURCE_DIR"\\Image\\Character\\bee_1.png";

void GameManager::init() noexcept
{

	bgm = std::make_shared<Util::BGM>(BGMPath);
	bgm->SetVolume(64);// 0~128
	background = std::make_shared<Util::GameObject>(Util::GameObject(std::make_unique<Util::Image>(BackgroundImagePath), 0));
	mario = std::make_shared<Mario>(marioImagePath);

	m_Root.AddChild(background);
	m_Root.AddChild(mario);
	bgm->Play();
}

void GameManager::Update() noexcept
{
	if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE)) {
		End();
	}
	mario->move(1.0);
	m_Root.Update();
}

void GameManager::End() noexcept
{
	endstate = true;
}
