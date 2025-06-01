#pragma once

#ifndef FLAGFORMPOLE_HPP
#define FLAGFORMPOLE_HPP

#include "Object/ImageObject.hpp"
#include "ObjectType.hpp"
#include "Util/Image.hpp"
#include <string>
#include <memory>
#include <glm/vec2.hpp>

namespace MyAPP::Form::Object {

	class FlagFromPole : public ImageObject {
	public:
		explicit FlagFromPole(const std::string& name,
			const float zIndex,
			const glm::vec2& pivot = { 0, 0 })
			: ImageObject(name, std::make_shared<Util::Image>(FlagFromPoleImage), zIndex, pivot) {
			MyType = ObjectType::FlagFromPole;
		}
		FlagFromPole(const FlagFromPole&) = delete;

		FlagFromPole(FlagFromPole&&) = delete;

		FlagFromPole() = delete;

		virtual void behavior(void* data = nullptr) override;

		static constexpr inline auto FlagFromPoleImage{ R"(imgs\super mario\FlagFromPole.png)" };

		bool enabled{ false };
	};

}

#endif // !FLAGFORMPOLE_HPP
