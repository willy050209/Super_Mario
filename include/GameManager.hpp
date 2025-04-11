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
constexpr auto Form_1_1_to_1_2 = "Form_1_1_to_1_2";
constexpr auto Form_1_2 = "Form_1_2";
constexpr auto Form_1_2_Pipe = "Form_1_2_Pipe";

class GameManager
{

public:
	GameManager() = default;
	~GameManager() = default;

	/// <summary>
	/// 執行初始化
	/// </summary>
	void init() noexcept;

	/// <summary>
	/// 表單刷新
	/// </summary>
	/// <param name=""></param>
	void Update(std::shared_ptr<Core::Context>&) noexcept;

	/// <summary>
	/// 結束遊戲
	/// </summary>
	void End() noexcept;

	/// <summary>
	/// 取得遊戲是否結束
	/// </summary>
	/// <returns></returns>
	inline bool isEnd() const noexcept { return endstate; }

	/// <summary>
	/// 取得FormManger
	/// </summary>
	/// <returns>所有表單</returns>
	inline FormManger& GetFormManger() noexcept { return MyFM; }

	/// <summary>
	/// 使否需要重啟
	/// </summary>
	/// <returns></returns>
	inline bool GetRestart() const noexcept { return m_Restart; }

	/// <summary>
	/// 取得存檔點座標
	/// </summary>
	/// <returns>CheckPoint Position</returns>
	inline const glm::vec2& GetCheckPointPos() const noexcept {
		return checkPointPos;
	}

	/// <summary>
	/// 取得玩家血量
	/// </summary>
	/// <returns>HP</returns>
	inline const int& GetHP() const noexcept { return HP; }

	/// <summary>
	/// 取得玩家分數
	/// </summary>
	/// <returns>Point</returns>
	inline const int& GetPoint() const noexcept { return point; }

	/// <summary>
	/// 增加分數
	/// </summary>
	/// <param name="val">lvalue ref</param>
	inline void addPoint(const int& val) noexcept { point += val; }
	/// <summary>
	/// 增加分數
	/// </summary>
	/// <param name="val">rvalue ref</param>
	inline void addPoint(int&& val) noexcept { point += val; }

	/// <summary>
	/// 血量遞增
	/// </summary>
	inline void IncHP() noexcept { ++HP; }

	/// <summary>
	/// 血量遞減
	/// </summary>
	inline void DecHP() noexcept { --HP; }

	//inline std::shared_ptr<Util::BGM>& GetBGM() noexcept { return bgm; }
	
	/// <summary>
	/// 設定是否要重啟
	/// </summary>
	/// <param name="val"></param>
	inline void SetRestart(bool val) noexcept { m_Restart = val; }

	/// <summary>
	/// 儲存位置
	/// </summary>
	/// <param name="pos">Position</param>
	inline void SaveCheckPointPos(const glm::vec2& pos) noexcept {
		checkPointPos = pos;
	}

	/// <summary>
	/// 是否於暫停狀態
	/// </summary>
	bool pause{ false };

	/// <summary>
	/// 是否啟用無敵模式
	/// </summary>
	bool opMode = false;

	/// <summary>
	/// 遊戲BGM
	/// </summary>
	std::shared_ptr<Util::BGM> bgm;

private:

	/// <summary>
	/// 管理所有表單
	/// </summary>
	FormManger MyFM;

	/// <summary>
	/// 玩家HP
	/// </summary>
	int HP = 3;

	/// <summary>
	/// 玩家分數
	/// </summary>
	int point = 0;
	//std::vector<std::shared_ptr<MyBGM::BGM>> bgms;

	/// <summary>
	/// 結束狀態
	/// </summary>
	bool endstate = false;

	/// <summary>
	/// 重啟狀態
	/// </summary>
	bool m_Restart = false;

	/// <summary>
	/// 上一個存檔點座標
	/// </summary>
	glm::vec2 checkPointPos;
};


#endif // !GAMEMANGER_HPP


