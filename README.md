# PropertyTree

A lightweight, header-driven C++17 property tree library for hierarchical key-value storage. Properties are organized in a tree structure and accessed via dot-separated paths (configurable delimiter). Each leaf node stores a typed value (`int`, `double`, `string`, `bool`); intermediate nodes are empty containers.

## Features

- Path-based access with configurable delimiter (e.g. `"player.health"`)
- Typed leaf nodes: `int`, `double`, `std::string`, `bool`
- Automatic creation of intermediate nodes when setting a property
- Thread-safe node-level access via `std::shared_mutex`
- No external dependencies beyond the C++ standard library

## Usage

```cpp
#include <propertytree/PropertyTree.h>

int main() {
  PropertyTree tree('.');

  // Set properties — intermediate nodes are created automatically
  tree.setInt("player.health", 100);
  tree.setDouble("physics.gravity", 9.81);
  tree.setString("player.name", "Alice");
  tree.setBool("debug.enabled", true);

  // Read values by path
  int health = tree.getInt("player.health");         // 100
  double gravity = tree.getDouble("physics.gravity"); // 9.81

  // Setters return a typed node pointer for direct access in hot loops
  IntPropertyNode* node = tree.setInt("player.score", 0);
  node->setValue(42);  // direct access, no path lookup
}
```

## API Overview

| Method | Description |
|--------|-------------|
| `PropertyTree(char delimiter)` | Construct a tree with the given path delimiter |
| `setInt/setDouble/setString/setBool(path, value)` | Create or update a typed property, returns the node pointer |
| `getInt/getDouble/getString/getBool(path)` | Read a typed value by path, throws if path or type is missing |
| `PropertyNode::getChild(key)` | Navigate the tree directly from a node pointer |
| `PropertyNode::getChildren()` | Get all direct children of a node |

## Building

Build with CMake presets (requires [Ninja](https://ninja-build.org/)):

```bash
cmake --preset linux-debug
cmake --build build/debug
```

For a release build, use the `linux-release` preset and the `build/release` directory.
On Windows under MSYS2 UCRT64, use the `msys2-ucrt64-debug` / `msys2-ucrt64-release` presets.

## Testing

Tests use [doctest](https://github.com/doctest/doctest) v2.5.3, fetched automatically via CMake `FetchContent` during configuration (network required on first configure).

```bash
cmake --preset linux-debug
cmake --build build/debug
ctest --test-dir build/debug
```

## Integration

Use CMake `FetchContent` to consume this library from another project:

```cmake
include(FetchContent)
FetchContent_Declare(
    propertytree
    GIT_REPOSITORY https://github.com/lugafner/kasim-propertytree.git
    GIT_TAG        v0.1.0
)
FetchContent_MakeAvailable(propertytree)

target_link_libraries(my_app PRIVATE propertytree)
```

## License

GNU GENERAL PUBLIC LICENSE Version 3
