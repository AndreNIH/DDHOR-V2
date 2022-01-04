#include "Legacy.h"
#include <typeinfo>
#include <iostream>

namespace Deserializer
{
    void Legacy::deserialize(FrameBehaviour* object)
    {
        std::cout << typeid(this).name() << " is deserializing a " << typeid(object).name() << " object\n";
    }
    
    void Legacy::deserialize(XBehaviour* object) 
    {
        std::cout << typeid(this).name() << " is deserializing a " << typeid(object).name() << " object\n";
    }

}

