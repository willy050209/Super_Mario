#pragma once
#ifndef QUESTIONBLOCK_HPP
#define QUESTIONBLOCK_HPP

#include "Brick.hpp"
#include "ObjectType.hpp"
#include "FilePath.hpp"
#include "Interface/IFrames.hpp"

namespace MyAPP {
	namespace Form {
		namespace Object {
			class QuestionBlock : Interface::Iframes, public Brick {
			public:
				explicit QuestionBlock(const std::string& name,
					BrickColor color_,
					const float zIndex = 10,
					bool isDark = false,
					const glm::vec2& pivot = { 0, 0 })
					: Brick(name, Frames[0], zIndex, pivot), color(color_) {
					MyType = ObjectType::QuestionBlock;

				}


				QuestionBlock(const QuestionBlock& other) = delete;

				QuestionBlock(QuestionBlock&& other) = delete;

				QuestionBlock() = delete;


				virtual void bonk() noexcept override;

				virtual void behavior(void* data = nullptr) override;

				static constexpr auto GetFrames() noexcept {
					return Frames;
				}

				virtual std::string GetFrame() const noexcept { return Frames[imgindex]; }
				

			private:
				virtual void PlayFrames() noexcept;

				static constexpr inline char* const Frames[] = { "imgs/super mario/QuestionBlock/frame0.png", "imgs/super mario/QuestionBlock/frame1.png", "imgs/super mario/QuestionBlock/frame2.png", "imgs/super mario/QuestionBlock/frame3.png", "imgs/super mario/QuestionBlock/frame4.png", "imgs/super mario/QuestionBlock/frame5.png" };

				int count{ 0 }, imgindex{ 0 };
				bool play{ true };

				BrickColor color{ BrickColor::normal };
			};
		}
	}
}
#endif // !QUESTIONBLOCK_HPP
