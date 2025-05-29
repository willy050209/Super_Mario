#include "Object/Brick/ContinueCoinBrick.hpp"
#include "GameManager.hpp"
#include "FormManger.hpp"
#include "filePath.hpp"

void MyAPP::Form::Object::ContinueCoinBrick::bonk() noexcept {
	if (bonkedCount < 9) {
		bonkedCount++;
		trigger = true;
	}
	else{
		switch (color) {
		case MyAPP::Form::Object::BrickColor::normal:
			std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::EmptyBlockImagePath);
			break;
		case MyAPP::Form::Object::BrickColor::dark:
			std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::EmptyBlockDarkImagePath);
			break;
		case MyAPP::Form::Object::BrickColor::grey:
			std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::EmptyBlockGreyImagePath);
			break;
		default:
			break;
		}
	}
}

void MyAPP::Form::Object::ContinueCoinBrick::behavior(void* data) {
	if (trigger) {
		CoinPoints::CreateCoinPoints(static_cast<GameManager*>(data)->GetFormManger(), GetPosition());
		trigger = false;
	}
}


void MyAPP::Form::Object::CoinPoints::CreateCoinPoints(MyAPP::Form::FormManger& FM, glm::vec2 pos) {
	auto pointobj = std::make_shared<CoinPoints>("CoinPoints");
	if (pointobj) {
		pointobj->SetPosition(pos + glm::vec2{ 0, pointobj->GetSize().y });
		pointobj->lifeCount = FPS_CAP / 2;
		FM.addObject(FM.GetNowForm(), std::move(pointobj));
	}
}

void MyAPP::Form::Object::CoinPoints::behavior(void* data) {
	using MyAPP::Form::Object::ImageObject;
	if (m_Visible) {
		PlayFrames();
		if (lifeCount <= 0) {
			auto GM = static_cast<GameManager*>(data);
			auto& FM = GM->GetFormManger();
			FM.removeFirstObject<ImageObject>(FM.GetNowForm(), name);
			m_Visible = false;
			return;
		}
		--lifeCount;
		m_Transform.translation.y++;
		count++;
	}
}

void MyAPP::Form::Object::CoinPoints::PlayFrames() noexcept {
	if(isPlay){
		if (count >= (FPS_CAP / 5)) {
			++FrameIndex;
			FrameIndex %= 6;
			std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(GetFrame());
			count = 0;
		}
	}
}