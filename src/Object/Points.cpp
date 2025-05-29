#include "Object/Points.hpp"
#include "GameManager.hpp"
#include "FormManger.hpp"

void MyAPP::Form::Object::Points::behavior(void* data) {
	using MyAPP::Form::Object::ImageObject;
	if (m_Visible) {
		if (count <= 0) {
			auto GM = static_cast<GameManager*>(data);
			auto& FM = GM->GetFormManger();
			FM.removeFirstObject<ImageObject>(FM.GetNowForm(), name);
			m_Visible = false;
			return;
		}
		--count;
		m_Transform.translation.y++;
	}
}
void MyAPP::Form::Object::Points::setPoint(PointType pointType) {
	if (pointType < PointType::pts100 || pointType > PointType::pts1up)
		return;
	setImage(PointsImage[(int)pointType]);
	count = FPS_CAP / 2;
}
void MyAPP::Form::Object::Points::UpdatePoint(MyAPP::Form::FormManger& FM, PointType pointType) {
	using MyAPP::Form::Object::Mario;
	using MyAPP::Form::Object::EventObject;
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	{
		auto event = FM.GetFormObject<EventObject>(FM.GetNowForm(), "UpdateHPText");
		if (event) {
			event->Enable = true;
		}
	}
	{
		auto pointobj = std::make_shared<Points>("Point");
		if (pointobj) {
			pointobj->setPoint(pointType);
			pointobj->SetPosition(mario->GetPosition() + glm::vec2(0, mario->GetSize().y / 2));
			FM.addObject(FM.GetNowForm(), std::move(pointobj));
		}
	}
};