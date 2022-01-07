#pragma once
#include <memory>
#include <string>
#include "../Deserializer/Deserialization.h"



std::unique_ptr<Deserializer::BotDeserializer> getCompatibleDeserializer(const std::string file);