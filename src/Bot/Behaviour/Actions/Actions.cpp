#include "Actions.h"
#include "../../Deserializer/Deserialization.h"

#include <fmt/format.h>

const std::string actionAsStr(Action action){
    if(action == Action::PUSH) return "PUSH";
    else return "RELEASE";
}


Action strAsAction(const std::string& str) 
{
    if(str == "PUSH") return Action::PUSH;
    else if(str == "RELEASE") return Action::RELEASE;
    else throw Deserializer::DerError{
        fmt::format("Invalid conversion from string to action type \"{}\" has no valid convertion to enum Action", str)
    };
}
