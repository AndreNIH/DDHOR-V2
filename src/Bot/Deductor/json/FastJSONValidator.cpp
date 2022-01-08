#include "FastJSONValidator.h"
#include <spdlog/spdlog.h>
#include <fstream>

class BraceCounter{
private:
    std::unordered_map<char, int> _template;
    std::unordered_map<char, int> _matches;
    std::string _pattern;
public: 
    void buildPattern(const std::string& pattern);
    void feed(char character);
    bool matchesPattern() const;
    std::string getPattern() const {return _pattern;}
};

void BraceCounter::buildPattern(const std::string& pattern){
    _template.clear();
    _matches.clear();
    for(char character : pattern)_template[character]++;
    for(auto& entry : _template) _matches[entry.first] = 0;
}

void BraceCounter::feed(char character){
    if(matchesPattern()) return;
    auto foundIt = _matches.find(character);
    if(foundIt != _matches.end()) foundIt->second++;
}

bool BraceCounter::matchesPattern() const{
    return _template == _matches;
}



void JSONLazyValidator::setQualifierPattern(const std::string& pattern) 
{
    _braces.buildPattern(pattern);
}

void JSONLazyValidator::setStringCorrection(const std::string& fix) 
{
    _fix = fix;
}

void JSONLazyValidator::setValidator(const std::function<ValidatorT>& validator) 
{
    _validator = validator;
}

bool JSONLazyValidator::validateFile(const std::string &filename) 
{
    if(_validator == nullptr) {
        spdlog::warn("Attempted to validate JSON wihtout a bound validator function");
        return false;
    }

    std::ifstream file(filename);
    std::string strPart;
    char character;
    while(file >> character){
        strPart += character;
        _braces.feed(character);
        if(_braces.matchesPattern())
            return _validator(strPart + _fix);
    
    spdlog::debug("File {} did not match the pattern '{}'", filename, _braces.getPattern());
    return false;
}
