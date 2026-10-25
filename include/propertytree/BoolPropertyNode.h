
/**	@file	BoolPropertyNode.h
 *	@author	Lukas Gafner (lugafner)
 *	@bug	None
 */

#pragma once
#include "PropertyNode.h"
#include <mutex>
#include <shared_mutex>

/** @brief Boolean property node implementation
 */
class BoolPropertyNode : public PropertyNode {
public:
  BoolPropertyNode(const std::string& key, const bool value)
      : PropertyNode(key), value_(value){};

  void setValue(const bool value) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    value_ = value;
  }

  int getInt() const override {
    // Return boolean as integer (true = 1, false = 0)
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return (value_ ? 1 : 0);
  }

  bool getBool() const override {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return value_;
  }

  NodeType getType() const override { return NodeType::Bool; }

private:
  bool value_;
};