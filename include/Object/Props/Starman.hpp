#pragma once
#ifndef STARMAN_HPP
#define STARMAN_HPP

#include "Props.hpp"
#include "ObjectType.hpp"
#include "Object/Interface/IFrames.hpp"

namespace MyAPP {
	namespace Form {
		namespace Object {
			namespace Props {
				/// <summary>
				/// �Ҧ��D�㪺�����O �~��ImageObject
				/// </summary>
				class Starman : Interface::Iframes, public Props {
				public:
					explicit Starman(const std::string& name,
						const float zIndex,
						const glm::vec2& pivot = { 0, 0 })
						: Props(name, frames[0], zIndex, pivot) {
						MyType = ObjectType::Starman;
					}

					Starman(const Starman& other) = delete;

					Starman(Starman&& other) = delete;

					Starman() = delete;


					virtual void behavior(void* data = nullptr) override;

					virtual std::string GetFrame() const noexcept { return *frames; }

					static constexpr auto GetFrames() noexcept { return frames; }

				protected:
					virtual void PlayFrames() noexcept override;

					virtual void touch(void* gm) override;

				private:
					int count{ 0 }, imgindex{ 0 };
					static constexpr inline char* const frames[] = { R"(imgs\super mario\Starman\frame0.png)", R"(imgs\super mario\Starman\frame1.png)", R"(imgs\super mario\Starman\frame2.png)", R"(imgs\super mario\Starman\frame3.png)" };
				};
			}
		}
	}
}
#endif // !BRICK_HPP
