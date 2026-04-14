#pragma once

namespace MyAPP::Form::Object {

enum class MarioState {
    UP,
    MOVE,
    DOWN,
    CROUCH,
    DIED,
    STAND,
    Invincible,
};

enum class MarioType {
    Mario,
    SuperMario,
    FieryMario,
    InvincibleMario,
    InvincibleSuperMario,
    InvincibleFieryMario
};

} // namespace MyAPP::Form::Object
