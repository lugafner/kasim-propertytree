/**	@file	PropertyNode.cpp
 *	@author	Lukas Gafner (lugafner)
 *	@bug	None
 */

#include "propertytree/PropertyNode.h"
#include "propertytree/BoolPropertyNode.h"
#include "propertytree/DoublePropertyNode.h"
#include "propertytree/EmptyPropertyNode.h"
#include "propertytree/IntPropertyNode.h"
#include "propertytree/PropertyTreeExceptions.h"
#include "propertytree/StringPropertyNode.h"
#include <mutex>
#include <shared_mutex>
#include <string>
#include <vector>

// Destruktor
PropertyNode::~PropertyNode() {
  for (const auto& i : children_) {
    delete i.second;
  }
  children_.clear();
}

PropertyNode* PropertyNode::getChild(std::string_view key) const {
  std::shared_lock<std::shared_mutex> lock(mutex_);
  return findChildImpl(key);
}

std::vector<PropertyNode*> PropertyNode::getChildren() const {
  std::shared_lock<std::shared_mutex> lock(mutex_);
  std::vector<PropertyNode*> children;
  children.reserve(children_.size());
  for (const auto& i : children_) {
    children.push_back(i.second);
  }

  return children;
}

int PropertyNode::getInt() const { throw WrongTypeException(key_, getType()); }

bool PropertyNode::getBool() const {
  throw WrongTypeException(key_, getType());
}

double PropertyNode::getDouble() const {
  throw WrongTypeException(key_, getType());
}

const std::string& PropertyNode::getString() const {
  throw WrongTypeException(key_, getType());
}

IntPropertyNode* PropertyNode::addIntProperty(std::string_view key,
                                              const int value) {
  std::unique_lock<std::shared_mutex> lock(mutex_);
  if (findChildImpl(key) != nullptr) {
    throw PropertyAlreadyExistsException(std::string(key));
  }
  IntPropertyNode* child = new IntPropertyNode(std::string(key), value);
  children_[child->getName()] = checkPointer(child);
  return child;
}

DoublePropertyNode* PropertyNode::addDoubleProperty(std::string_view key,
                                                    const double value) {
  std::unique_lock<std::shared_mutex> lock(mutex_);
  if (findChildImpl(key) != nullptr) {
    throw PropertyAlreadyExistsException(std::string(key));
  }
  DoublePropertyNode* child = new DoublePropertyNode(std::string(key), value);
  children_[child->getName()] = checkPointer(child);
  return child;
}

BoolPropertyNode* PropertyNode::addBoolProperty(std::string_view key,
                                                const bool value) {
  std::unique_lock<std::shared_mutex> lock(mutex_);
  if (findChildImpl(key) != nullptr) {
    throw PropertyAlreadyExistsException(std::string(key));
  }
  BoolPropertyNode* child = new BoolPropertyNode(std::string(key), value);
  children_[child->getName()] = checkPointer(child);
  return child;
}

StringPropertyNode* PropertyNode::addStringProperty(std::string_view key,
                                                    const std::string& value) {
  std::unique_lock<std::shared_mutex> lock(mutex_);
  if (findChildImpl(key) != nullptr) {
    throw PropertyAlreadyExistsException(std::string(key));
  }
  StringPropertyNode* child = new StringPropertyNode(std::string(key), value);
  children_[child->getName()] = checkPointer(child);
  return child;
}

EmptyPropertyNode* PropertyNode::addEmptyProperty(std::string_view key) {
  std::unique_lock<std::shared_mutex> lock(mutex_);
  if (findChildImpl(key) != nullptr) {
    throw PropertyAlreadyExistsException(std::string(key));
  }
  EmptyPropertyNode* child = new EmptyPropertyNode(std::string(key));
  children_[child->getName()] = checkPointer(child);
  return child;
}

PropertyNode* PropertyNode::findChildImpl(std::string_view key) const {
  auto child_iterator = children_.find(key);

  // Return nullptr if key is not present
  return (child_iterator == children_.end() ? nullptr : child_iterator->second);
}
