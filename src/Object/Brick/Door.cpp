#include "Object/Brick/Door.hpp"
#include "GameManager.hpp"
#include "Form/FormNames.hpp"
#include "InitFormFunc.hpp"

void MyAPP::Form::Object::Door::behavior(void* data) {
	auto& FM = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	if (inRange(marioPos, marioSize)) {
		auto& objandform = FM.GetFormAndObject(FM.GetNowForm());
		for (auto& eventobj : objandform.m_Events) {
			eventobj->Enable = false;
		}
		auto ChangeFormEventObject = (FM.GetFormObject<EventObject>(FM.GetNowForm(), "ChangeFormEvent"));
		ChangeFormEventObject->Enable = true;
		if (FM.GetNowForm() == MyAPP::Form::FormNames::Form_1_1) {
			initForm_1_1_to_1_2(static_cast<MyAPP::GameManager*>(data));
			ChangeFormEventObject->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_1_to_1_2);
		}
		else if (FM.GetNowForm() == MyAPP::Form::FormNames::Form_1_1_Pipe) {
			auto& form_1_1_OBJ = FM.GetFormAndObject(MyAPP::Form::FormNames::Form_1_1);
			std::for_each(std::execution::par_unseq, form_1_1_OBJ.m_Characters.begin(), form_1_1_OBJ.m_Characters.end(), [displacement = GetSize().x * (-107)](auto& it) {
				it->incPositionX(displacement);
			});
			std::for_each(std::execution::par_unseq, form_1_1_OBJ.m_Images.begin(), form_1_1_OBJ.m_Images.end(), [displacement = GetSize().x * (-107)](auto& it) {
				it->incPositionX(displacement);
			});
			(FM.GetFormObject<Mario>(MyAPP::Form::FormNames::Form_1_1, "Mario"))->SetPosition({ -(WINDOW_WIDTH >> 1) + GetSize().x * 9, GetY0(this) - GetSize().y * 10 });
			(FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_1, "freeForm_1_1_pipe"))->Enable = true;
			ChangeFormEventObject->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_1);
			(FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_1, "UpdateHPText"))->Enable = true;
			(FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_1, "UpdatePointText"))->Enable = true;
		}
		else if (FM.GetNowForm() == MyAPP::Form::FormNames::Form_1_1_to_1_2) {
			initForm_1_2(static_cast<MyAPP::GameManager*>(data));
			ChangeFormEventObject->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_2);
		}
		else if (FM.GetNowForm() == MyAPP::Form::FormNames::Form_1_2_Pipe) {
			auto& form_1_2_OBJ = FM.GetFormAndObject(MyAPP::Form::FormNames::Form_1_2);
			std::for_each(std::execution::par_unseq, form_1_2_OBJ.m_Characters.begin(), form_1_2_OBJ.m_Characters.end(), [displacement = GetSize().x * (-7)](auto& it) {
				it->incPositionX(displacement);
			});
			std::for_each(std::execution::par_unseq, form_1_2_OBJ.m_Images.begin(), form_1_2_OBJ.m_Images.end(), [displacement = GetSize().x * (-7)](auto& it) {
				it->incPositionX(displacement);
			});
			(FM.GetFormObject<Mario>(MyAPP::Form::FormNames::Form_1_2, "Mario"))->SetPosition({ -(WINDOW_WIDTH >> 1) + GetSize().x * 10, GetY0(this) - GetSize().y * 10 });
			ChangeFormEventObject->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_2);
			(FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_2, "freeForm_1_2_Pipe"))->Enable = true;
			(FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_2, "UpdateHPText"))->Enable = true;
			(FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_2, "UpdatePointText"))->Enable = true;
		}
		else if (FM.GetNowForm() == MyAPP::Form::FormNames::Form_1_2) {
			initForm_1_4(static_cast<MyAPP::GameManager*>(data));
			ChangeFormEventObject->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_4);
		}
		else {
			winForm(static_cast<MyAPP::GameManager*>(data));
			ChangeFormEventObject->userdata = std::make_shared<std::string>("Win");
		}
		// initForm_1_2(static_cast<MyAPP::GameManager*>(data));
	}
}