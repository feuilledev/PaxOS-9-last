# How to add your own functions in the Lua API

- Copy the example.hpp and example.cpp add your code
- After go to lua_file.hpp and add

```cpp
#include "your_file.hpp"
```

- After go to lua_file.cpp and add

```cpp
#include "your_file.hpp"
```

- After go to lua_file.cpp and add

```cpp
lua.new_usertype<LuaExample>(
        "Example",
        sol::base_classes,
        sol::bases<LuaWidget>(),

        "example",
        &LuaExample::example
    );
```