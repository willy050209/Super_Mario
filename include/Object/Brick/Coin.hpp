#pragma once
#ifndef COIN_HPP
#define COIN_HPP

#include "Brick.hpp"
#include "ObjectType.hpp"
#include "Interface/IFrames.hpp"
#include "Interface/ICollisionable.hpp"

namespace MyAPP::Form::Object {
	/// <summary>
	/// �������� �~��Brick
	/// </summary>
	class Coin :Interface::ICollisionable, Interface::Iframes, public Brick {
	public:
		explicit Coin(const std::string& name,
			const float zIndex,
			const glm::vec2& pivot = { 0, 0 })
			: Brick(name, Frames[0], zIndex, pivot) {
			MyType = ObjectType::Coin;
			collisionable = false;
		}

		Coin(const Coin& ) = delete;

		Coin(Coin&&) = delete;

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

		virtual std::string GetFrame() const noexcept { return Frames[GetFrameCount()]; }

		static inline size_t& GetFrameCount() noexcept {
			static size_t frameCount = 0;
			return frameCount;
		}

		static constexpr size_t GetMaxFrameCount() noexcept {
			return 6;
		}
				

	private:
		/// <summary>
		/// ����Ϥ�
		/// </summary>
		virtual void PlayFrames() noexcept override;

		void CheckCollision(void*) noexcept;

		// static constexpr inline char* const EmptyBlockImagePath{ "imgs/super mario/EmptyBlock.png" };
		/// <summary>
		/// �V�ƶ��X
		/// </summary>
		static constexpr inline char* const Frames[] = { "imgs/super mario/1-1/CoinForBlueBG/frame0.png", "imgs/super mario/1-1/CoinForBlueBG/frame1.png", "imgs/super mario/1-1/CoinForBlueBG/frame2.png", "imgs/super mario/1-1/CoinForBlueBG/frame3.png", "imgs/super mario/1-1/CoinForBlueBG/frame4.png", "imgs/super mario/1-1/CoinForBlueBG/frame5.png" };
		bool play{ true };
	};
}

#endif // !QUESTIONBLOCK_HPP
