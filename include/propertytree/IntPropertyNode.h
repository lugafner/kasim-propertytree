
/**	@file	IntPropertyNode.h
 *	@author	Lukas Gafner (lugafner)
 *	@bug	None
 */

#pragma once
#include "PropertyNode.h"
#include <mutex>
#include <shared_mutex>

/** @brief Integer property node implementation
 */
class IntPropertyNode : public PropertyNode {
public:
  IntPropertyNode(const std::string& key, const int value)
      : PropertyNode(key), value_(value){};

  void setValue(const int value) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    value_ = value;
  }

  int getInt() const override {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return value_;
  }

  bool getBool() const override {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return static_cast<bool>(value_);
  }

  double getDouble() const override {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return static_cast<double>(value_);
  }

  NodeType getType() const override { return NodeType::Int; }

private:
  int value_;
};