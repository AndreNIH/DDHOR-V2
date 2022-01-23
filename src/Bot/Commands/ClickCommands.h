#pragma once
#include "BaseCommand.h"

class DoPress : public BaseCommand{
private:
    bool _isP2=false;
public:
    void execute() override;
    void setP2(bool p2);
    CommandID type() const override;
    DoPress(bool p2);
};

class DoRelease : public BaseCommand{
private:
    bool _isP2=false;
public:
    void execute() override;
    void setP2(bool p2);
    CommandID type() const override;
    DoRelease(bool p2);
};