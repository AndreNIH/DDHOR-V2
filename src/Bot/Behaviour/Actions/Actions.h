#pragma once
#include <string>

enum class Action{
    PUSH,
    RELEASE
};


//Input-Action Structure
template<typename PositionT>
struct IAS{
    PositionT location;
    Action action;
};

namespace ActionTools{
    const std::string actionAsStr(Action action);
    Action strAsAction(const std::string& str);
}