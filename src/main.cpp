#include <iostream>
#include <variant>
#include <vector>
#include <string> 
#include "Bot/Engine.h"
//Mock PlayLayer
/*struct PlayLayer{
    float xpos;
    int elapsedFrames;
};


struct SerdeObject{
    virtual void serialize(const std::string& outFilename)=0;
    virtual void deserialize(const std::string& inFilename)=0;
};

struct LegacySerde : public SerdeObject{
        
};

struct NewSerde{

};



class BotPolicy{    
private:

public:
    virtual void insertAction(Action action)=0;
    virtual void rewindActionQueue(PlayLayer* playLayer)=0;    
    virtual void reset()=0;

    
    //virtual bool shouldDispatch(){};
};


class FramesPolicy : public BotPolicy{
private:
    std::vector<int> _frames;
public:
    void insertAction(Action action) override{
        std::cout << "FramesPolicy insertAction called\n";
        _frames.push_back(playLayer->elapsedFrames);
    }
    
    void rewindActionQueue(PlayLayer* playLayer) override{
        std::cout << "FramesPolicy rewind called (mock, popback)\n";
        _frames.pop_back();
    }
    
    void reset() override{
        std::cout << "FramesPolicy reset called\n";
        _frames.clear();
    }
};

class XPosPolicy : public BotPolicy{
private:
    std::vector<float> _xpositions;

public:
    void insertAction(Action action) override{
        std::cout << "XPosPolicy insertAction called\n";
        _xpositions.push_back(playLayer->xpos);
    }
    
    void rewindActionQueue(PlayLayer* playLayer) override{
        std::cout << "XPosPolicy rewind called (mock, popback)\n";
        _xpositions.pop_back();
    }
    
    void reset() override{
        std::cout << "XPosPolicy reset called\n";
        _xpositions.clear();
    }
};
*/


int main(int, char**) {
    /*XPosBackend xposBot;
    FrameBackend frameBot;*/
    /*CommandBackend* xposBot = new XPosBackend;
    CommandBackend* frameBot = new FrameBackend;
    Bot* bot = new Bot;
    Deserializer::BotDeserializer* deserializerObject = new Deserializer::Legacy;
    
    
    deserializerObject->setFilename("Macro.ddhor");
    xposBot->runDeserializer(deserializerObject);
    frameBot->runDeserializer(deserializerObject);
    bot->importMacro("test");*/
    /*delete deserializerObject;
    deserializerObject = new Deserializer::V2;
    
    deserializerObject->setFilename("Macro.ddhor");
    xposBot->runDeserializer(deserializerObject);
    frameBot->runDeserializer(deserializerObject);*/
    Bot bot;
    bot.importMacro("v1test.ddhor");
    bot.importMacro("v2test.ddhor");
    
}
