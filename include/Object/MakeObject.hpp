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
		/// 回傳作為座標參考的方塊
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
		/// 地圖檔格式
		/// </summary>
		struct Fileinfo {
			glm::vec2 XY{};
			int Type{};
			int Visibility{};
			int Collisionable{};

			/// <summary>
			/// 從檔案讀取資料
			/// </summary>
			/// <param name="inp"></param>
			void GetFileDate(std::ifstream& inp) {
				if (inp.good()) {
					inp >> XY.x >> XY.y >> Type >> Visibility >> Collisionable;
				}
			}

			/// <summary>
			/// 將XY轉為實際座標
			/// </summary>
			void ChangeXY() {
				auto& PositionReference = PositionReference::GetPositionReference();
				XY = XY * PositionReference->GetSize() + glm::vec2{ GetLeftEdge(PositionReference), GetTopEdge(PositionReference) };
			}
		};


		/// <summary>
		/// 建立包含火球的火柱方塊
		/// </summary>
		/// <param name="name">物件ID</param>
		/// <param name="zindex">圖層</param>
		/// <returns>火柱方塊的指標</returns>
		[[nodiscard]] static SpinningFireBallsPtr make_SpinningFireBalls(const std::string& name = "SpinningFireBalls", glm::vec2 pos = { 0, 0 }, int zindex = 100) noexcept;

		/// <summary>
		/// 建立背景圖與Mario
		/// </summary>
		/// <param name="backgrount_FilePath">背景圖路徑</param>
		/// <param name="marioPos">Mario座標</param>
		/// <param name="backgroundZindex">背景圖Zindex</param>
		/// <param name="marioZindex">MarioZindex</param>
		/// <returns> first : 背景圖 second : Mario</returns>
		[[nodiscard]] static BackgroundMarioPair make_Background_And_Mario(const std::string& backgrount_FilePath, std::shared_ptr<BrickPtrVec>& Bricks, glm::vec2 marioPos = { 0, 100 }, int backgroundZindex = 0, int marioZindex = 50) noexcept;


		/// <summary>
		/// 從檔案建立 Brick vector 指標
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<BrickPtrVec> make_Bricks_From_File(const std::string& filename, BrickColor color = BrickColor::normal) noexcept;

		/// <summary>
		/// 建立 Brick 指標陣列
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<BrickPtrVec> make_Bricks() noexcept;

		/// <summary>
		/// 建立 Brick 指標
		/// </summary>
		/// <param name="fileinfo"></param>
		/// <param name="isDark"></param>
		/// <returns></returns>
		[[nodiscard]] static BrickPtr make_BrickPtr(const Fileinfo& fileinfo, BrickColor color = BrickColor::normal) noexcept;

		/// <summary>
		/// 建立 Character vector 指標
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<Character>>> make_Characters() noexcept;

		/// <summary>
		/// 建立 Coin vector 指標
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<Coin>>> make_Coins() noexcept;

		/// <summary>
		/// 建立時間、分數、生命文字方塊
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<TextObject>>> make_GameText() noexcept;

		/// <summary>
		/// 從檔案建立 enemys 指標陣列
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<Character>>> make_Enemys_From_File(const std::string& filename, std::shared_ptr<std::vector<std::shared_ptr<Brick>>>& Bricks) noexcept;

		/// <summary>
		/// 建立 Character 指標
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<Character> make_EnemysPtr(const Fileinfo& fileinfo) noexcept;

		/// <summary>
		/// 建立 Props 指標陣列
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<Props::Props>>> make_Props() noexcept;
	};

}

#endif // !MAKEOBJECT_HPP