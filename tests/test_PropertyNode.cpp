#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "propertytree/BoolPropertyNode.h"
#include "propertytree/DoublePropertyNode.h"
#include "propertytree/EmptyPropertyNode.h"
#include "propertytree/IntPropertyNode.h"
#include "propertytree/PropertyNode.h"
#include "propertytree/StringPropertyNode.h"

TEST_CASE("PropertyNode: Add child nodes") {
  EmptyPropertyNode emptyNode("emptyNode");

  auto* intNode = emptyNode.addIntProperty("intNode", 3);
  CHECK_EQ(intNode->getInt(), 3);

  auto* doubleNode = emptyNode.addDoubleProperty("doubleNode", 3.5);
  CHECK_EQ(doubleNode->getDouble(), 3.5);

  auto* boolNode = emptyNode.addBoolProperty("boolNode", true);
  CHECK_EQ(boolNode->getBool(), true);

  auto* stringNode = emptyNode.addStringProperty("stringNode", "Hello world");
  CHECK_EQ(stringNode->getString(), "Hello world");
}

TEST_CASE("PropertyNode: Get Child and Children") {
  EmptyPropertyNode emptyNode("root");
  emptyNode.addIntProperty("a", 1);
  emptyNode.addBoolProperty("b", false);
  emptyNode.addStringProperty("c", "test");

  CHECK(emptyNode.getChild("a") != nullptr);
  CHECK_EQ(emptyNode.getChild("a")->getInt(), 1);
  CHECK(emptyNode.getChild("nonexistent") == nullptr);

  auto children = emptyNode.getChildren();
  CHECK(children.size() == 3);
}

TEST_CASE("PropertyNode: Type Conversion") {
  // Int
  IntPropertyNode intNode("int", 42);
  CHECK(intNode.getInt() == 42);
  CHECK(intNode.getDouble() == doctest::Approx(42.0));
  CHECK(intNode.getBool() == true); // 42 != 0 → true
  CHECK_THROWS_AS(intNode.getString(),
                  std::runtime_error); // TODO: Check custom error

  // Bool
  BoolPropertyNode boolNode("bool", true);
  CHECK(boolNode.getBool() == true);
  CHECK(boolNode.getInt() == 1);
  CHECK_THROWS_AS(boolNode.getDouble(),
                  std::runtime_error); // TODO: Check custom error
  CHECK_THROWS_AS(boolNode.getString(),
                  std::runtime_error); // TODO: Check custom error

  // Double
  DoublePropertyNode doubleNode("double", 3.7);
  CHECK(doubleNode.getDouble() == doctest::Approx(3.7));
  CHECK(doubleNode.getInt() == 4); // std::round(3.7) = 4
  CHECK_THROWS_AS(doubleNode.getBool(),
                  std::runtime_error); // TODO: Check custom error
  CHECK_THROWS_AS(doubleNode.getString(),
                  std::runtime_error); // TODO: Check custom error

  // String
  StringPropertyNode strNode("str", "hello");
  CHECK_EQ(strNode.getString(), "hello");
  CHECK(strNode.getBool() == true); // nicht leer → true
  CHECK_THROWS_AS(strNode.getInt(),
                  std::runtime_error); // TODO: Check custom error
  CHECK_THROWS_AS(strNode.getDouble(),
                  std::runtime_error); // TODO: Check custom error

  StringPropertyNode emptyStrNode("empty", "");
  CHECK(emptyStrNode.getBool() == false);
}

TEST_CASE("PropertyNode: Thread Safety") {
  CHECK(true); // TODO: Add Thread safety test
}
