#pragma once
#ifndef USERTYPE_HPP
#define USERTYPE_HPP

#include <memory>
#include <vector>
#include <tuple>
#include "incallobj.hpp"


typedef std::tuple<std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Character>>>,
	std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Brick>>>,
	std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Props::Props>>>>
	GameObjectTuple;

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

typedef std::shared_ptr<MyAPP::Form::Object::Character>
	CharacterPtr;

typedef std::shared_ptr<MyAPP::Form::Object::Mario>
	MarioPtr;

typedef std::shared_ptr<MyAPP::Form::Object::ImageObject>
	ImageObjectPtr;

typedef std::shared_ptr<MyAPP::Form::Object::SpinningFireBalls>
	SpinningFireBallsPtr;

typedef std::shared_ptr<MyAPP::Form::Object::FireBalls>
	FireBallsPtr;

typedef std::vector <FireBallsPtr>
	FireBallsPtrVec;

typedef std::vector<BrickPtr>
	BrickPtrVec;

typedef std::pair<ImageObjectPtr, MarioPtr>
	BackgroundMarioPair;

#endif // !USERTYPE_HPP