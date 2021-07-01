#pragma once

namespace GameController{
    void setSpeed(float multiplier);
    void setPaused(bool paused);

    float getSpeed();
    bool getPaused();

    void suspend();
    void commit();
}

