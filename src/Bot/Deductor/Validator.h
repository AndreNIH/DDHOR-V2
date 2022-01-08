#pragma once
#include <string>

namespace Validators{
    bool isDDHORV1(const std::string& filename);
    bool isDDHORV2(const std::string& filename);
    
    bool isTASBOT1(const std::string& filename);
    bool isTASBOT2(const std::string& filename);
    
    bool isZBOT(const std::string& filename);
    bool isZBOTF(const std::string& filename);

    bool isYBOT1(const std::string& filename);
    bool isYBOT2(const std::string& filename);

    bool isREPLAY1(const std::string& filename);
    bool isREPLAY2(const std::string& filename);
}