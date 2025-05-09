#include "MakeObject.hpp"
#include "ImageObject.hpp"
#include "Mario.hpp"
#include "Position.hpp"

#include <memory>
#include <fstream>


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

std::pair<std::shared_ptr<ImageObject>, std::shared_ptr<Mario>> MyAPP::Form::Object::MakeObject::make_Background_And_Mario(
	std::string&& backgrount_FilePath, std::shared_ptr<std::vector<std::shared_ptr<Brick>>> Bricks,
	glm::vec2 marioPos, int backgroundZindex, int marioZindex) noexcept {

	auto background = std::make_shared<ImageObject>("Background", backgrount_FilePath, backgroundZindex);
	background->SetPosition({ GetX0(background), 0 });
	background->userdata = Bricks;

	auto mario = std::make_shared<Mario>("Mario", marioZindex);
	mario->SetPosition(marioPos);
	mario->userdata = background->userdata;
	
	return std::pair<std::shared_ptr<ImageObject>, std::shared_ptr<Mario>>(background, mario);
}

std::shared_ptr<std::vector<std::shared_ptr<Brick>>> MyAPP::Form::Object::MakeObject::make_Bricks() noexcept {
	return std::make_shared<std::vector<std::shared_ptr<Brick>>>();
}

std::shared_ptr<std::vector<std::shared_ptr<Brick>>> MyAPP::Form::Object::MakeObject::make_Bricks_From_File(std::string&& filename, bool isDark) noexcept {
	Fileinfo fileinfo;
	auto bricks = MakeObject::make_Bricks();
	std::ifstream inp(filename);
	while (!inp.eof()) {
		fileinfo.GetFileDate(inp);
		fileinfo.ChangeXY();
		auto ptr = make_BrickPtr(fileinfo, isDark);
		if (ptr) {
			bricks->push_back(ptr);
		}
	}
	return bricks;
}

std::shared_ptr<Brick> MyAPP::Form::Object::MakeObject::make_BrickPtr(const Fileinfo& fileinfo, bool isDark) noexcept {
	std::shared_ptr<Brick> BrickPtr = nullptr;
	if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Brick) {
		BrickPtr = std::make_shared<Brick>("",
			((isDark) ? MyAPP::MyResourcesFilePath::BlockDarkImagePath : MyAPP::MyResourcesFilePath::BlockImagePath), 1);
		BrickPtr->SetPosition(fileinfo.XY);
		BrickPtr->SetVisible(true);
		BrickPtr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::QuestionBlock) {
		BrickPtr = std::make_shared<QuestionBlock>("QuestionBlock", (*QuestionBlock::GetFrames()), 10);
		BrickPtr->SetPosition(fileinfo.XY);
		BrickPtr->SetVisible(fileinfo.Visibility);
		BrickPtr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::HiddenBrick) {
		BrickPtr = std::make_shared<HiddenBrick>("HiddenBrick",
			((isDark) ? HiddenBrick::GetDefultDarkImagePath() : HiddenBrick::GetDefultImagePath()), 10);
		BrickPtr->SetPosition(fileinfo.XY);
		BrickPtr->SetVisible(fileinfo.Visibility);
		BrickPtr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Coin) {
		BrickPtr = std::make_shared<Coin>("Coin", 10);
		BrickPtr->SetPosition(fileinfo.XY);
		BrickPtr->SetVisible(fileinfo.Visibility);
		BrickPtr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::CheckPoint) {
		BrickPtr = std::make_shared<CheckPoint>("CheckPoint");
		BrickPtr->SetPosition(fileinfo.XY);
		BrickPtr->SetVisible(fileinfo.Visibility);
		BrickPtr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::SpinningFireBalls) {
		BrickPtr = make_SpinningFireBalls();
		BrickPtr->SetPosition(fileinfo.XY);
		BrickPtr->SetVisible(fileinfo.Visibility);
		BrickPtr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::PipeBrick) {
		BrickPtr = std::make_shared<PipeBrick>("PipeBrick",0);
		BrickPtr->SetPosition(fileinfo.XY);
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Door) {
		BrickPtr = std::make_shared<Door>("Door");
		BrickPtr->SetPosition(fileinfo.XY);
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Flagpole) {
		BrickPtr = std::make_shared<Flagpole>("Flagpole");
		BrickPtr->SetPosition(fileinfo.XY);
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Floor) {
		BrickPtr = std::make_shared<Floor>("Floor",
			(isDark) ? MyAPP::MyResourcesFilePath::FloorDarkImagePath :
					   MyAPP::MyResourcesFilePath::FloorImagePath);
		BrickPtr->SetPosition(fileinfo.XY);
		BrickPtr->SetVisible(fileinfo.Visibility);
		BrickPtr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Stairs) {
		BrickPtr = std::make_shared<Floor>("Stairs",
			(isDark) ? MyAPP::MyResourcesFilePath::StairsBrickDarkImagePath : MyAPP::MyResourcesFilePath::StairsBrickImagePath);
		BrickPtr->SetPosition(fileinfo.XY);
		BrickPtr->SetVisible(fileinfo.Visibility);
		BrickPtr->collisionable = fileinfo.Collisionable;
	}
	return BrickPtr;
}

