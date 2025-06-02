#pragma once
#ifndef MAKEOBJECT_HPP
#define MAKEOBJECT_HPP
#include "Position.hpp"
#include "incallobj.hpp"
#include "MyDefine.hpp"
#include "userType.hpp"


#include <tuple>
#include <memory>
#include <fstream>

namespace MyAPP::Form::Object {

	struct PositionReference {
		/// <summary>
		/// �^�ǧ@���y�аѦҪ����
		/// </summary>
		/// <returns></returns>
		static const auto& GetPositionReference() {
			static ConstUniqueBrickPtr BrickPositionReference = std::make_unique<Brick>("", MyAPP::MyResourcesFilePath::BlockImagePath, 0);

			return BrickPositionReference;
		}

		CANNOTCREATE(PositionReference);
	};

	struct MakeObject {

		CANNOTCREATE(MakeObject);

		/// <summary>
		/// �a���ɮ榡
		/// </summary>
		struct Fileinfo {
			glm::vec2 XY{};
			int Type{};
			int Visibility{};
			int Collisionable{};
			std::string data{};

			/// <summary>
			/// �q�ɮ�Ū�����
			/// </summary>
			/// <param name="inp"></param>
			void GetFileDate(std::ifstream& inp) {
				if (inp.good()) {
					inp >> XY.x >> XY.y >> Type >> Visibility >> Collisionable;
					if (static_cast<ObjectType>(Type) == ObjectType::QuestionBlock ||
						static_cast<ObjectType>(Type) == ObjectType::PropBrick) {
						inp >> data;
					}
				}
			}

			/// <summary>
			/// �NXY�ର��ڮy��
			/// </summary>
			void ChangeXY() {
				auto& PositionReference = PositionReference::GetPositionReference();
				XY = XY * PositionReference->GetSize() + glm::vec2{ GetLeftEdge(PositionReference), GetTopEdge(PositionReference) };
			}
		};


		/// <summary>
		/// �إߥ]�t���y�����W���
		/// </summary>
		/// <param name="name">����ID</param>
		/// <param name="zindex">�ϼh</param>
		/// <returns>���W���������</returns>
		[[nodiscard]] static SpinningFireBallsPtr make_SpinningFireBalls(const std::string& name = "SpinningFireBalls", glm::vec2 pos = { 0, 0 }, int zindex = 100) noexcept;

		/// <summary>
		/// �إ߭I���ϻPMario
		/// </summary>
		/// <param name="backgrount_FilePath">�I���ϸ��|</param>
		/// <param name="marioPos">Mario�y��</param>
		/// <param name="backgroundZindex">�I����Zindex</param>
		/// <param name="marioZindex">MarioZindex</param>
		/// <returns> first : �I���� second : Mario</returns>
		[[nodiscard]] static BackgroundMarioPair make_Background_And_Mario(const std::string& backgrount_FilePath, std::shared_ptr<BrickPtrVec>& Bricks, glm::vec2 marioPos = { 0, 100 }, int backgroundZindex = 0, int marioZindex = 50) noexcept;


		/// <summary>
		/// �q�ɮ׫إ� Brick vector ����
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<BrickPtrVec> make_Bricks_From_File(const std::string& filename, BrickColor color = BrickColor::normal) noexcept;

		/// <summary>
		/// �إ� Brick ���а}�C
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<BrickPtrVec> make_Bricks() noexcept;

		/// <summary>
		/// �إ� Brick ����
		/// </summary>
		/// <param name="fileinfo"></param>
		/// <param name="isDark"></param>
		/// <returns></returns>
		[[nodiscard]] static BrickPtr make_BrickPtr(const Fileinfo& fileinfo, BrickColor color = BrickColor::normal) noexcept;

		/// <summary>
		/// �إ� Character vector ����
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<CharacterPtrVec> make_Characters() noexcept;

		/// <summary>
		/// �إ� Coin vector ����
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<CoinPtrVec> make_Coins() noexcept;

		/// <summary>
		/// �إ߮ɶ��B���ơB�ͩR��r���
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<TextObjectPtrVec> make_GameText() noexcept;

		/// <summary>
		/// �q�ɮ׫إ� enemys ���а}�C
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<CharacterPtrVec> make_Enemys_From_File(const std::string& filename, std::shared_ptr<BrickPtrVec>& Bricks) noexcept;

		/// <summary>
		/// �إ� Character ����
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static CharacterPtr make_EnemysPtr(const Fileinfo& fileinfo) noexcept;

		/// <summary>
		/// �إ� Props ���а}�C
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<PropsPtrVec> make_Props() noexcept;

		[[nodiscard]] static std::shared_ptr<ObjectPtrVec> make_Objs() noexcept;
	};

}

#endif // !MAKEOBJECT_HPP