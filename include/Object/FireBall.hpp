#pragma once
#ifndef FIREBALLS_HPP
#define FIREBALLS_HPP

#include "Brick.hpp"
#include "ObjectType.hpp"
#include "FilePath.hpp"


namespace MyAPP {
	namespace Form {
		namespace Object {
			/// <summary>
			/// ���W���� �~��Brick�A�Фų�W�A��
			/// </summary>
			class FireBalls : public Brick {
			public:
				explicit FireBalls(const std::string& name,
					const float zIndex,
					const glm::vec2& pivot = { 0, 0 })
					: Brick(name, MyAPP::MyResourcesFilePath::FrieBall, zIndex, pivot) {
					MyType = ObjectType::FireBalls;
					collisionable = false;
					m_Visible = false;
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

				FireBalls(const FireBalls& other) = delete;

				FireBalls(FireBalls&& other) = delete;

				FireBalls() = delete;


				/// <summary>
				/// ����s�ɰ���
				/// </summary>
				/// <param name="data"></param>
				virtual void behavior(void* data = nullptr) override;


			private:

			};
		}
	}
}
#endif // !QUESTIONBLOCK_HPP
