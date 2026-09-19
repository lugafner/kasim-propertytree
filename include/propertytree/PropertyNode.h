/**	@file	PropertyNode.h
 *	@author	Lukas Gafner (lugafner)
 *	@bug	None
 */

#pragma once
#include <mutex>
#include <shared_mutex>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

// Forward declarations of child classes
class IntPropertyNode;
class BoolPropertyNode;
class DoublePropertyNode;
class StringPropertyNode;
class EmptyPropertyNode;

/** @brief Parent Node class for property tree
 *  @warning
 *  - @b Circular References: Adding a node as its own ancestor (directly or
 * indirectly) will cause infinite recursion during destruction. Avoid cycles in
 * the tree structure.
 */
class PropertyNode {
public:
  PropertyNode(const std::string& key) : key_(key) {}
  virtual ~PropertyNode();

  /**
   * @brief Returns the child node with the specified key.
   * @param key The key of the child node to retrieve.
   * @return const PropertyNode* Pointer to the child node, or nullptr if not
   * found.
   */
  PropertyNode* getChild(const std::string& key) const;

  /**
   * @brief Returns all direct child nodes of this property node.
   * @return const std::vector<PropertyNode*> Vector containing pointers to
   * all direct children. Returns an empty vector if there are no children.
   */
  std::vector<PropertyNode*> getChildren() const;

  /**
   * @brief Adds a new integer property node as a child.
   * @param key The key for the new property.
   * @param value The integer value to store.
   * @throws std::invalid_argument If the created node pointer is nullptr.
   */
  IntPropertyNode* addIntProperty(const std::string& key, const int value);

  /**
   * @brief Adds a new double property node as a child.
   * @param key The key for the new property.
   * @param value The double value to store.
   * @throws std::invalid_argument If the created node pointer is nullptr.
   */
  DoublePropertyNode* addDoubleProperty(const std::string& key,
                                        const double value);

  /**
   * @brief Adds a new boolean property node as a child.
   * @param key The key for the new property.
   * @param value The boolean value to store.
   * @throws std::invalid_argument If the created node pointer is nullptr.
   */
  BoolPropertyNode* addBoolProperty(const std::string& key, const bool value);

  /**
   * @brief Adds a new string property node as a child.
   * @param key The key for the new property.
   * @param value The string value to store.
   * @throws std::invalid_argument If the created node pointer is nullptr.
   */
  StringPropertyNode* addStringProperty(const std::string& key,
                                        const std::string& value);

  EmptyPropertyNode* addEmptyProperty(const std::string& key);

  /**
   * @brief Get the property value as integer
   * @return int The stored value as integer
   * @throws std::runtime_error If this node does not support integer
   * conversion
   * @note Must be overridden by derived classes that store integer values
   */
  virtual int getInt() const {
    throw std::runtime_error("No conversion for type int available");
  }

  /**
   * @brief Get the property value as double
   * @return double The stored value as double
   * @throws std::runtime_error If this node does not support double
   * conversion
   * @note Must be overridden by derived classes that store double values
   */
  virtual double getDouble() const {
    throw std::runtime_error("No conversion for type double available");
  }

  /**
   * @brief Get the property value as string
   * @return string& The stored value as const string reference
   * @throws std::runtime_error If this node does not support string
   * conversion
   * @note Must be overridden by derived classes that store string values
   */
  virtual const std::string& getString() const {
    throw std::runtime_error("No conversion for type string available");
  }

  /**
   * @brief Get the property value as boolean
   * @return bool The stored value as bool
   * @throws std::runtime_error If this node does not support bool conversion
   * @note Must be overridden by derived classes that store bool values
   */
  virtual bool getBool() const {
    throw std::runtime_error("No conversion for type bool available");
  }

protected:
  const std::string key_; // The key used to get property by path
  std::unordered_map<std::string, PropertyNode*>
      children_; // Map holding the key and the pointer for each child
  mutable std::shared_mutex mutex_; // Mutex (must be mutable)

  /**
   * @brief Validates that a pointer is no nullptr.
   * @tparam T The type of the pointer.
   * @param ptr The pointer to check.
   * @return T* The same pointer if valid.
   * @throws std::invalid_argument If the pointer is nullptr.
   */
  template <typename T> static T* checkPointer(T* ptr) {
    if (ptr == nullptr) {
      throw std::invalid_argument("Nullpointer for Property Node not allowed");
    } else {
      return ptr;
    }
  }
};
