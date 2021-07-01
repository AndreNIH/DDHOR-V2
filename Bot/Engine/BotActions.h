#pragma once
#include <utility>
#include <vector>
enum class Act {
	PUSH,
	RELEASE
};

//Position X, Act::PUSH | Act::RELEASE
using Action = std::pair<float, Act>;