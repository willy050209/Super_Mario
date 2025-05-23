#pragma once
#ifndef OBJECTTYPE_HPP
#define OBJECTTYPE_HPP
namespace MyAPP {
	namespace Form {
		namespace Object {
			/// <summary>
			/// �C�|�Ҧ��~��Object�����O
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
				Points
			};
		}
	}
}
#endif // !OBJECTTYPE_HPP
