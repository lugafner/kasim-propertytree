/** @file   PropertyTreeExceptions.h
 *   @author Lukas Gafner
 *   @bug none
 */

#pragma once
#include "PropertyNode.h"
#include <exception>
#include <format>
#include <string>

/** @brief  Basic propertytree exception class
 */
class PropertyTreeException : public std::exception {
public:
  explicit PropertyTreeException(const std::string& message)
      : message_(message) {}
  const char* what() const noexcept override { return message_.c_str(); }
  virtual ~PropertyTreeException() = default;

protected:
  std::string message_;
};

/** @brief Property not found exception
   Only use this exception, when the property not exists but the path
   is in valid format If the path is malformated use @b InvalidPathException
   instead
 */
class PropertyNotFoundException : public PropertyTreeException {
public:
  explicit PropertyNotFoundException(const std::string& path)
      : PropertyTreeException(std::format("Property not found: {}", path)) {}
};

/** @brief Invalid path exception
 * Use when the path is malformated. If the path is correct, but the property
 * not exists use @b PropertyNotFoundException instead
 */
class InvalidPathException : public PropertyTreeException {
public:
  explicit InvalidPathException(const std::string& path)
      : PropertyTreeException(std::format("Invalid path: {}", path)) {}
};

/** @brief Wrong type exception
 * Use when the called getter or setter functio for the given node is not
 * available
 */
class WrongTypeException : public PropertyTreeException {
public:
  explicit WrongTypeException(const std::string& path,
                              PropertyNode::NodeType nodeType)
      : PropertyTreeException(std::format(
            "Wrong type: Called function not available on node {} with type {}",
            path, PropertyNode::typeAsString(nodeType))) {}
};

/** @brief Property already exists and will not be created
 * Exception thrown when a child is created directly over the Node API. When
 * using the property tree API (i.e. see @b setInt), the value will be overriden
 * without error
 */
class PropertyAlreadyExistsException : public PropertyTreeException {
public:
  explicit PropertyAlreadyExistsException(const std::string& path)
      : PropertyTreeException(
            std::format("Property already exists: {}", path)) {}
};
