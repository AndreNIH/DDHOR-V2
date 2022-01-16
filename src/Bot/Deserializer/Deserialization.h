#pragma once
#include <string>
#include <memory>
#include <stdexcept>

class XPosBackend;
class FrameBackend;
class Bot;

namespace Deserializer
{
    class DerError : public std::runtime_error{
    public:
        using _Mybase = std::runtime_error;
        explicit DerError(const std::string& _Message) : _Mybase(_Message.c_str()) {}
        explicit DerError(const char* _Message) : _Mybase(_Message) {}
    };
    
    class UnsupportedConversion:  public std::runtime_error{
    public:
        using _Mybase = std::runtime_error;
        explicit UnsupportedConversion(const std::string& _Message) : _Mybase(_Message.c_str()) {}
        explicit UnsupportedConversion(const char* _Message) : _Mybase(_Message) {}
    };

    class BotDeserializer{
    private:
        std::string _targetFile;
        
    public:
        virtual void deserialize(XPosBackend* object)=0;
        virtual void deserialize(FrameBackend* object)=0;
        virtual void deserialize(Bot* object)=0;
        
        void setFilename(const std::string& filename){_targetFile = filename;}
        std::string getFilename() const{return _targetFile;}

        static std::unique_ptr<BotDeserializer> create(const std::string& id);
        
    };



    /*class DDHORV2 : public BotDeserializer{
    public:
        void serialize(XPosBackend* object) override;
        void serialize(FrameBackend* object) override;
        void deserialize(XPosBackend* object) override;
        void deserialize(FrameBackend* object) override;
    public:
        
    };
    
    class YBOT : public BotDeserializer{
    public:
        void serialize(XPosBackend* object) override;
        void serialize(FrameBackend* object) override;
        void deserialize(XPosBackend* object) override;
        void deserialize(FrameBackend* object) override;

    };
    
    class ZBOT : public BotDeserializer{
    public:
        void serialize(XPosBackend* object) override;
        void serialize(FrameBackend* object) override;
        void deserialize(XPosBackend* object) override;
        void deserialize(FrameBackend* object) override;
    };
    
    class TASBOT : public BotDeserializer{
    public:
        void serialize(XPosBackend* object) override;
        void serialize(FrameBackend* object) override;
        void deserialize(XPosBackend* object) override;
        void deserialize(FrameBackend* object) override;
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
    CommandExecuter* object;
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