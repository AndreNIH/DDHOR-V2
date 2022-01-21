#pragma once
#include "BaseCommand.h"
#include <cassert>
class PlayerInput{
public:
        void holdClick();
        void releaseClick();
        void setPlayer2();
};

class DoPress : public BaseCommand{
private:
    std::unique_ptr<PlayerInput> _actor;

public:
    void execute() override;
    void bind(std::unique_ptr<PlayerInput>& command);
    CommandID type() const override;
    DoPress(std::unique_ptr<PlayerInput>& command);
    DoPress() = default;
};

class DoRelease : public BaseCommand{
private:
    std::unique_ptr<PlayerInput> _actor;

public:
    void execute() override;
    void bind(std::unique_ptr<PlayerInput>& command);
    CommandID type() const override;
    DoRelease() = default;
    DoRelease(std::unique_ptr<PlayerInput>& command);
};