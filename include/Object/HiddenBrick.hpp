#pragma once
#ifndef HIDDENBRICK_HPP
#define HIDDENBRICK_HPP

#include "Brick.hpp"
#include "ObjectType.hpp"
namespace MyAPP {
	namespace Form {
		namespace Object {
			class HiddenBrick : public Brick {
			public:
				explicit HiddenBrick(const std::string& name, const std::string& ImagePath,
					const float zIndex,
					const glm::vec2& pivot = { 0, 0 })
					: Brick(name, ImagePath, zIndex, pivot) {
					MyType = ObjectType::HiddenBrick;
					this->collisionable = false;
					this->m_Visible = false;
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

				HiddenBrick(const HiddenBrick& other) = delete;

				HiddenBrick(HiddenBrick&& other) = delete;

				HiddenBrick() = delete;

				inline void setDark() noexcept {
					blockState = EmptyBlockState::Dark;
				}

				virtual void behavior(void* data = nullptr) override;

				static constexpr inline char* const EmptyBlockImagePath{ "imgs/super mario/EmptyBlock.png" };
				static constexpr inline char* const EmptyBlockDarkImagePath{ "imgs/super mario/EmptyBlockDark.png" };

			private:
				enum class EmptyBlockState {
					normal,
					Dark
				} blockState = EmptyBlockState::normal;
			};
		}
	}
}
#endif // !QUESTIONBLOCK_HPP
