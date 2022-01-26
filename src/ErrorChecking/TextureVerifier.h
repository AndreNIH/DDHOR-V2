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