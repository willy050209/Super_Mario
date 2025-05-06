#pragma once
#ifndef QUESTIONBLOCK_HPP
#define QUESTIONBLOCK_HPP

#include "Brick.hpp"
#include "ObjectType.hpp"
#include "FilePath.hpp"

namespace MyAPP {
	namespace Form {
		namespace Object {
			class QuestionBlock : public Brick {
			public:
				explicit QuestionBlock(const std::string& name, const std::string& ImagePath,
					const float zIndex,
					const glm::vec2& pivot = { 0, 0 })
					: Brick(name, ImagePath, zIndex, pivot) {
					MyType = ObjectType::QuestionBlock;
				}

				/*QuestionBlock(
					const std::string& name,
					const std::shared_ptr<Core::Drawable>& drawable,
					const float zIndex,
					const glm::vec2& pivot = { 0, 0 },
					const bool visible = true,
					const std::vector<std::shared_ptr<GameObject>>& children = std::vector<std::shared_ptr<GameObject>>()) : Brick(name, drawable, zIndex, pivot, visible, children) {
					MyType = ObjectType::QuestionBlock;
				}*/

				QuestionBlock(const QuestionBlock& other) = delete;

				QuestionBlock(QuestionBlock&& other) = delete;

				QuestionBlock() = delete;

				inline void setDark() noexcept {
					blockState = EmptyBlockState::Dark;
				}

				virtual void bonk() noexcept override;

				virtual void behavior(void* data = nullptr) override;

				static constexpr auto GetFrames() noexcept {
					return Frames;
				}

				static constexpr auto GetEmptyBlockImagePath() noexcept { return *EmptyBlockImagePath; }

				static constexpr auto GetEmptyBlockDarkImagePath() noexcept { return *EmptyBlockDarkImagePath; }


			private:
				void PlayGIF() noexcept;

				static constexpr inline char* const Frames[] = { "imgs/super mario/QuestionBlock/frame0.png", "imgs/super mario/QuestionBlock/frame1.png", "imgs/super mario/QuestionBlock/frame2.png", "imgs/super mario/QuestionBlock/frame3.png", "imgs/super mario/QuestionBlock/frame4.png", "imgs/super mario/QuestionBlock/frame5.png" };

				static constexpr inline decltype(&MyAPP::MyResourcesFilePath::EmptyBlockImagePath) EmptyBlockImagePath{ &MyAPP::MyResourcesFilePath::EmptyBlockImagePath };
				static constexpr inline decltype(&MyAPP::MyResourcesFilePath::EmptyBlockDarkImagePath) EmptyBlockDarkImagePath{ &MyAPP::MyResourcesFilePath::EmptyBlockDarkImagePath };

				int count{ 0 }, imgindex{ 0 };
				bool play{ true };

				enum class EmptyBlockState {
					normal,
					Dark
				} blockState = EmptyBlockState::normal;
			};
		}
	}
}
#endif // !QUESTIONBLOCK_HPP
