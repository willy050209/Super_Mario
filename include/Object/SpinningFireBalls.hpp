#pragma once
#ifndef SPINNINGFIREBALLS_HPP
#define SPINNINGFIREBALLS_HPP

#include "Brick.hpp"
#include "ObjectType.hpp"
#include <string>

namespace MyAPP {
	namespace Form {
		namespace Object {
			/// <summary>
			/// ���W�j�Y���� �~��Brick
			/// </summary>
			class SpinningFireBalls : public Brick {
			public:
				explicit SpinningFireBalls(const std::string& name,
					const float zIndex,
					const glm::vec2& pivot = { 0, 0 })
					: Brick(name, R"(imgs\super mario\SpinningFireBalls\frame0.png)", zIndex, pivot) {
					MyType = ObjectType::SpinningFireBalls;
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

				SpinningFireBalls(const SpinningFireBalls& other) = delete;

				SpinningFireBalls(SpinningFireBalls&& other) = delete;

				SpinningFireBalls() = delete;

				/// <summary>
				/// �Q�V���ƥ�
				/// </summary>
				virtual void bonk() noexcept override;

				/// <summary>
				/// ����s�ɰ���
				/// </summary>
				/// <param name="data"></param>
				virtual void behavior(void* data = nullptr) override;

				inline auto GetFrame() const noexcept {
					return R"(imgs\super mario\SpinningFireBalls\frame)" + std::to_string(imgindex) + ".png";
				}

			private:
				/// <summary>
				/// ����Ϥ�
				/// </summary>
				void PlayGIF() noexcept;

				/*template<size_t N>
				static constexpr auto init_Frames() noexcept {
					std::array<std::string, N> _{};
					for (int i = 0; i < N; ++i) {
						_[i] = R"(imgs\super mario\SpinningFireBalls\frame)" + std::to_string(i) + ".png";
					}
					return _;
				}*/

				// static constexpr inline char* const EmptyBlockImagePath{ "imgs/super mario/EmptyBlock.png" };
				/// <summary>
				/// �V�ƶ��X
				/// </summary>
				//std::array<std::string, 103> Frames; // = init_Frames<103>();
				int count{ 0 }, imgindex{ 0 };
				bool play{ true };
			};
		}
	}
}
#endif // !QUESTIONBLOCK_HPP
