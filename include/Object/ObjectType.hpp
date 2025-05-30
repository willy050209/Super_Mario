#pragma once
#ifndef OBJECTTYPE_HPP
#define OBJECTTYPE_HPP
namespace MyAPP::Form::Object {
	/// <summary>
	/// 列舉所有繼承Object的型別
	/// </summary>
	enum class ObjectType {
		Object,
		Character,
		Mario,
		Goomba,
		Turtle,
		ImageObject,
		Brick,
		QuestionBlock,
		HiddenBrick,
		Coin,
		CheckPoint,
		SpinningFireBalls,
		FireBalls,
		TextObject,
		Button,
		EventObject,
		Props,
		FireFlower,
		Mushroom,
		Starman,
		PipeBrick,
		Door,
		Flagpole,
		Floor,
		Stairs,
		MovingPlatform,
		Koopa,
		Bridge,
		Axe,
		FlagFromPole,
		Points,
		ContinueCoinBrick,
		CoinPoints,
		PropBrick
	};

}
#endif // !OBJECTTYPE_HPP
