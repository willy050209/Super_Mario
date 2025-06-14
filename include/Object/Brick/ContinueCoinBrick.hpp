#pragma once

#ifndef CONTINUECOINBRICK_HPP
#define CONTINUECOINBRICK_HPP

#include "Brick.hpp"
#include "ObjectType.hpp"
#include "Coin.hpp"
#include "FilePath.hpp"

namespace MyAPP::Form::Object {

	class ContinueCoinBrick : public Brick {
	public:
		explicit ContinueCoinBrick(const std::string& name, const std::string& ImagePath,
			BrickColor color,
			const float zIndex,
			const glm::vec2& pivot = { 0, 0 })
			: Brick(name, ImagePath, zIndex, pivot),color(color) {
			MyType = ObjectType::ContinueCoinBrick;
		}

		ContinueCoinBrick(const ContinueCoinBrick&) = delete;

		ContinueCoinBrick(ContinueCoinBrick&&) = delete;

		ContinueCoinBrick() = delete;

		/// <summary>
		/// 被敲擊事件
		/// </summary>
		virtual void bonk() noexcept override;

		virtual void Reset() noexcept override {
			Brick::Reset();
			switch (color) {
			case MyAPP::Form::Object::BrickColor::normal:
				std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::BlockImagePath);
				break;
			case MyAPP::Form::Object::BrickColor::dark:
				std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::BlockDarkImagePath);
				break;
			case MyAPP::Form::Object::BrickColor::grey:
				std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::BlockGreyImagePath);
				break;
			default:
				break;
			}
			trigger = false;
			bonkedCount = 0;
		}

		/// <summary>
		/// 表單刷新時執行
		/// </summary>
		/// <param name="data"></param>
		virtual void behavior(void* data = nullptr) override;

	private:
		int bonkedCount{ 0 };
		bool trigger = false;
		BrickColor color;
	};
}

namespace MyAPP::Form {
	class FormManger;
}
#include "Interface/IFrames.hpp"
namespace MyAPP::Form::Object {

	class CoinPoints : Interface::Iframes, public ImageObject {
	public:
		explicit CoinPoints(const std::string& name,
			const float zIndex = 80,
			const glm::vec2& pivot = { 0, 0 })
			: ImageObject(name, std::make_shared<Util::Image>(*Coin::GetFrames()), zIndex, pivot) {
			MyType = ObjectType::CoinPoints;
			collisionable = false;
		}
		CoinPoints(const CoinPoints&) = delete;

		CoinPoints(CoinPoints&&) = delete;

		CoinPoints() = delete;

		virtual void behavior(void* data = nullptr) override;


		static void CreateCoinPoints(MyAPP::Form::FormManger& FM, glm::vec2 pos);

		virtual std::string GetFrame() const noexcept override { return Coin::GetFrames()[FrameIndex % 6]; }

	private:
		/// <summary>
		/// 播放圖片
		/// </summary>
		virtual void PlayFrames() noexcept override;
		int lifeCount = 0;
		int count = 0;
		int FrameIndex{ 0 };
		bool isPlay{ true };
	};

}

#endif // !CONTINUECOINBRICK_HPP
