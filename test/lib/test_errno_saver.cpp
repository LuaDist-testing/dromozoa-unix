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

#include <assert.h>
#include <errno.h>

#include <dromozoa/errno_saver.hpp>

int main(int, char*[]) {
  errno = ENOENT;
  assert(errno == ENOENT);
  {
    dromozoa::errno_saver save_errno;
    assert(errno == ENOENT);
    errno = EINTR;
    assert(errno == EINTR);
  }
  assert(errno == ENOENT);
  return 0;
}
