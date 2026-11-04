#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "propertytree/DoublePropertyNode.h"
#include "propertytree/IntPropertyNode.h"
#include "propertytree/PropertyTree.h"
#include "propertytree/PropertyTreeExceptions.h"

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
  tree.setInt("root.path", 5);

  // Wrong path
  CHECK_THROWS_AS(tree.getInt("root.value"), PropertyNotFoundException);

  // Get Wrong type
  tree.setString("text", "hello");
  CHECK_THROWS_AS(tree.getInt("text"), WrongTypeException);

  // Set wrong type on existing node
  tree.setInt("existingInt", 4);
  CHECK_THROWS_AS(tree.setBool("existingInt", false), WrongTypeException);

  // Empty path
  CHECK_THROWS_AS(tree.setInt("", 3), InvalidPathException);
  CHECK_THROWS_AS(tree.getInt(""), InvalidPathException);

  // Leading delimiter
  CHECK_THROWS_AS(tree.setInt(".a.b", 3), InvalidPathException);
  CHECK_THROWS_AS(tree.getInt(".a.b"), InvalidPathException);

  // Trailing delimiter
  CHECK_THROWS_AS(tree.setInt("x.y.", 4), InvalidPathException);
  tree.setInt("x.y", 4);
  CHECK_THROWS_AS(tree.getInt("x.y."), InvalidPathException);

  // Double delimiter not allowed
  CHECK_THROWS_AS(tree.setInt("f..g", 6), InvalidPathException);
  tree.setInt("f.g", 6);
  CHECK_THROWS_AS(tree.getInt("f..g"), InvalidPathException);
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
