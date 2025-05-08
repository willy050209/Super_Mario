#include "MakeObject.hpp"
#include "ImageObject.hpp"
#include "Mario.hpp"
#include <Position.hpp>

using namespace MyAPP::Form::Object;

std::shared_ptr<MyAPP::Form::Object::SpinningFireBalls> MyAPP::Form::Object::MakeObject::make_SpinningFireBalls(const std::string& name, glm::vec2 pos, int zindex) noexcept {
	auto result = std::make_shared<SpinningFireBalls>(name, zindex);
	std::vector<std::shared_ptr<FireBalls>> fireballs;
	for (int i = 0; i < 6; ++i) {
		fireballs.push_back(std::make_shared<FireBalls>("", 0));
	}
	result->userdata = std::make_shared<std::vector<std::shared_ptr<FireBalls>>>(fireballs);
	result->SetPosition(pos);
	return result;
}

std::pair<std::shared_ptr<ImageObject>, std::shared_ptr<Mario>> MyAPP::Form::Object::MakeObject::make_Background_And_Mario(std::string&& backgrount_FilePath, glm::vec2 marioPos, int backgroundZindex, int marioZindex) noexcept {

	auto background = std::make_shared<ImageObject>("Background", backgrount_FilePath, backgroundZindex);
	background->SetPosition({ GetX0(background), 0 });
	background->userdata = make_Bricks();

	auto mario = std::make_shared<Mario>("Mario", marioZindex);
	mario->SetPosition(marioPos);
	mario->userdata = background->userdata;
	
	return std::pair<std::shared_ptr<ImageObject>, std::shared_ptr<Mario>>(background, mario);
}

std::shared_ptr<std::vector<std::shared_ptr<Brick>>> MyAPP::Form::Object::MakeObject::make_Bricks() noexcept {
	return std::make_shared<std::vector<std::shared_ptr<Brick>>>();
}

std::shared_ptr<std::vector<std::shared_ptr<Character>>> MyAPP::Form::Object::MakeObject::make_Characters() noexcept {
	return std::make_shared<std::vector<std::shared_ptr<Character>>>();
}

std::shared_ptr<std::vector<std::shared_ptr<Coin>>> MyAPP::Form::Object::MakeObject::make_Coins() noexcept {
	return std::make_shared<std::vector<std::shared_ptr<Coin>>>();
}





