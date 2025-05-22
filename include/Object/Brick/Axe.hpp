#pragma once
#ifndef AXE_HPP
#define AXE_HPP
#include "Object/Brick/Brick.hpp"
#include "Interface/ICollisionable.hpp"
#include "Interface/Iframes.hpp"

namespace MyAPP::Form::Object {
	/// <summary>
	/// ���Y���� �~��Brick
	/// </summary>
	class Axe : Interface::ICollisionable, Interface::Iframes, public Brick {
	public:
		explicit Axe(const std::string& name,
			const float zIndex,
			const glm::vec2& pivot = { 0, 0 })
			: Brick(name, Frames[0], zIndex, pivot) {
			MyType = ObjectType::Axe;
			collisionable = false;
		}

		Axe(const Axe&) = delete;

		Axe(Axe&&) = delete;

		Axe() = delete;

		/// <summary>
		/// �Q�V���ƥ�
		/// </summary>
		virtual void bonk() noexcept override {};

		/// <summary>
		/// ����s�ɰ���
		/// </summary>
		/// <param name="data"></param>
		virtual void behavior(void* data = nullptr) override;

		static constexpr auto GetFrames() noexcept { return Frames; }

		virtual std::string GetFrame() const noexcept override { return Frames[imgindex]; }


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
		static constexpr inline char* const Frames[] = { "imgs/super mario/Axe/frame0.png", "imgs/super mario/Axe/frame1.png", "imgs/super mario/Axe/frame2.png", "imgs/super mario/Axe/frame3.png", "imgs/super mario/Axe/frame4.png", "imgs/super mario/Axe/frame5.png" };
		int count{ 0 }, imgindex{ 0 };
		bool play{ true }, enable{ true };
	};
}
#endif