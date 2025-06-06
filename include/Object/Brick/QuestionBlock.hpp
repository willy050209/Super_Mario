#pragma once
#ifndef QUESTIONBLOCK_HPP
#define QUESTIONBLOCK_HPP

#include "Brick.hpp"
#include "ObjectType.hpp"
#include "FilePath.hpp"
#include "Interface/IFrames.hpp"
#include <string>
#include <glm/vec2.hpp>

namespace MyAPP {
	class GameManager;
}


namespace MyAPP::Form::Object {
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

		virtual std::string GetFrame() const noexcept { return Frames[GetFrameCount()]; }
				
		virtual void Reset() noexcept override {
			Brick::Reset();
			isbonked = false;
			play = true;
			GetFrameCount() = 0;
		}

		static constexpr size_t& GetFrameCount() noexcept {
			return frameCount;
		}

		static constexpr size_t GetMaxFrameCount() noexcept {
			return 6;
		}

		static void nextFrame() noexcept {
			frameCount = (frameCount + 1) % GetMaxFrameCount();
		}

	private:
		virtual void PlayFrames() noexcept;

		void CreateProp(GameManager* const GM) noexcept;

		static constexpr inline char* const Frames[] = { "imgs/super mario/QuestionBlock/frame0.png", "imgs/super mario/QuestionBlock/frame1.png", "imgs/super mario/QuestionBlock/frame2.png", "imgs/super mario/QuestionBlock/frame3.png", "imgs/super mario/QuestionBlock/frame4.png", "imgs/super mario/QuestionBlock/frame5.png" };

		bool play{ true }, isbonked{ false };

		BrickColor color{ BrickColor::normal };

		static inline size_t frameCount = 0;
	};
}

#endif // !QUESTIONBLOCK_HPP
