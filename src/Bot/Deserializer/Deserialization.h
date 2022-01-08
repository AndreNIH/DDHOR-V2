#pragma once
#include <string>
#include <memory>

class XBehaviour;
class FrameBehaviour;
class Bot;

namespace Deserializer
{
    class DerError : public std::runtime_error{
    public:
        using _Mybase = std::runtime_error;
        explicit DerError(const std::string& _Message) : _Mybase(_Message.c_str()) {}
        explicit DerError(const char* _Message) : _Mybase(_Message) {}
    };
    
    class BotDeserializer{
    private:
        std::string _targetFile;
        
    public:
        virtual void deserialize(XBehaviour* object)=0;
        virtual void deserialize(FrameBehaviour* object)=0;
        virtual void deserialize(Bot* object)=0;
        
        void setFilename(const std::string& filename){_targetFile = filename;}
        std::string getFilename() const{return _targetFile;}

        static std::unique_ptr<BotDeserializer> create(const std::string& id);
        
    };



    /*class DDHORV2 : public BotDeserializer{
    public:
        void serialize(XBehaviour* object) override;
        void serialize(FrameBehaviour* object) override;
        void deserialize(XBehaviour* object) override;
        void deserialize(FrameBehaviour* object) override;
    public:
        
    };
    
    class YBOT : public BotDeserializer{
    public:
        void serialize(XBehaviour* object) override;
        void serialize(FrameBehaviour* object) override;
        void deserialize(XBehaviour* object) override;
        void deserialize(FrameBehaviour* object) override;

    };
    
    class ZBOT : public BotDeserializer{
    public:
        void serialize(XBehaviour* object) override;
        void serialize(FrameBehaviour* object) override;
        void deserialize(XBehaviour* object) override;
        void deserialize(FrameBehaviour* object) override;
    };
    
    class TASBOT : public BotDeserializer{
    public:
        void serialize(XBehaviour* object) override;
        void serialize(FrameBehaviour* object) override;
        void deserialize(XBehaviour* object) override;
        void deserialize(FrameBehaviour* object) override;
    };*/
} // namespace Deserializer





/*Deserializer::BotDeserializer* findCompatibleSerde(const std::string& filename){
    FileType type = detectFiletype(filename);
    switch(type){
        case kLegacy: return new Deserializer::Legacy;
        case kVersion2: return new Deserializer::DDHORV2;
        case kYBOT : return new Deserializer::YBOT;
        case kZBOT : return new Deserializer::ZBOT;
        default: return nullptr;
    }
}




bool mock(){
    BotBackend* object;
    Deserializer::BotDeserializer* serdeMode=nullptr;
    

    serdeMode->bind(object);
    serdeMode->deserialize("sdfs");
    serdeMode->serialize("dsds");
    

    serdeMode->setTarget("Lmao.txt");
    object->runDeserializer()
    serdeMode->bind(object)
    
    
    
    
    object->serialize()
    object->runDeserializer(serdeMode);
    
    return true;
}

class ASS{
protected:
    int _instance;

protected:

    virtual void doSomethingImpl(int object)=0;
public:

    void doSomething(){
        doSomethingImpl(_instance);
    }

};

class BUTT : public ASS{
    
    void doSomethingImpl(int object) override{
       
    }

};*/