#include "Actions.h"

const std::string actionAsStr(Action action){
    if(action == Action::PUSH) return "PUSH";
    else return "RELEASE";
}
