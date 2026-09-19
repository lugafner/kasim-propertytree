
/**	@file	EmptyPropertyNode.h
 *	@author	Lukas Gafner (lugafner)
 *	@bug	None
 */

#pragma once
#include "PropertyNode.h"
#include <mutex>
#include <shared_mutex>

/** @brief Empty property node implementation
           This property node has no value member and the getter methods are not
   implemented
*/
class EmptyPropertyNode : public PropertyNode {
public:
  EmptyPropertyNode(const std::string& key) : PropertyNode(key){};
};