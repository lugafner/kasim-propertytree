#include "doctest/doctest.h"
#include "propertytree/PropertyTree.h"
#include <string_view>
#include <vector>

class TestPropertyTree {
public:
  static void testSplitPath() {
    PropertyTree tree('.');

    std::string path = "node1.node2";
    std::vector<std::string_view> case1 = tree.splitPath(path);
    REQUIRE(case1.size() == 2);
    REQUIRE_EQ(case1[0], "node1");
    REQUIRE_EQ(case1[1], "node2");

    path = ".node1.node2";
    std::vector<std::string_view> case2 = tree.splitPath(path);
    REQUIRE(case2.size() == 2);
    REQUIRE_EQ(case2[0], "node1");
    REQUIRE_EQ(case2[1], "node2");

    path = "node1.node2.";
    std::vector<std::string_view> case3 = tree.splitPath(path);
    REQUIRE(case3.size() == 2);
    REQUIRE_EQ(case3[0], "node1");
    REQUIRE_EQ(case3[1], "node2");

    path = "node1..node2";
    std::vector<std::string_view> case4 = tree.splitPath(path);
    REQUIRE(case4.size() == 2);
    REQUIRE_EQ(case4[0], "node1");
    REQUIRE_EQ(case4[1], "node2");
  }
};

TEST_CASE("Test split path function") { TestPropertyTree::testSplitPath(); };