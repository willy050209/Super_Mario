#pragma once
#ifndef BRICK_HPP
#define BRICK_HPP

#include "ImageObject.hpp"
#include "ObjectType.hpp"

/// <summary>
/// 所有磚頭的父類別 繼承ImageObject
/// </summary>
class Brick : public ImageObject {
public:

	enum class State {
		null, jump, down
	};

	explicit Brick(const std::string& name, const std::string& ImagePath,
		const float zIndex,
		const glm::vec2& pivot = { 0, 0 })
		:  ImageObject(name, std::make_shared<Util::Image>(ImagePath), zIndex, pivot) {
		MyType = ObjectType::Brick;
	}

	/*Brick(
		const std::string& name,
		const std::shared_ptr<Core::Drawable>& drawable,
		const float zIndex,
		const glm::vec2& pivot = { 0, 0 },
		const bool visible = true,
		const std::vector<std::shared_ptr<GameObject>>& children = std::vector<std::shared_ptr<GameObject>>()) : ImageObject(name, drawable, zIndex, pivot, visible, children) {
		MyType = ObjectType::Brick;
	}*/

	Brick(const Brick& other) = delete;

	Brick(Brick&& other) = delete;

	Brick() = delete;

	virtual void behavior(void* data = nullptr) override;

	/// <summary>
	/// 被敲擊事件
	/// </summary>
	virtual void bonk() noexcept;

	/// <summary>
	/// 跳躍觸發
	/// </summary>
	virtual void bonkJump() noexcept;

	/// <summary>
	/// 取得方塊目前狀態
	/// </summary>
	/// <returns></returns>
	inline auto getState() const noexcept { return state; }

protected:

	/// <summary>
	/// 執行跳躍
	/// </summary>
	void dojump() noexcept;

	/// <summary>
	/// 墜落事件
	/// </summary>
	void comeDown() noexcept;

	bool jumpenable{ true };
	State state{ State::null };
	//bool jumpFlag{ false }, comeDownFlag{ false };
	int jumpcount = 0;
	glm::vec2 pos{ 0, 0 };

};

#endif // !BRICK_HPP
