#pragma once
#ifndef COIN_HPP
#define COIN_HPP

#include "Brick.hpp"
#include "ObjectType.hpp"
namespace MyAPP {
	namespace Form {
		namespace Object {
			/// <summary>
			/// �������� �~��Brick
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
				/// �Q�V���ƥ�
				/// </summary>
				virtual void bonk() noexcept override;

				/// <summary>
				/// ����s�ɰ���
				/// </summary>
				/// <param name="data"></param>
				virtual void behavior(void* data = nullptr) override;

				static constexpr auto GetFrames() noexcept { return Frames; }

			private:
				/// <summary>
				/// ����Ϥ�
				/// </summary>
				void PlayGIF() noexcept;


				// static constexpr inline char* const EmptyBlockImagePath{ "imgs/super mario/EmptyBlock.png" };
				/// <summary>
				/// �V�ƶ��X
				/// </summary>
				static constexpr inline char* const Frames[] = { "imgs/super mario/1-1/CoinForBlueBG/frame0.png", "imgs/super mario/1-1/CoinForBlueBG/frame1.png", "imgs/super mario/1-1/CoinForBlueBG/frame2.png", "imgs/super mario/1-1/CoinForBlueBG/frame3.png", "imgs/super mario/1-1/CoinForBlueBG/frame4.png", "imgs/super mario/1-1/CoinForBlueBG/frame5.png" };
				int count{ 0 }, imgindex{ 0 };
				bool play{ true };
			};
		}
	}
}
#endif // !QUESTIONBLOCK_HPP
