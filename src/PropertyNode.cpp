/**	@file	PropertyNode.cpp
 *	@author	Lukas Gafner (lugafner)
 *	@bug	None
 */

#include "propertytree/PropertyNode.h"
#include "propertytree/BoolPropertyNode.h"
#include "propertytree/DoublePropertyNode.h"
#include "propertytree/EmptyPropertyNode.h"
#include "propertytree/IntPropertyNode.h"
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

PropertyNode* PropertyNode::getChild(const std::string& key) const {
  std::shared_lock<std::shared_mutex> lock(mutex_);
  auto child_iterator = children_.find(key);

  // Return nullptr if key is not present
  return (child_iterator == children_.end() ? nullptr : child_iterator->second);
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

IntPropertyNode* PropertyNode::addIntProperty(const std::string& key,
                                              const int value) {
  std::unique_lock<std::shared_mutex> lock(mutex_);
  IntPropertyNode* child = new IntPropertyNode(key, value);
  children_[key] = checkPointer(child);
  return child;
}

DoublePropertyNode* PropertyNode::addDoubleProperty(const std::string& key,
                                                    const double value) {
  std::unique_lock<std::shared_mutex> lock(mutex_);
  DoublePropertyNode* child = new DoublePropertyNode(key, value);
  children_[key] = checkPointer(child);
  return child;
}

BoolPropertyNode* PropertyNode::addBoolProperty(const std::string& key,
                                                const bool value) {
  std::unique_lock<std::shared_mutex> lock(mutex_);
  BoolPropertyNode* child = new BoolPropertyNode(key, value);
  children_[key] = checkPointer(child);
  return child;
}

StringPropertyNode* PropertyNode::addStringProperty(const std::string& key,
                                                    const std::string& value) {
  std::unique_lock<std::shared_mutex> lock(mutex_);
  StringPropertyNode* child = new StringPropertyNode(key, value);
  children_[key] = checkPointer(child);
  return child;
}

EmptyPropertyNode* PropertyNode::addEmptyProperty(const std::string& key) {
  std::unique_lock<std::shared_mutex> lock(mutex_);
  EmptyPropertyNode* child = new EmptyPropertyNode(key);
  children_[key] = checkPointer(child);
  return child;
}
