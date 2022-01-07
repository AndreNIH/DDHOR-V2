#pragma once
#include <string>

namespace Validators{
    bool isLegacyDDHOR(const std::string& filename);
    bool isDDHORV2(const std::string& filename);
    bool isTASBOT1(const std::string& filename);
    bool isTASBOT2(const std::string& filename);
    bool isZBOT(const std::string& filename);
    bool isYBOT(const std::string& filename);
}