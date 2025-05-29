#include "incallobj.hpp"
#include "Position.hpp"
#include "config.hpp"
#include "userType.hpp"

#include <memory>
#include <fstream>


using namespace MyAPP::Form::Object;

SpinningFireBallsPtr MyAPP::Form::Object::MakeObject::make_SpinningFireBalls(const std::string& name, glm::vec2 pos, int zindex) noexcept {
	auto result = std::make_shared<SpinningFireBalls>(name, zindex);
	FireBallsPtrVec fireballs;
	for (int i = 0; i < 6; ++i) {
		fireballs.push_back(std::move(std::make_shared<FireBalls>("", 0)));
	}
	result->userdata = std::make_shared<FireBallsPtrVec>(std::move(fireballs));
	result->SetPosition(pos);
	return result;
}

BackgroundMarioPair MyAPP::Form::Object::MakeObject::make_Background_And_Mario(
	const std::string& backgrount_FilePath, std::shared_ptr<BrickPtrVec>& Bricks,
	glm::vec2 marioPos, int backgroundZindex, int marioZindex) noexcept {

	auto background = std::make_shared<ImageObject>("Background", backgrount_FilePath, backgroundZindex);
	background->SetPosition({ GetLeftEdge(background), 0 });
	background->userdata = Bricks;

	auto mario = std::make_shared<Mario>("Mario", marioZindex);
	mario->SetPosition(marioPos);
	mario->userdata = background->userdata;

	return std::make_pair<ImageObjectPtr, MarioPtr>(std::move(background), std::move(mario));
}

std::shared_ptr<BrickPtrVec> MyAPP::Form::Object::MakeObject::make_Bricks() noexcept {
	return std::make_shared<BrickPtrVec>();
}

std::shared_ptr<BrickPtrVec> MyAPP::Form::Object::MakeObject::make_Bricks_From_File(const std::string& filename, BrickColor color) noexcept {
	Fileinfo fileinfo;
	auto bricks = MakeObject::make_Bricks();
	std::ifstream inp(filename);
	while (!inp.eof()) {
		fileinfo.GetFileDate(inp);
		fileinfo.ChangeXY();
		auto ptr = make_BrickPtr(fileinfo, color);
		if (ptr) {
			bricks->push_back(std::move(ptr));
		}
	}
	return bricks;
}

