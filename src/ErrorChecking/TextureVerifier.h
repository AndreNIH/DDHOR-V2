#pragma once
#include "ChainedChecks.h"

class TextureVerifier : public ITest{
private:
    const std::string _textureName;
public:
    bool runTest() override;    
    TextureVerifier(const std::string& testName, const std::string& textureName) 
        : ITest(testName), _textureName(textureName){}
};

class MultiTextureVerifier : public ITest{
private:
    const std::string _baseTexture;
    const int _minNumber;
    const int _maxNumber;

public:
    bool runTest() override;
    MultiTextureVerifier(const std::string& testName, const std::string& baseTexture, int minimum, int maximum) : 
        ITest(testName), 
        _baseTexture(baseTexture), 
        _minNumber(minimum), 
        _maxNumber(maximum)
        {}
};