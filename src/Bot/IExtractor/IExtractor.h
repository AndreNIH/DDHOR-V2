#pragma once
#include <type_traits>


class IFrames{};
class IXPosition{};

template<typename T>
typename std::enable_if<std::is_same_v<T, IFrames>, int>::type extractPosition(){

}

template<typename T>
typename std::enable_if<std::is_same_v<T, IXPosition>, int>::type extractPosition(){
    
}
