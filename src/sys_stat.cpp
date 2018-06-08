// Copyright (C) 2016 Tomoyuki Fujimori <moyu@dromozoa.com>
//
// This file is part of dromozoa-unix.
//
// dromozoa-unix is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// dromozoa-unix is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with dromozoa-unix.  If not, see <http://www.gnu.org/licenses/>.

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#include <sys/stat.h>

#include "dromozoa/bind.hpp"

#include "sys_stat.hpp"

namespace dromozoa {
  using bind::function;

  namespace {
    int impl_umask(lua_State* L) {
      lua_pushinteger(L, umask(luaL_checkinteger(L, 1)));
      return 1;
    }
  }

  void initialize_sys_stat(lua_State* L) {
    function<impl_umask>::set_field(L, "umask");
  }
}