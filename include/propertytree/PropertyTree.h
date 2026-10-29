/** @file   PropertyTree.h
 *   @author Lukas Gafner
 *   @bug none
 */

#pragma once
#include "PropertyNode.h"
#include <string>

/** @brief  Property Tree class holding all the nodes
            and provides the getter and setter functions on tree level
*/
class PropertyTree {
public:
  /**
   * @brief Constructs a PropertyTree with the given path delimiter.
   * @param delimiter The character used to separate path segments.
   */
  PropertyTree(char delimiter);

  /**
   * @brief Destructor. Deletes root property
   */
  ~PropertyTree();

  /**
   * @brief Returns the integer value of the property at the given path.
   * @param path The path to the property, using the configured delimiter.
   * @return int The stored integer value.
   * @throws std::runtime_error If no property exists under the path or the
   * node does not support integer conversion.
   */
  int getInt(const std::string& path) const;

  /**
   * @brief Returns the double value of the property at the given path.
   * @param path The path to the property, using the configured delimiter.
   * @return double The stored double value.
   * @throws std::runtime_error If no property exists under the path or the
   * node does not support double conversion.
   */
  double getDouble(const std::string& path) const;

  /**
   * @brief Returns the string value of the property at the given path.
   * @param path The path to the property, using the configured delimiter.
   * @return const std::string& Const reference to the stored string value.
   * @throws std::runtime_error If no property exists under the path or the
   * node does not support string conversion.
   */
  const std::string& getString(const std::string& path) const;

  /**
   * @brief Returns the boolean value of the property at the given path.
   * @param path The path to the property, using the configured delimiter.
   * @return bool The stored boolean value.
   * @throws std::runtime_error If no property exists under the path or the
   * node does not support bool conversion.
   */
  bool getBool(const std::string& path) const;

  /**
   * @brief Creates or updates an integer property at the given path, creating
   * intermediate nodes as needed.
   * @param path The path to the property, using the configured delimiter.
   * @param value The integer value to store.
   * @return IntPropertyNode* Pointer to the created or updated integer node.
   * @throws std::invalid_argument If the created node pointer is nullptr.
   */
  IntPropertyNode* setInt(const std::string& path, const int value);

  /**
   * @brief Creates or updates a double property at the given path, creating
   * intermediate nodes as needed.
   * @param path The path to the property, using the configured delimiter.
   * @param value The double value to store.
   * @return DoublePropertyNode* Pointer to the created or updated double node.
   * @throws std::invalid_argument If the created node pointer is nullptr.
   */
  DoublePropertyNode* setDouble(const std::string& path, const double value);

  /**
   * @brief Creates or updates a string property at the given path, creating
   * intermediate nodes as needed.
   * @param path The path to the property, using the configured delimiter.
   * @param value The string value to store.
   * @return StringPropertyNode* Pointer to the created or updated string node.
   * @throws std::invalid_argument If the created node pointer is nullptr.
   */
  StringPropertyNode* setString(const std::string& path,
                                const std::string& value);

  /**
   * @brief Creates or updates a boolean property at the given path, creating
   * intermediate nodes as needed.
   * @param path The path to the property, using the configured delimiter.
   * @param value The boolean value to store.
   * @return BoolPropertyNode* Pointer to the created or updated boolean node.
   * @throws std::invalid_argument If the created node pointer is nullptr.
   */
  BoolPropertyNode* setBool(const std::string& path, const bool value);

private:
  PropertyNode* rootNode_;
  const char path_delimiter_ = '.';

  /**
   * @brief Resolves a path to its corresponding node by traversing the tree
   * from the root.
   * @param path The path to resolve, using the configured delimiter.
   * @return const PropertyNode* Pointer to the node at the path, or nullptr if
   * any segment does not exist.
   */
  const PropertyNode* getNodeByPathImpl(const std::string& path) const;

  /**
   * @brief Resolves a path to its corresponding node, allowing modification of
   * the returned node.
   * @param path The path to resolve, using the configured delimiter.
   * @return PropertyNode* Pointer to the node at the path, or nullptr if any
   * segment does not exist.
   */
  PropertyNode* getNodeByPath(const std::string& path);

  /**
   * @brief Resolves a path to its corresponding node in read-only mode.
   * @param path The path to resolve, using the configured delimiter.
   * @return const PropertyNode* Pointer to the node at the path, or nullptr if
   * any segment does not exist.
   */
  const PropertyNode* getNodeByPath(const std::string& path) const;

  /**
   * @brief Splits a path into its individual segments using the configured
   * delimiter.
   * @param path The path to split.
   * @return const std::vector<std::string_view> Vector of path segments as
   * string views into the input string.
   * @note Returned views are valid only while the input string is alive.
   */
  const std::vector<std::string_view> splitPath(const std::string& path);

  /**
   * @brief Ensures all intermediate nodes for a path exist, creating empty
   * nodes where needed.
   * @param path_parts The path segments, where the last segment is the leaf
   * and all preceding segments are traversed or created.
   * @return PropertyNode* Pointer to the parent node of the leaf segment, where
   * the leaf property should be added.
   */
  PropertyNode* createNodeTree(const std::vector<std::string_view>& path_parts);
};