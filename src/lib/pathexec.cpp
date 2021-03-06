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

#include <errno.h>
#include <unistd.h>

#include <dromozoa/pathexec.hpp>

extern char** environ;

namespace dromozoa {
  namespace {
    inline char* copy(char* p, char c) {
      *p = c;
      return p + 1;
    }

    inline char* copy(char* p1, const char* p2, size_t n) {
      for (size_t i = 0; i < n; ++i) {
        p1[i] = p2[i];
      }
      return p1 + n;
    }
  }

  size_t pathexec_buffer_size(const char* path, const char* const* argv) {
    const char* command = argv[0];
    size_t i = 0;
    for (; command[i] != '\0'; ++i) {
      if (command[i] == '/') {
        return 0;
      }
    }
    size_t command_size = i;

    if (!path) {
      return 0;
    }

    size_t path_size = 1;
    size_t j = 0;
    for (size_t i = 0; ; ++i) {
      char c = path[i];
      if (c == ':' || c == '\0') {
        size_t k = i - j;
        if (path_size < k) {
          path_size = k;
        }
        if (c == '\0') {
          break;
        }
        j = i + 1;
      }
    }
    return path_size + command_size + 2;
  }

  int pathexec(const char* path, const char* const* argv, const char* const* envp, char* buffer, size_t size) {
    if (!envp) {
      envp = environ;
    }

    const char* command = argv[0];
    size_t i = 0;
    for (; command[i] != '\0'; ++i) {
      if (command[i] == '/') {
        execve(command, const_cast<char**>(argv), const_cast<char**>(envp));
        return -1;
      }
    }
    size_t command_size = i;

    if (!path) {
      errno = ENOENT;
      return -1;
    }

    int code = ENOENT;
    size_t j = 0;
    for (size_t i = 0; ; ++i) {
      char c = path[i];
      if (c == ':' || c == '\0') {
        size_t path_size = i > j ? i - j : 1;
        if (path_size + 1 + command_size < size) {
          char* p = buffer;
          if (i > j) {
            p = copy(p, path + j, path_size);
          } else {
            p = copy(p, '.');
          }
          p = copy(p, '/');
          p = copy(p, command, command_size);
          copy(p, '\0');
          execve(buffer, const_cast<char**>(argv), const_cast<char**>(envp));
          switch (errno) {
            case ENOENT:
              break;
            case EACCES:
            case EISDIR:
            case EPERM:
              code = errno;
              break;
            default:
              return -1;
          }
        }
        if (c == '\0') {
          break;
        }
        j = i + 1;
      }
    }
    errno = code;
    return -1;
  }
}
