#pragma once
#ifndef FIREFLOWER_HPP
#define FIREFLOWER_HPP

#include "Props.hpp"
#include "ObjectType.hpp"
#include "Object/Interface/IFrames.hpp"
#include "Interface/ICollisionable.hpp"

namespace MyAPP {
	namespace Form {
		namespace Object {
			namespace Props {
				/// <summary>
				/// �Ҧ��D�㪺�����O �~��ImageObject
				/// </summary>
				class FireFlower : Interface::ICollisionable, Interface::Iframes, public Props {
				public:
					explicit FireFlower(const std::string& name,
						const float zIndex,
						const glm::vec2& pivot = { 0, 0 })
						: Props(name, frames[0], zIndex, pivot) {
						MyType = ObjectType::FireFlower;
					}

					FireFlower(const FireFlower& other) = delete;

					FireFlower(FireFlower&& other) = delete;

					FireFlower() = delete;


					static constexpr auto GetFrames() noexcept { return frames; }

					virtual void behavior(void* data = nullptr) override;
					virtual std::string GetFrame() const noexcept { return frames[imgindex]; }

				protected:
					virtual void PlayFrames() noexcept override;

					virtual void CheckCollision(void* data) override;

				private:
					int count{ 0 }, imgindex{ 0 };
					static constexpr inline char* const frames[] = { R"(imgs\super mario\FireFlower\frame0.png)", R"(imgs\super mario\FireFlower\frame1.png)", R"(imgs\super mario\FireFlower\frame2.png)", R"(imgs\super mario\FireFlower\frame3.png)" };
				};
			}
		}
	}
}
#endif // !BRICK_HPP