BrickPtr MyAPP::Form::Object::MakeObject::make_BrickPtr(const Fileinfo& fileinfo, BrickColor color) noexcept {
	using namespace MyAPP;
	using namespace MyAPP::Form::Object;
	BrickPtr brick_ptr = nullptr;
	if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Brick) {
		switch (color) {
		case MyAPP::Form::Object::BrickColor::normal:
			brick_ptr = std::make_shared<Brick>("Brick", MyResourcesFilePath::BlockImagePath, 10);
			break;
		case MyAPP::Form::Object::BrickColor::dark:
			brick_ptr = std::make_shared<Brick>("Brick", MyResourcesFilePath::BlockDarkImagePath, 10);
			break;
		case MyAPP::Form::Object::BrickColor::grey:
			brick_ptr = std::make_shared<Brick>("Brick", MyResourcesFilePath::BlockGreyImagePath, 10);
			break;
		default:
			return brick_ptr;
		}
		brick_ptr->SetPosition(fileinfo.XY);
		brick_ptr->SetVisible(fileinfo.Visibility);
		brick_ptr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::QuestionBlock) {
		switch (color) {
		case MyAPP::Form::Object::BrickColor::normal:
			brick_ptr = std::make_shared<QuestionBlock>("QuestionBlock", BrickColor::normal, 10);
			break;
		case MyAPP::Form::Object::BrickColor::dark:
			brick_ptr = std::make_shared<QuestionBlock>("QuestionBlock", BrickColor::dark, 10);
			break;
		case MyAPP::Form::Object::BrickColor::grey:
			brick_ptr = std::make_shared<QuestionBlock>("QuestionBlock", BrickColor::grey, 10);
			break;
		default:
			return brick_ptr;
		}
		brick_ptr->SetPosition(fileinfo.XY);
		brick_ptr->SetVisible(fileinfo.Visibility);
		brick_ptr->collisionable = fileinfo.Collisionable;
		if (fileinfo.data == "BigMushroom") {
			brick_ptr->userdata = std::make_shared<std::string>(fileinfo.data);
		}
		else {
			brick_ptr->userdata = nullptr;
		}
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::HiddenBrick) {
		switch (color) {
		case MyAPP::Form::Object::BrickColor::normal:
			brick_ptr = std::make_shared<HiddenBrick>("HiddenBrick", MyResourcesFilePath::EmptyBlockImagePath, 10);
			break;
		case MyAPP::Form::Object::BrickColor::dark:
			brick_ptr = std::make_shared<HiddenBrick>("HiddenBrick", MyResourcesFilePath::EmptyBlockDarkImagePath, 10);
			break;
		case MyAPP::Form::Object::BrickColor::grey:
			brick_ptr = std::make_shared<HiddenBrick>("HiddenBrick", MyResourcesFilePath::EmptyBlockGreyImagePath, 10);
			break;
		default:
			return brick_ptr;
		}
		brick_ptr->SetPosition(fileinfo.XY);
		brick_ptr->SetVisible(fileinfo.Visibility);
		brick_ptr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Coin) {
		brick_ptr = std::make_shared<Coin>("Coin", 10);
		brick_ptr->SetPosition(fileinfo.XY);
		brick_ptr->SetVisible(fileinfo.Visibility);
		brick_ptr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::CheckPoint) {
		brick_ptr = std::make_shared<CheckPoint>("CheckPoint");
		brick_ptr->SetPosition(fileinfo.XY);
		brick_ptr->SetVisible(fileinfo.Visibility);
		brick_ptr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::SpinningFireBalls) {
		brick_ptr = make_SpinningFireBalls();
		brick_ptr->SetPosition(fileinfo.XY);
		brick_ptr->SetVisible(fileinfo.Visibility);
		brick_ptr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::PipeBrick) {
		brick_ptr = std::make_shared<PipeBrick>("PipeBrick",0);
		brick_ptr->SetPosition(fileinfo.XY);
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Door) {
		brick_ptr = std::make_shared<Door>("Door");
		brick_ptr->SetPosition(fileinfo.XY);
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Flagpole) {
		brick_ptr = std::make_shared<Flagpole>("Flagpole");
		brick_ptr->SetPosition(fileinfo.XY);
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Floor) {
		switch (color) {
		case MyAPP::Form::Object::BrickColor::normal:
			brick_ptr = std::make_shared<Floor>("Floor", MyResourcesFilePath::FloorImagePath, 10);
			break;
		case MyAPP::Form::Object::BrickColor::dark:
			brick_ptr = std::make_shared<Floor>("Floor", MyResourcesFilePath::FloorDarkImagePath, 10);
			break;
		case MyAPP::Form::Object::BrickColor::grey:
			brick_ptr = std::make_shared<Floor>("Floor", MyResourcesFilePath::FloorGreyImagePath, 10);
			break;
		default:
			return brick_ptr;
		}
		brick_ptr->SetPosition(fileinfo.XY);
		brick_ptr->SetVisible(fileinfo.Visibility);
		brick_ptr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Stairs) {
		switch (color) {
		case MyAPP::Form::Object::BrickColor::normal:
			brick_ptr = std::make_shared<Stairs>("Stairs", MyResourcesFilePath::StairsBrickImagePath, 10);
			break;
		case MyAPP::Form::Object::BrickColor::dark:
			brick_ptr = std::make_shared<Stairs>("Stairs", MyResourcesFilePath::StairsBrickDarkImagePath, 10);
			break;
		case MyAPP::Form::Object::BrickColor::grey:
			brick_ptr = std::make_shared<Stairs>("Stairs", MyResourcesFilePath::StairsBrickImagePath, 10);
			break;
		default:
			return brick_ptr;
		}
		brick_ptr->SetPosition(fileinfo.XY);
		brick_ptr->SetVisible(fileinfo.Visibility);
		brick_ptr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::MovingPlatform) {
		brick_ptr = std::make_shared<MovingPlatform>("MovingPlatform");
		brick_ptr->SetPosition(fileinfo.XY);
		brick_ptr->SetVisible(fileinfo.Visibility);
		std::static_pointer_cast<MovingPlatform>(brick_ptr)->up = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Bridge) {
		brick_ptr = std::make_shared<Bridge>("Bridge",  10);
		brick_ptr->SetPosition(fileinfo.XY);
		brick_ptr->SetVisible(fileinfo.Visibility);
		brick_ptr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Axe) {
		brick_ptr = std::make_shared<Axe>("Axe", 10);
		brick_ptr->SetPosition(fileinfo.XY);
		brick_ptr->SetVisible(fileinfo.Visibility);
		brick_ptr->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::ContinueCoinBrick) {
		switch (color) {
		case MyAPP::Form::Object::BrickColor::normal:
			brick_ptr = std::make_shared<ContinueCoinBrick>("ContinueCoinBrick", MyResourcesFilePath::BlockImagePath, color, 10);
			break;
		case MyAPP::Form::Object::BrickColor::dark:
			brick_ptr = std::make_shared<ContinueCoinBrick>("BriContinueCoinBrickck", MyResourcesFilePath::BlockDarkImagePath, color, 10);
			break;
		case MyAPP::Form::Object::BrickColor::grey:
			brick_ptr = std::make_shared<ContinueCoinBrick>("ContinueCoinBrick", MyResourcesFilePath::BlockGreyImagePath, color, 10);
			break;
		default:
			return brick_ptr;
		}
		brick_ptr->SetPosition(fileinfo.XY);
		brick_ptr->SetVisible(fileinfo.Visibility);
		brick_ptr->collisionable = fileinfo.Collisionable;
	}
	return brick_ptr;
}

