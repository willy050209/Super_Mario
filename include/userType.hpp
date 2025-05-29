#pragma once
#ifndef USERTYPE_HPP
#define USERTYPE_HPP

#include <memory>
#include <utility>
#include "incallobj.hpp"



typedef std::unique_ptr<const MyAPP::Form::Object::Brick>
	ConstUniqueBrickPtr;

typedef std::shared_ptr<MyAPP::Form::Object::Object>
	ObjectPtr;

typedef std::shared_ptr<MyAPP::Form::Object::Character>
	CharacterPtr;

typedef std::shared_ptr<MyAPP::Form::Object::Brick>
	BrickPtr;

typedef std::shared_ptr<MyAPP::Form::Object::Props::Props>
	PropsPtr;

typedef std::shared_ptr<MyAPP::Form::Object::Mario>
	MarioPtr;

typedef std::shared_ptr<MyAPP::Form::Object::ImageObject>
	ImageObjectPtr;

typedef std::shared_ptr<MyAPP::Form::Object::SpinningFireBalls>
	SpinningFireBallsPtr;

typedef std::shared_ptr<MyAPP::Form::Object::FireBalls>
	FireBallsPtr;

typedef std::shared_ptr<MyAPP::Form::Object::TextObject>
	TextObjectPtr;

typedef std::shared_ptr<MyAPP::Form::Object::Coin>
	CoinPtr;

typedef std::shared_ptr<MyAPP::Form::Object::CheckPoint>
	CheckPointPtr;

typedef std::shared_ptr<MyAPP::Form::Object::QuestionBlock>
	QuestionBlockPtr;

typedef std::shared_ptr<MyAPP::Form::Object::EventObject>
	EventObjectPtr;

typedef std::shared_ptr<MyAPP::Form::Object::Button>
	ButtonPtr;

typedef std::vector <FireBallsPtr>
	FireBallsPtrVec;

typedef std::vector<BrickPtr>
	BrickPtrVec;

typedef std::vector<CharacterPtr>
	CharacterPtrVec;

typedef std::vector<PropsPtr>
	PropsPtrVec;

typedef std::vector<CoinPtr>
	CoinPtrVec;

typedef std::vector<TextObjectPtr>
	TextObjectPtrVec;

typedef std::vector<CheckPointPtr>
	CheckPointPtrVec;

typedef std::vector<QuestionBlockPtr>
	QuestionBlockPtrVec;

typedef std::vector<EventObjectPtr>
	EventObjectPtrVec;

typedef std::vector<ObjectPtr>
	ObjectPtrVec;

typedef std::vector<ImageObjectPtr>
	ImageObjectPtrVec;

typedef std::vector<ButtonPtr>
	ButtonPtrVec;

typedef std::pair<ImageObjectPtr, MarioPtr>
	BackgroundMarioPair;

typedef std::tuple<
	std::shared_ptr<CharacterPtrVec>,
	std::shared_ptr<BrickPtrVec>,
	std::shared_ptr<PropsPtrVec>>
	GameObjectTuple;

typedef std::tuple<int, std::vector<bool>>
	SleepAllEventUserDataType;
#endif // !USERTYPE_HPP