#include "doctest/doctest.h"
#include "propertytree/BoolPropertyNode.h"
#include "propertytree/DoublePropertyNode.h"
#include "propertytree/EmptyPropertyNode.h"
#include "propertytree/IntPropertyNode.h"
#include "propertytree/PropertyNode.h"
#include "propertytree/StringPropertyNode.h"

class TestPropertyNode {
public:
  static void testGetType() {
    IntPropertyNode* intProperty = new IntPropertyNode("intProperty", 5);
    REQUIRE(intProperty->getType() == PropertyNode::NodeType::Int);

    BoolPropertyNode* boolProperty = new BoolPropertyNode("boolProperty", true);
    REQUIRE(boolProperty->getType() == PropertyNode::NodeType::Bool);

    StringPropertyNode* stringProperty =
        new StringPropertyNode("stringProperty", "Hello");
    REQUIRE(stringProperty->getType() == PropertyNode::NodeType::String);

    DoublePropertyNode* doubleProperty =
        new DoublePropertyNode("doubleProperty", 3.5);
    REQUIRE(doubleProperty->getType() == PropertyNode::NodeType::Double);

    EmptyPropertyNode* emptyProperty = new EmptyPropertyNode("emptyProperty");
    REQUIRE(emptyProperty->getType() == PropertyNode::NodeType::Empty);
  }
};

TEST_CASE("Test get node type") { TestPropertyNode::testGetType(); };
