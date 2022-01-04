#pragma once
#include "Behaviour/BotBehavior.h"
enum class BotType{};


class FakePlayer{
private:
    BotBehaviour* _behaviour;

public:

    void insertAction(PlayLayer* playLayer){_behaviour->insertAction(playLayer);};
    void rewindActionQueue(PlayLayer* playLayer){_behaviour->rewindActionQueue(playLayer);}
    void reset() {_behaviour->reset();}
    
    void importInputs();
    void exportInputs();

};

