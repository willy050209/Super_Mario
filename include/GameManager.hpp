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

	//inline std::shared_ptr<Util::BGM>& GetBGM() noexcept { return bgm; }
	
	inline void SetRestart(bool val) noexcept { m_Restart = val; }

	bool pause{ false };

private:

	FormManger MyFM;

	//std::shared_ptr<Util::BGM> bgm;
	std::vector<std::shared_ptr<MyBGM::BGM>> bgms;
	bool endstate = false;
	bool m_Restart = false;
};


#endif // !GAMEMANGER_HPP


