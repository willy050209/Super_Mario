#pragma once
#ifndef COIN_HPP
#define COIN_HPP

#include "Brick.hpp"
#include "ObjectType.hpp"
namespace MyAPP {
	namespace Form {
		namespace Object {
			/// <summary>
			/// 金幣物件 繼承Brick
			/// </summary>
			class Coin : public Brick {
			public:
				explicit Coin(const std::string& name,
					const float zIndex,
					const glm::vec2& pivot = { 0, 0 })
					: Brick(name, Frames[0], zIndex, pivot) {
					MyType = ObjectType::Coin;
					collisionable = false;
				}

				// explicit Coin(
				//	const std::string& name,
				//	const std::shared_ptr<Core::Drawable>& drawable,
				//	const float zIndex,
				//	const glm::vec2& pivot = { 0, 0 },
				//	const bool visible = true,
				//	const std::vector<std::shared_ptr<GameObject>>& children = std::vector<std::shared_ptr<GameObject>>()) : Brick(name, drawable, zIndex, pivot, visible, children) {
				//	MyType = ObjectType::Coin;
				//	collisionable = false;
				// }

				Coin(const Coin& other) = delete;

				Coin(Coin&& other) = delete;

				Coin() = delete;

				/// <summary>
				/// 被敲擊事件
				/// </summary>
				virtual void bonk() noexcept override;

				/// <summary>
				/// 表單刷新時執行
				/// </summary>
				/// <param name="data"></param>
				virtual void behavior(void* data = nullptr) override;

				static constexpr auto GetFrames() noexcept { return Frames; }

			private:
				/// <summary>
				/// 播放圖片
				/// </summary>
				void PlayGIF() noexcept;


				// static constexpr inline char* const EmptyBlockImagePath{ "imgs/super mario/EmptyBlock.png" };
				/// <summary>
				/// 幀數集合
				/// </summary>
				static constexpr inline char* const Frames[] = { "imgs/super mario/1-1/CoinForBlueBG/frame0.png", "imgs/super mario/1-1/CoinForBlueBG/frame1.png", "imgs/super mario/1-1/CoinForBlueBG/frame2.png", "imgs/super mario/1-1/CoinForBlueBG/frame3.png", "imgs/super mario/1-1/CoinForBlueBG/frame4.png", "imgs/super mario/1-1/CoinForBlueBG/frame5.png" };
				int count{ 0 }, imgindex{ 0 };
				bool play{ true };
			};
		}
	}
}
#endif // !QUESTIONBLOCK_HPP