std::shared_ptr<CharacterPtrVec> MyAPP::Form::Object::MakeObject::make_Characters() noexcept {
	return std::make_shared<CharacterPtrVec>();
}

std::shared_ptr<CoinPtrVec> MyAPP::Form::Object::MakeObject::make_Coins() noexcept {
	return std::make_shared<CoinPtrVec>();
}

std::shared_ptr<TextObjectPtrVec> MyAPP::Form::Object::MakeObject::make_GameText() noexcept {
	auto result = std::make_shared<TextObjectPtrVec>();
	auto texttime = std::make_shared<TextObject>("Timetext", MyAPP::MyResourcesFilePath::MyFontPath, 20 * ((float)WINDOW_HEIGHT / 480), "300", Util::Color::FromName(Util::Colors::WHITE), 100);
	texttime->SetPosition({ GetLeftEdge(texttime), GetTopEdge(texttime) });
	result->push_back(std::move(texttime));

	auto text = std::make_shared<TextObject>("HPText", MyAPP::MyResourcesFilePath::MyFontPath, 20 * ((float)WINDOW_HEIGHT / 480), "HP:3", Util::Color::FromName(Util::Colors::WHITE), 100);
	text->SetPosition({ -GetLeftEdge(text), GetTopEdge(text) });
	result->push_back(std::move(text));

	auto pointtext = std::make_shared<TextObject>("PointText", MyAPP::MyResourcesFilePath::MyFontPath, 20 * ((float)WINDOW_HEIGHT / 480), "Point:0", Util::Color::FromName(Util::Colors::WHITE), 100);
	pointtext->SetPosition({ 0, GetTopEdge(pointtext) });
	result->push_back(std::move(pointtext));

	return result;
}

std::shared_ptr<CharacterPtrVec> MyAPP::Form::Object::MakeObject::make_Enemys_From_File(const std::string& filename, std::shared_ptr<BrickPtrVec>& Bricks) noexcept {
	Fileinfo fileinfo;
	auto enemys = MakeObject::make_Characters();
	std::ifstream inp(filename);
	while (!inp.eof()) {
		fileinfo.XY = { INFINITY, INFINITY };
		fileinfo.GetFileDate(inp);
		if (fileinfo.XY.x == INFINITY || fileinfo.XY.y == INFINITY) {
			break;
		}
		fileinfo.ChangeXY();
		auto ptr = make_EnemysPtr(fileinfo);
		if (ptr) {
			ptr->userdata = Bricks;
			enemys->push_back(std::move(ptr));
		}
	}
	return enemys;
}

CharacterPtr MyAPP::Form::Object::MakeObject::make_EnemysPtr(const Fileinfo& fileinfo) noexcept {
	CharacterPtr enemy = nullptr;
	if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Goomba) {
		enemy = std::make_shared<Goomba>("Goomba", 20);
		enemy->SetPosition(fileinfo.XY);
		enemy->SetVisible(true);
		enemy->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Turtle) {
		enemy = std::make_shared<Turtle>("Turtle", 20);
		enemy->SetPosition(fileinfo.XY);
		enemy->SetVisible(true);
		enemy->collisionable = fileinfo.Collisionable;
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Koopa) {
		enemy = std::make_shared<Koopa>("Koopa", 20);
		enemy->SetPosition(fileinfo.XY);
		enemy->SetVisible(true);
		enemy->collisionable = fileinfo.Collisionable;
	}
	
	return enemy;
}

std::shared_ptr<PropsPtrVec> MyAPP::Form::Object::MakeObject::make_Props() noexcept {
	return std::make_shared<PropsPtrVec>();
}





