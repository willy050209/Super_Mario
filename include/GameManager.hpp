#ifndef GAMEMANGER_HPP
#define GAMEMANGER_HPP 

#include "MyContext.hpp"
#include "Util/Renderer.hpp"
#include "Util/BGM.hpp"
#include "ImageObject.hpp"
#include "TextObject.hpp"
#include "Mario.hpp"
#include "Button.hpp"

#include <memory>

class GameManager
{

public:
	GameManager() = default;
	~GameManager() = default;

	void init() noexcept;

	void Update(std::shared_ptr<Core::Context>&) noexcept;

	void End() noexcept;

	inline bool isEnd() const noexcept { return endstate; }

	inline void doEvent() noexcept {
		std::for_each(m_Events.begin(), m_Events.end(), [](const auto& it) {it->behavior(); });
	}

private:
	Util::Renderer m_Root;
	std::vector<std::shared_ptr<Object>> m_Events;
	std::shared_ptr<Util::BGM> bgm;
	std::shared_ptr<TextObject> text;
	std::shared_ptr<ImageObject> background;
	std::vector<std::shared_ptr<Button>> buttons;
	std::shared_ptr<Mario> mario;
	

	bool endstate = false;
};


#endif // !GAMEMANGER_HPP


