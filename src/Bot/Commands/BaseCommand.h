#pragma once
#include <memory>

enum class CommandID{
    CLICK,
    RELEASE,
    PLAYSOUND,
    CHANGEFPS,
    SETPLAYERATTR
};

class BaseCommand{
public:
    virtual void execute()=0;
    virtual CommandID type() const=0;
};
