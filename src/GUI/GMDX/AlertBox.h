#pragma once
#include <optional>
#include <string>
#include <gd.h>

namespace gmdx{

    class AlertBox{
    private:
        std::string _title;
        std::string _content;
        std::optional<float> _size;
        std::string _button1="Ok";
        std::optional<std::string> _button2;
        gd::FLAlertLayerProtocol* _delegate=nullptr;
    public:
        void setTitle(const std::string& title);
        void setContent(const std::string& content);
        void setSize(float size);
        void setButtonText(const std::string& b1);
        void setButtonText(const std::string& b1, const std::string& b2);
        void addDelegate(gd::FLAlertLayerProtocol* delegate);
        void show();
    };



}