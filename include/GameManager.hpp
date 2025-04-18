#pragma once
#ifndef GAMEMANGER_HPP
#define GAMEMANGER_HPP

#include "MyContext.hpp"
#include "Util/BGM.hpp"
#include "Form/FormManger.hpp"
#include "MyBGM.hpp"
#include "FilePath.hpp"
#include "Util/SFX.hpp"

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

/// <summary>
/// �޲z�C���}�l�B����B�Ȱ��B����
/// </summary>
class GameManager {

public:
	GameManager() = default;
	~GameManager() = default;

	/// <summary>
	/// �����l��
	/// </summary>
	void init() noexcept;

	/// <summary>
	/// ����s
	/// </summary>
	/// <param name=""></param>
	void Update(std::shared_ptr<Core::Context>&) noexcept;

	/// <summary>
	/// �����C��
	/// </summary>
	void End() noexcept;

	/// <summary>
	/// ���o�C���O�_����
	/// </summary>
	/// <returns></returns>
	inline auto isEnd() const noexcept { return endstate; }

	/// <summary>
	/// ���oFormManger
	/// </summary>
	/// <returns></returns>
	inline auto& GetFormManger() noexcept { return MyFM; }

	/// <summary>
	/// �ϧ_�ݭn����
	/// </summary>
	/// <returns></returns>
	inline auto GetRestart() const noexcept { return m_Restart; }

	/// <summary>
	/// ���o�s���I�y��
	/// </summary>
	/// <returns>CheckPoint Position</returns>
	inline const auto& GetCheckPointPos() const noexcept {
		return checkPointPos;
	}

	/// <summary>
	/// ���o���a��q
	/// </summary>
	/// <returns>HP</returns>
	inline const auto& GetHP() const noexcept { return HP; }

	/// <summary>
	/// ���o���a����
	/// </summary>
	/// <returns>Point</returns>
	inline const auto& GetPoint() const noexcept { return point; }

	/// <summary>
	/// �W�[����
	/// </summary>
	/// <param name="val">lvalue ref</param>
	inline auto addPoint(const int& val) noexcept { point += val; }
	/// <summary>
	/// �W�[����
	/// </summary>
	/// <param name="val">rvalue ref</param>
	inline auto addPoint(int&& val) noexcept { point += val; }

	/// <summary>
	/// ��q���W
	/// </summary>
	inline auto IncHP() noexcept { ++HP; }

	/// <summary>
	/// ��q����
	/// </summary>
	inline auto DecHP() noexcept { --HP; }

	// inline std::shared_ptr<Util::BGM>& GetBGM() noexcept { return bgm; }

	/// <summary>
	/// �]�w�O�_�n����
	/// </summary>
	/// <param name="val"></param>
	inline auto SetRestart(bool val) noexcept { m_Restart = val; }

	/// <summary>
	/// �x�s��m
	/// </summary>
	/// <param name="pos">Position</param>
	inline auto SaveCheckPointPos(const glm::vec2& pos) noexcept {
		checkPointPos = pos;
	}

	/// <summary>
	/// �O�_��Ȱ����A
	/// </summary>
	bool pause{ false };

	/// <summary>
	/// �O�_�ҥεL�ļҦ�
	/// </summary>
	bool opMode = false;

	/// <summary>
	/// �C��BGM
	/// </summary>
	std::shared_ptr<Util::BGM> bgm = nullptr;
	std::shared_ptr<Util::SFX> sfx = nullptr;


private:
	/// <summary>
	/// �޲z�Ҧ����
	/// </summary>
	FormManger MyFM{};

	/// <summary>
	/// ���aHP
	/// </summary>
	int HP = 3;

	/// <summary>
	/// ���a����
	/// </summary>
	int point = 0;
	// std::vector<std::shared_ptr<MyBGM::BGM>> bgms;

	/// <summary>
	/// �������A
	/// </summary>
	bool endstate = false;

	/// <summary>
	/// ���Ҫ��A
	/// </summary>
	bool m_Restart = false;

	/// <summary>
	/// �W�@�Ӧs���I�y��
	/// </summary>
	glm::vec2 checkPointPos{ 0, 0 };
};


#endif // !GAMEMANGER_HPP
