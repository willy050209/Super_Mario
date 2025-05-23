#pragma once

#ifndef POINTS_HPP
#define POINTS_HPP

#include "Object/ImageObject.hpp"
#include "ObjectType.hpp"
#include "Util/Image.hpp"
#include "config.hpp"
#include <string>
#include <memory>
#include <glm/vec2.hpp>

namespace MyAPP::Form::Object {

	class Points : public ImageObject {
	public:
		explicit Points(const std::string& name,
			const float zIndex = 80,
			const glm::vec2& pivot = { 0, 0 })
			: ImageObject(name, std::make_shared<Util::Image>(PointsImage[0]), zIndex, pivot) {
			MyType = ObjectType::Points;
			collisionable = false;
		}
		Points(const Points&) = delete;

		Points(Points&&) = delete;

		Points() = delete;

		virtual void behavior(void* data = nullptr) override;

		enum class Point {
			pts100 = 0,
			pts200 = 1,
			pts400 = 2,
			pts500 = 3,
			pts800 = 4,
			pts1000 = 5,
			pts2000 = 6,
			pts4000 = 7,
			pts5000 = 8,
			pts1up = 9
		};

		void setPoint(Point point);

		int count = 0;

		private:

		static constexpr inline char* const PointsImage[]{
			R"(imgs\super mario\100pts.png)",
			R"(imgs\super mario\200pts.png)",
			R"(imgs\super mario\400pts.png)",
			R"(imgs\super mario\500pts.png)",
			R"(imgs\super mario\800pts.png)",
			R"(imgs\super mario\1000pts.png)",
			R"(imgs\super mario\2000pts.png)",
			R"(imgs\super mario\4000pts.png)",
			R"(imgs\super mario\5000pts.png)",
			R"(imgs\super mario\1up.png)"
		};
	};

}

#endif // !POINTS_HPP
