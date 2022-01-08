#pragma once
#include <string>
#include <functional>

class BraceCounter;
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
