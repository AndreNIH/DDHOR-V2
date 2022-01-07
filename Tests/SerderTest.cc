#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/Bot/Deserializer/Deserialization.h"
#include "../src/Bot/Deserializer/V2.h"
#include "../src/Bot/Deserializer/Legacy.h"

using ::testing::WhenDynamicCastTo;
using ::testing::Ne;
using ::testing::Eq;

TEST(DDHOR, DeserializerCreation) {
  using namespace Deserializer;
  ASSERT_THAT(BotDeserializer::create("legacy").get(),WhenDynamicCastTo<Legacy*>(Ne(nullptr)));
  ASSERT_THAT(BotDeserializer::create("v2").get(),WhenDynamicCastTo<V2*>(Ne(nullptr)));
  
}

TEST(DDHOR, DeserializerCreationFailure) {
  using namespace Deserializer;
  ASSERT_THAT(BotDeserializer::create("tasbot").get(), Eq(nullptr));
  ASSERT_THAT(BotDeserializer::create("xbot").get(), Eq(nullptr));
  ASSERT_THAT(BotDeserializer::create("ybot").get(), Eq(nullptr));
  ASSERT_THAT(BotDeserializer::create("zbot").get(), Eq(nullptr));
}

