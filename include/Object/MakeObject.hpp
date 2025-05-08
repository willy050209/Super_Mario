#pragma once
#ifndef MAKEOBJECT_HPP
#define MAKEOBJECT_HPP

#include "incallobj.hpp"

#include <tuple>
#include <memory>

namespace MyAPP::Form::Object {

	struct MakeObject {

		/// <summary>
		/// 建立包含火球的火柱方塊
		/// </summary>
		/// <param name="name">物件ID</param>
		/// <param name="zindex">圖層</param>
		/// <returns>火柱方塊的指標</returns>
		[[nodiscard]] static std::shared_ptr<SpinningFireBalls> make_SpinningFireBalls(const std::string& name = "SpinningFireBalls", glm::vec2 pos = {0,0}, int zindex = 100) noexcept;

		/// <summary>
		/// 建立背景圖與Mario
		/// </summary>
		/// <param name="backgrount_FilePath">背景圖路徑</param>
		/// <param name="marioPos">Mario座標</param>
		/// <param name="backgroundZindex">背景圖Zindex</param>
		/// <param name="marioZindex">MarioZindex</param>
		/// <returns> first : 背景圖 second : Mario</returns>
		[[nodiscard]] static std::pair<std::shared_ptr<ImageObject>, std::shared_ptr<Mario>> make_Background_And_Mario(std::string&& backgrount_FilePath, glm::vec2 marioPos = { 0, 100 }, int backgroundZindex = 1, int marioZindex = 50) noexcept;

		/// <summary>
		/// 建立 Brick vector 指標
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] static std::shared_ptr<std::vector<std::shared_ptr<Brick>>> make_Bricks() noexcept;

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
	};

}

#endif // !MAKEOBJECT_HPP