#pragma once
#include "../../Engine.h"


NLOHMANN_JSON_SERIALIZE_ENUM(
    BackendType,{
        {BackendType::FRAMES, "frames"},
        {BackendType::XPOS, "x-position"},
        {BackendType::PHYSICS, "physics"}
    }
)