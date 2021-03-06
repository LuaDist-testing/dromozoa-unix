// Copyright (C) 2016,2018 Tomoyuki Fujimori <moyu@dromozoa.com>
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

#include <unistd.h>

#include <vector>

#include "common.hpp"

namespace dromozoa {
  namespace {
    void impl_read(lua_State* L) {
      int fd = check_fd(L, 1);
      size_t size = luaX_check_integer<size_t>(L, 2);
      std::vector<char> buffer(size);
      ssize_t result = read(fd, &buffer[0], buffer.size());
      if (result == -1) {
        push_error(L);
      } else {
        luaX_push(L, luaX_string_reference(&buffer[0], result));
      }
    }

    void impl_write(lua_State* L) {
      luaX_string_reference buffer = luaX_check_string(L, 2);
      size_t i = luaX_opt_range_i(L, 3, buffer.size());
      size_t j = luaX_opt_range_j(L, 4, buffer.size());
      if (j < i) {
        j = i;
      }
      ssize_t result = write(check_fd(L, 1), buffer.data() + i, j - i);
      if (result == -1) {
        push_error(L);
      } else {
        luaX_push(L, result);
      }
    }

    void impl_fsync(lua_State* L) {
      if (fsync(check_fd(L, 1)) == -1) {
        push_error(L);
      } else {
        luaX_push_success(L);
      }
    }
  }

  void initialize_fd_unistd(lua_State* L) {
    luaX_set_field(L, -1, "read", impl_read);
    luaX_set_field(L, -1, "write", impl_write);
    luaX_set_field(L, -1, "fsync", impl_fsync);
  }
}
