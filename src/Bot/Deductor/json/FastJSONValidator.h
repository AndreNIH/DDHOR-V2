#pragma once
#include <string>
#include <functional>
#include <unordered_map>

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

class JSONLazyValidator{
private:
    using ValidatorT= bool(const std::string&);
    std::string _fix;
    std::function<ValidatorT> _validator;
    BraceCounter _braces;

public:
    void setQualifierPattern(const std::string& pattern);
    void setStringCorrection(const std::string& fix);
    void setValidator(const std::function<ValidatorT>& validator);
    bool validateFile(const std::string &filename);
};
