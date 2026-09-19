
#include "propertytree/PropertyTree.h"
#include <string>
#include <string_view>

PropertyTree::PropertyTree(char delimiter) : path_delimiter_(delimiter) {
  // Create root node with the key root
  rootNode_ = new EmptyPropertyNode("root");
}

PropertyTree::~PropertyTree() {
  delete rootNode_;
  rootNode_ = nullptr;
}

int PropertyTree::getInt(const std::string& path) const {
  const PropertyNode* node = getNodeByPath(path);
  if (node == nullptr) {
    throw std::runtime_error("No property under path " + path);
  }
  return node->getInt();
}

double PropertyTree::getDouble(const std::string& path) const {
  const PropertyNode* node = getNodeByPath(path);
  if (node == nullptr) {
    throw std::runtime_error("No property under path " + path);
  }
  return node->getDouble();
}

const std::string& PropertyTree::getString(const std::string& path) const {
  const PropertyNode* node = getNodeByPath(path);
  if (node == nullptr) {
    throw std::runtime_error("No property under path " + path);
  }
  return node->getString();
}

bool PropertyTree::getBool(const std::string& path) const {
  const PropertyNode* node = getNodeByPath(path);
  if (node == nullptr) {
    throw std::runtime_error("No property under path " + path);
  }
  return node->getBool();
}

IntPropertyNode* PropertyTree::setInt(const std::string& path,
                                      const int value) {
  std::vector<std::string_view> path_parts = splitPath(path);
  PropertyNode* parent_node = createNodeTree(path_parts);
  return parent_node->addIntProperty(std::string(path_parts.back()), value);
}

BoolPropertyNode* PropertyTree::setBool(const std::string& path,
                                        const bool value) {
  std::vector<std::string_view> path_parts = splitPath(path);
  PropertyNode* parent_node = createNodeTree(path_parts);
  return parent_node->addBoolProperty(std::string(path_parts.back()), value);
}

DoublePropertyNode* PropertyTree::setDouble(const std::string& path,
                                            const double value) {
  std::vector<std::string_view> path_parts = splitPath(path);
  PropertyNode* parent_node = createNodeTree(path_parts);
  return parent_node->addDoubleProperty(std::string(path_parts.back()), value);
}

StringPropertyNode* PropertyTree::setString(const std::string& path,
                                            const std::string& value) {
  std::vector<std::string_view> path_parts = splitPath(path);
  PropertyNode* parent_node = createNodeTree(path_parts);
  return parent_node->addStringProperty(std::string(path_parts.back()), value);
}

const PropertyNode*
PropertyTree::getNodeByPathImpl(const std::string& path) const {
  std::string_view view = path;
  size_t start = 0;
  size_t end = view.find(path_delimiter_);

  const PropertyNode* current_node = rootNode_;
  while (end != std::string_view::npos) {
    current_node = current_node->getChild(std::string(view.substr(start, end)));
    start = end + 1;
    end = view.find(path_delimiter_, start);
  }
  return current_node->getChild(std::string(view.substr(start)));
}

const PropertyNode* PropertyTree::getNodeByPath(const std::string& path) const {
  return getNodeByPathImpl(path);
}

PropertyNode* PropertyTree::getNodeByPath(const std::string& path) {
  return const_cast<PropertyNode*>(getNodeByPathImpl(path));
}

const std::vector<std::string_view>
PropertyTree::splitPath(const std::string& path) {
  std::string_view view = path;
  size_t start = 0;
  size_t end = view.find(path_delimiter_);

  std::vector<std::string_view> path_parts;
  while (end != std::string_view::npos) {
    path_parts.push_back(view.substr(start, end));
    start = end + 1;
    end = view.find(path_delimiter_, start);
  }

  path_parts.push_back(view.substr(start, end));
  return path_parts;
}

PropertyNode*
PropertyTree::createNodeTree(const std::vector<std::string_view>& path_parts) {
  PropertyNode* last_node = rootNode_;
  PropertyNode* current_node = last_node;
  std::string current_key;
  for (size_t i = 0; i < path_parts.size() - 1; i++) {
    current_key = std::string(path_parts[i]);
    current_node = last_node->getChild(current_key);
    if (current_node == nullptr) {
      current_node = last_node->addEmptyProperty(current_key);
    }
    last_node = current_node;
  }

  return current_node;
}