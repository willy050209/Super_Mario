#include "Object/Points.hpp"
#include "GameManager.hpp"

void MyAPP::Form::Object::Points::behavior(void* data) {
	using MyAPP::Form::Object::ImageObject;
	if (m_Visible) {
		if (count <= 0) {
			auto GM = static_cast<GameManager*>(data);
			auto& FM = GM->GetFormManger();
			FM.removeObject<ImageObject>(FM.GetNowForm(), name);
			m_Visible = false;
			return;
		}
		--count;
		m_Transform.translation.y++;
	}
}
void MyAPP::Form::Object::Points::setPoint(Point point) {
	if (point < Point::pts100 || point > Point::pts1up) return;
	setImage(PointsImage[(int)point]);
	count = FPS_CAP / 2;
};