std::shared_ptr<std::vector<std::shared_ptr<Character>>> MyAPP::Form::Object::MakeObject::make_Characters() noexcept {
	return std::make_shared<std::vector<std::shared_ptr<Character>>>();
}

std::shared_ptr<std::vector<std::shared_ptr<Coin>>> MyAPP::Form::Object::MakeObject::make_Coins() noexcept {
	return std::make_shared<std::vector<std::shared_ptr<Coin>>>();
}

std::shared_ptr<std::vector<std::shared_ptr<TextObject>>> MyAPP::Form::Object::MakeObject::make_GameText() noexcept {
	auto result = std::make_shared<std::vector<std::shared_ptr<TextObject>>>();
	auto texttime = std::make_shared<TextObject>("Timetext", MyAPP::MyResourcesFilePath::MyFontPath, 20, "300", Util::Color::FromName(Util::Colors::WHITE), 100);
	texttime->SetPosition({ GetX0(texttime), GetY0(texttime) });
	result->push_back(texttime);

	auto text = std::make_shared<TextObject>("HPText", MyAPP::MyResourcesFilePath::MyFontPath, 20, "HP:3", Util::Color::FromName(Util::Colors::WHITE), 100);
	text->SetPosition({ -GetX0(text), GetY0(text) });
	result->push_back(text);

	auto pointtext = std::make_shared<TextObject>("PointText", MyAPP::MyResourcesFilePath::MyFontPath, 20, "Point:0", Util::Color::FromName(Util::Colors::WHITE), 100);
	pointtext->SetPosition({ 0, GetY0(pointtext) });
	result->push_back(pointtext);

	return result;
}

std::shared_ptr<std::vector<std::shared_ptr<Character>>> MyAPP::Form::Object::MakeObject::make_Enemys_From_File(std::string&& filename, std::shared_ptr<std::vector<std::shared_ptr<Brick>>> Bricks) noexcept {
	Fileinfo fileinfo;
	auto enemys = MakeObject::make_Characters();
	std::ifstream inp(filename);
	while (!inp.eof()) {
		fileinfo.GetFileDate(inp);
		fileinfo.ChangeXY();
		auto ptr = make_EnemysPtr(fileinfo);
		if (ptr) {
			ptr->userdata = Bricks;
			enemys->push_back(ptr);
		}
	}
	return enemys;
}

std::shared_ptr<Character> MyAPP::Form::Object::MakeObject::make_EnemysPtr(const Fileinfo& fileinfo) noexcept {
	std::shared_ptr<Character> enemy = nullptr;
	if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Goomba) {
		enemy = std::make_shared<Goomba>("Goomba", 1);
		enemy->SetPosition(fileinfo.XY);
		enemy->SetVisible(true);
		enemy->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Turtle) {
		enemy = std::make_shared<Turtle>("Turtle", 1);
		enemy->SetPosition(fileinfo.XY);
		enemy->SetVisible(true);
		enemy->collisionable = fileinfo.Collisionable;
	}
	
	return enemy;
}





