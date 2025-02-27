#include "GameManager.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"

#include <memory>

constexpr auto BGMPath = MY_RESOURCE_DIR"\\BGM\\Ring08.wav";
constexpr auto ArialFontPath = MY_RESOURCE_DIR"\\Font\\arial.ttf";
constexpr auto BackgroundImagePath = MY_RESOURCE_DIR"\\Image\\Background\\cat.jpg";
constexpr auto marioImagePath = MY_RESOURCE_DIR"\\Image\\Character\\bee_1.png";

inline static float GetX0(std::shared_ptr<Object> obj) noexcept {
	return -(WINDOW_WIDTH / 2 - obj->GetSize().x / 2);
}

inline static float GetY0(std::shared_ptr<Object> obj) noexcept {
	return (WINDOW_HEIGHT / 2 - obj->GetSize().y / 2);
}

void GameManager::init() noexcept
{

	bgm = std::make_shared<Util::BGM>(BGMPath);
	bgm->SetVolume(0);// 0~128
	
	background = std::make_shared<ImageObject>(BackgroundImagePath,-10);
	background->SetPosition({ GetX0(background),GetY0(background) - (WINDOW_HEIGHT - background->GetSize().y) });
	

	mario = std::make_shared<Mario>(marioImagePath,10);
	mario->SetPosition({ 0,300 });
	

	text = std::make_shared<TextObject>(ArialFontPath, 20, "Text Output Example(Font = Arial)", Util::Color::FromName(Util::Colors::YELLOW), 10);
	text->SetPosition({ -400,300 });
	text->SetPosition({ GetX0(text),GetY0(text) });
	m_Root.AddChild(text);
	m_Root.AddChild(background);
	m_Root.AddChild(mario);
	bgm->Play();
}

void GameManager::Update(std::shared_ptr<Core::Context>& context) noexcept
{
	if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE)) {
		End();
	}
	else if (Util::Input::IsKeyPressed(Util::Keycode::RALT) && Util::Input::IsKeyDown(Util::Keycode::RETURN)) {
		context->SetFullScreenState((context->GetFullScreenState() == SDL_bool::SDL_TRUE) ? SDL_bool::SDL_FALSE : SDL_bool::SDL_TRUE);
		SDL_SetWindowFullscreen(context->GetWindow(), context->GetFullScreenState());
	}
	else if (Util::Input::IsKeyDown(Util::Keycode::LSHIFT))
	{
		context->ReSize(1600, 900);
	}
	mario->behavior();
	m_Root.Update();
}

void GameManager::End() noexcept
{
	endstate = true;
}
