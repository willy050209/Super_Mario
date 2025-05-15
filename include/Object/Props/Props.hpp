#pragma once
#ifndef PROPS_HPP
#define PROPS_HPP

#include "ImageObject.hpp"
#include "ObjectType.hpp"
#include "Interface/ICollisionable.hpp"
namespace MyAPP {
	namespace Form {
		namespace Object {
			namespace Props {
				/// <summary>
				/// 所有道具的父類別 繼承ImageObject
				/// </summary>
				class Props :public ImageObject {
				public:

					explicit Props(const std::string& name, const std::string& ImagePath,
						const float zIndex,
						const glm::vec2& pivot = { 0, 0 })
						: ImageObject(name, std::make_shared<Util::Image>(ImagePath), zIndex, pivot) {
						MyType = ObjectType::Props;
					}

					Props(const Props& other) = delete;

					Props(Props&& other) = delete;

					Props() = delete;


				protected:

					int count{ 0 }, imgindex{ 0 };
					// static constexpr char* const frames[] = { R"(imgs\super mario\FireFlower\frame0.png)", R"(imgs\super mario\FireFlower\frame1.png)", R"(imgs\super mario\FireFlower\frame2.png)", R"(imgs\super mario\FireFlower\frame3.png)" };
				};
			}
		}
	}
}
#endif // !BRICK_HPP
