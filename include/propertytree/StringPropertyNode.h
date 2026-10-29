
/**	@file	StringPropertyNode.h
 *	@author	Lukas Gafner (lugafner)
 *	@bug	None
 */

#pragma once
#include "PropertyNode.h"
#include <mutex>
#include <shared_mutex>

/** @brief Integer property node implementation
 */
class StringPropertyNode : public PropertyNode {
public:
  StringPropertyNode(const std::string& key, const std::string& value)
      : PropertyNode(key), value_(value){};

  void setValue(const std::string& value) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    value_ = value;
  }

  const std::string& getString() const override { return value_; }

  bool getBool() const override {
    // Return false if string is empty and true for all non empty strings
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return (value_.empty() ? false : true);
  }

  NodeType getType() const override { return NodeType::String; }

private:
  std::string value_;
};