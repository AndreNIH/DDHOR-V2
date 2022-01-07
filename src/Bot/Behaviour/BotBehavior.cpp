#include <iostream>
#include "BotBehavior.h"
#include "../Deserializer/Deserialization.h"
using std::cout;
// XBehaviour Class
//=================================================

void XBehaviour::insertAction(PlayLayer* playLayer) 
{
}

void XBehaviour::rewindActionQueue(PlayLayer* playLayer) 
{
        
}

void XBehaviour::runDeserializer(Deserializer::BotDeserializer* serializaitionObject) 
{
    serializaitionObject->deserialize(this);   
}

nlohmann::json XBehaviour::runSerializer(Serializer::BotSerializer* serializaitionObject)
{
    return nlohmann::json();
}




// FrameBehaviour Class
//=================================================

void FrameBehaviour::insertAction(PlayLayer* playLayer) 
{
    
}

void FrameBehaviour::rewindActionQueue(PlayLayer* playLayer) 
{
    
}


void FrameBehaviour::runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) 
{
    deserializaitionObject->deserialize(this);    
}

nlohmann::json FrameBehaviour::runSerializer(Serializer::BotSerializer* serializaitionObject)
{
    return nlohmann::json();
}
