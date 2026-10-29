include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG        2d0a9359a60c51affe2a9bebb1be1dca47868151  # v2.5.3
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(doctest)

add_executable(test_propertytree test_PropertyTree.cpp)
target_link_libraries(test_propertytree PRIVATE propertytree doctest::doctest)
add_test(NAME propertytree_tests COMMAND test_propertytree)

add_executable(test_propertynode test_PropertyNode.cpp)
target_link_libraries(test_propertynode PRIVATE propertytree doctest::doctest)
add_test(NAME propertynode_tests COMMAND test_propertynode)