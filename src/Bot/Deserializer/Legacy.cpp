#include "Legacy.h"
#include <typeinfo>
#include <iostream>
#include "../Engine.h"

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

    void Legacy::deserialize(Bot* object){
        
    }

    
}

