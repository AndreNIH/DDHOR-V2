#pragma once
#include <string>

enum class Action{
    PUSH,
    RELEASE
};


template<typename PositionT>
struct InAct{
    PositionT location;
    Action action;
};

const std::string actionAsStr(Action action);
