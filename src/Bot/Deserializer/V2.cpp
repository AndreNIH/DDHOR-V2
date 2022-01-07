#include "V2.h"
#include <typeinfo>
#include <iostream>
#include "../Behaviour/BotBehavior.h"
#include "../Engine.h"

namespace Deserializer
{
    void V2::deserialize(FrameBehaviour* object)
    {
        std::cout << typeid(this).name() << " is deserializing a " << typeid(object).name() << " object\n";
    }
    
    void V2::deserialize(XBehaviour* object) 
    {
        std::cout << typeid(this).name() << " is deserializing a " << typeid(object).name() << " object\n";
    }

    void V2::deserialize(Bot* object)
    {
        std::cout << typeid(this).name() << " is deserializing a " << typeid(object).name() << " object\n";
    }
}

