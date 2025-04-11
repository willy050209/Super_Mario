#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

#include "Object/Brick.hpp"

/// <summary>
/// �s���I���� �~��Brick
/// </summary>
class CheckPoint : public Brick {
public:

	/// <summary>
	/// 
	/// </summary>
	/// <param name="name">ID</param>
	/// <param name="ImagePath">�Ϥ����|(�w�] CheckPoint::CheckPointImagePath)</param>
	explicit CheckPoint(const std::string& name, const std::string& ImagePath = CheckPointImagePath,
		const float zIndex = -10,
		const glm::vec2& pivot = { 0, 0 })
		: Brick(name, ImagePath, zIndex, pivot) {
		MyType = ObjectType::CheckPoint;
	}

	//CheckPoint(
	//	const std::string& name,
	//	const std::shared_ptr<Core::Drawable>& drawable,
	//	const float zIndex,
	//	const glm::vec2& pivot = { 0, 0 },
	//	const bool visible = true,
	//	const std::vector<std::shared_ptr<GameObject>>& children = std::vector<std::shared_ptr<GameObject>>()) : Brick(name, drawable, zIndex, pivot, visible, children) {
	//	MyType = ObjectType::CheckPoint;
	//}

	CheckPoint(const Brick& CheckPoint) = delete;

	CheckPoint(Brick&& CheckPoint) = delete;

	//CheckPoint() = delete;

	/// <summary>
	/// �Ϥ����|
	/// </summary>
	static constexpr char* const CheckPointImagePath = "imgs/super mario/CheckPoint.png";

	bool Enable = true;
};
#endif