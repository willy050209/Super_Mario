#include "GameManager.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"

#include <memory>

constexpr auto imagepath = "C:\\Users\\Willy\\Pictures\\Saved Pictures\\GepqrWqbsAI1gpA.jpg";

void GameManager::init() noexcept
{
	background = std::make_shared<Util::GameObject>(Util::GameObject(std::make_unique<Util::Image>(imagepath), -10));
	m_Root.AddChild(background);
}

void GameManager::Update() noexcept
{
	m_Root.Update();
	if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE)) {
		End();
	}
}

void GameManager::End() noexcept
{
	endstate = true;
}
