// A function named : example() that return "Hello World"

#ifndef LUA_EXAMPLE_MODULE
#define LUA_EXAMPLE_MODULE

#include "lua_widget.hpp"

class LuaExample : public LuaWidget
{
  public:
    std::string example() const;
};

#endif