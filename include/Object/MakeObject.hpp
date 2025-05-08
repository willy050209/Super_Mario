#pragma once
#ifndef MAKEoBJECT_HPP

#include "incallobj.hpp"

#include <tuple>
#include <memory>

namespace MyAPP {
	namespace Form {
		namespace Object {
			
			struct MakeObject {

				/// <summary>
				/// 建立包含火球的火柱方塊
				/// </summary>
				/// <param name="name">物件ID</param>
				/// <param name="zindex">圖層</param>
				/// <returns></returns>
				[[nodiscard]] static std::shared_ptr<SpinningFireBalls> make_SpinningFireBalls(const std::string& name = "SpinningFireBalls", glm::vec2 pos = {0,0}, int zindex = 100) noexcept;

				[[nodiscard]] static std::pair<std::shared_ptr<ImageObject>, std::shared_ptr<Mario>> make_Background_And_Mario(std::string&& backgrount_FilePath, glm::vec2 marioPos = { 0, 100 }, int backgroundZindex = 1, int marioZindex = 50) noexcept;

				[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<Brick>>> make_Bricks() noexcept;

				[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<Character>>> make_Characters() noexcept;

				[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<Coin>>> make_Coins() noexcept;
			};
		}
	}
}

#endif // !MAKEoBJECT_HPP