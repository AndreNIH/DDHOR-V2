#pragma once

namespace Deserializer{
    class V1;
    class V2;
}

#define EXTEND_DESERIALIZER_ACCESS \
    friend class Deserializer::V1; \
    friend class Deserializer::V2;