#pragma once
#ifndef MAKEOBJECT_HPP
#define MAKEOBJECT_HPP
#include "Position.hpp"
#include "incallobj.hpp"


#include <tuple>
#include <memory>
#include <fstream>

namespace MyAPP::Form::Object {

	struct MakeObject {

		/// <summary>
		/// �a���ɮ榡
		/// </summary>
		struct Fileinfo {
			glm::vec2 XY{};
			int Type{};
			int Visibility{};
			int Collisionable{};

			/// <summary>
			/// �q�ɮ�Ū�����
			/// </summary>
			/// <param name="inp"></param>
			void GetFileDate(std::ifstream& inp) {
				if (inp.good()) {
					inp >> XY.x >> XY.y >> Type >> Visibility >> Collisionable;
				}
			}

			/// <summary>
			/// �NXY�ର��ڮy��
			/// </summary>
			void ChangeXY() {
				auto brick = std::make_unique<Brick>("", MyAPP::MyResourcesFilePath::BlockImagePath, 0);
				XY = XY * brick->GetSize() + glm::vec2{ GetX0(brick), GetY0(brick) };				
			}
		};

		/// <summary>
		/// �إߥ]�t���y�����W���
		/// </summary>
		/// <param name="name">����ID</param>
		/// <param name="zindex">�ϼh</param>
		/// <returns>���W���������</returns>
		[[nodiscard]] static std::shared_ptr<SpinningFireBalls> make_SpinningFireBalls(const std::string& name = "SpinningFireBalls", glm::vec2 pos = {0,0}, int zindex = 100) noexcept;

		/// <summary>
		/// �إ߭I���ϻPMario
		/// </summary>
		/// <param name="backgrount_FilePath">�I���ϸ��|</param>
		/// <param name="marioPos">Mario�y��</param>
		/// <param name="backgroundZindex">�I����Zindex</param>
		/// <param name="marioZindex">MarioZindex</param>
		/// <returns> first : �I���� second : Mario</returns>
		[[nodiscard]] static std::pair<std::shared_ptr<ImageObject>, std::shared_ptr<Mario>> make_Background_And_Mario(std::string&& backgrount_FilePath, std::shared_ptr<std::vector<std::shared_ptr<Brick>>> Bricks = nullptr, glm::vec2 marioPos = { 0, 100 }, int backgroundZindex = 0, int marioZindex = 50) noexcept;


		/// <summary>
		/// �q�ɮ׫إ� Brick vector ����
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<Brick>>> make_Bricks_From_File(std::string&& filename, bool isDark = false) noexcept;

		/// <summary>
		/// �إ� Brick ���а}�C
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<Brick>>> make_Bricks() noexcept;

		/// <summary>
		/// �إ� Brick ����
		/// </summary>
		/// <param name="fileinfo"></param>
		/// <param name="isDark"></param>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<Brick> make_BrickPtr(const Fileinfo& fileinfo, bool isDark) noexcept;

		/// <summary>
		/// �إ� Character vector ����
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<Character>>> make_Characters() noexcept;

		/// <summary>
		/// �إ� Coin vector ����
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<Coin>>> make_Coins() noexcept;
	
		/// <summary>
		/// �إ߮ɶ��B���ơB�ͩR��r���
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<TextObject>>> make_GameText() noexcept;

		/// <summary>
		/// �q�ɮ׫إ� enemys ���а}�C
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<Character>>> make_Enemys_From_File(std::string&& filename, std::shared_ptr<std::vector<std::shared_ptr<Brick>>> Bricks) noexcept;
	
		/// <summary>
		/// �إ� Character ����
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<Character> make_EnemysPtr(const Fileinfo& fileinfo) noexcept;

		/// <summary>
		/// �إ� Props ���а}�C
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<Props::Props>>> make_Props() noexcept;
	
	};

}

#endif // !MAKEOBJECT_HPP