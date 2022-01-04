#include "V2.h"
#include <typeinfo>
#include <iostream>


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
}

