
/**	@file	DoublePropertyNode.h
 *	@author	Lukas Gafner (lugafner)
 *	@bug	None
 */

#pragma once
#include "PropertyNode.h"
#include <cmath>
#include <mutex>
#include <shared_mutex>

/** @brief Double property node implementation
 */
class DoublePropertyNode : public PropertyNode {
public:
  DoublePropertyNode(const std::string& key, const double value)
      : PropertyNode(key), value_(value){};

  void setValue(const double value) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    value_ = value;
  }

  int getInt() const override {
    // Return nearest integer, rounding away from zero in halfway cases
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return static_cast<int>(std::round(value_));
  }

  double getDouble() const override {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return value_;
  }

private:
  double value_;
};