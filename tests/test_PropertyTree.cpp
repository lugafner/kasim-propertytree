#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "propertytree/DoublePropertyNode.h"
#include "propertytree/IntPropertyNode.h"
#include "propertytree/PropertyTree.h"

TEST_CASE("PropertyTree: Set Values with Paths") {
  PropertyTree tree('.');

  // Simple path
  auto* intNode = tree.setInt("basis", 800);
  CHECK(intNode != nullptr);
  CHECK(intNode->getInt() == 800);

  // Extended path with empty node
  auto* doubleNode = tree.setDouble("basis.empty.value", 600.5);
  CHECK(doubleNode != nullptr);
  CHECK(doubleNode->getDouble() == doctest::Approx(600.5));

  // Overwrite value
  auto* updatedNode = tree.setInt("basis", 1024);
  CHECK(updatedNode->getInt() == 1024);
}

TEST_CASE("PropertyTree: Get Values with Paths") {
  PropertyTree tree('.');
  tree.setInt("a.b.c", 42);
  tree.setBool("x.y", true);
  tree.setString("root.name", "test");

  CHECK(tree.getInt("a.b.c") == 42);
  CHECK(tree.getBool("x.y") == true);
  CHECK_EQ(tree.getString("root.name"), "test");
}

TEST_CASE("PropertyTree: Error Handling") {
  PropertyTree tree('.');
  tree.setInt("root", 5);

  // Wrong path
  CHECK_THROWS_AS(tree.getInt("root.path"),
                  std::runtime_error); // TODO: Custom error

  // Wrong type
  tree.setString("text", "hello");
  CHECK_THROWS_AS(tree.getInt("text"),
                  std::runtime_error); // TODO: Custom error

  // Empty path
  CHECK_THROWS_AS(tree.getInt(""), std::runtime_error); // TODO: Custom error
}

TEST_CASE("PropertyTree: Delimiter") {
  PropertyTree tree1('.');
  // Delimiter '.'
  tree1.setInt("a.b.c", 1);
  CHECK(tree1.getInt("a.b.c") == 1);

  // Delimiter '/'
  PropertyTree tree2('/');
  tree2.setBool("a/b/c", false);
  CHECK(tree2.getBool("a/b/c") == false);
}

TEST_CASE("PropertyTree: Edge case incomplete path") {
  PropertyTree tree('.');

  // Leading delimiter
  tree.setInt(".a.b", 3);
  CHECK(tree.getInt("a.b") == 3);

  // Trailing delimiter
  tree.setInt("x.y.", 4);
  CHECK(tree.getInt("x.y") == 4);

  // Leading and trailing delimiter
  tree.setInt(".o.p.", 5);
  CHECK(tree.getInt("o.p") == 5);

  // Ignore empty delimiter
  tree.setInt("f..g", 6);
  CHECK(tree.getInt("f.g") == 6);
}