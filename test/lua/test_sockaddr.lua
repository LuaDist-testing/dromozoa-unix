-- Copyright (C) 2016 Tomoyuki Fujimori <moyu@dromozoa.com>
--
-- This file is part of dromozoa-unix.
--
-- dromozoa-unix is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- dromozoa-unix is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with dromozoa-unix.  If not, see <http://www.gnu.org/licenses/>.

local unix = require "dromozoa.unix"

assert(not pcall(unix.sockaddr_un, ("0123456789abcdef"):rep(4096)))

local sa = assert(unix.sockaddr_un("test.sock"))
assert(sa:family() == unix.AF_UNIX)
assert(sa:path() == "test.sock")

local sa = assert(unix.sockaddr_un("\0test.sock"))
assert(sa:family() == unix.AF_UNIX)
assert(sa:path() == "\0test.sock")

assert(not pcall(unix.sockaddr_un, ("x"):rep(sa:size() * 2)))