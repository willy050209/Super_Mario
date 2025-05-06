#pragma once
#ifndef PROPS_HPP
#define PROPS_HPP

#include "ImageObject.hpp"
#include "ObjectType.hpp"
namespace MyAPP {
	namespace Form {
		namespace Object {
			namespace Props {
				/// <summary>
				/// 所有道具的父類別 繼承ImageObject
				/// </summary>
				class Props : public ImageObject {
				public:
					/*enum class State {
						null,
						jump,
						down
					};*/

					explicit Props(const std::string& name, const std::string& ImagePath,
						const float zIndex,
						const glm::vec2& pivot = { 0, 0 })
						: ImageObject(name, std::make_shared<Util::Image>(ImagePath), zIndex, pivot) {
						MyType = ObjectType::Props;
					}

					Props(const Props& other) = delete;

					Props(Props&& other) = delete;

					Props() = delete;



					// static constexpr auto GetFrame0() const noexcept { return frames[0]; }

				protected:
					virtual void playFrames() = 0;

					virtual void touch(void* gm) = 0;

					int count{ 0 }, imgindex{ 0 };
					// static constexpr char* const frames[] = { R"(imgs\super mario\FireFlower\frame0.png)", R"(imgs\super mario\FireFlower\frame1.png)", R"(imgs\super mario\FireFlower\frame2.png)", R"(imgs\super mario\FireFlower\frame3.png)" };
				};
			}
		}
	}
}
#endif // !BRICK_HPP
