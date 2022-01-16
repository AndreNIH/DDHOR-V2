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
    void execute() override{
        assert(_actor != nullptr, "Comamnd target cannot be nullptr");
        _actor->holdClick();
    }

    DoPress(std::unique_ptr<PlayerInput>& command){
        _actor = std::move(command);
    }
};

class DoRelease : public BaseCommand{
private:
    std::unique_ptr<PlayerInput> _actor;

public:
    void execute() override{
        assert(_actor != nullptr, "Comamnd target cannot be nullptr");
        _actor->releaseClick();
    }

    DoPress(std::unique_ptr<PlayerInput>& command){
        _actor = std::move(command);
    }
};