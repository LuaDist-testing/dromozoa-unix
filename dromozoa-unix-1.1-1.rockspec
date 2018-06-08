-- This file was automatically generated for the LuaDist project.

package = "dromozoa-unix"
version = "1.1-1"
-- LuaDist source
source = {
  tag = "1.1-1",
  url = "git://github.com/LuaDist-testing/dromozoa-unix.git"
}
-- Original source
-- source = {
--   url = "https://github.com/dromozoa/dromozoa-unix/archive/v1.1.tar.gz";
--   file = "dromozoa-unix-1.1.tar.gz";
-- }
description = {
  summary = "Lua bindings for UNIX system interface";
  license = "GPL-3";
  homepage = "https://github.com/dromozoa/dromozoa-unix/";
  maintainer = "Tomoyuki Fujimori <moyu@dromozoa.com>";
}
build = {
  type = "make";
  build_variables = {
    CFLAGS = "$(CFLAGS)";
    LIBFLAG = "$(LIBFLAG)";
    LUA_INCDIR = "$(LUA_INCDIR)";
    LUA_LIBDIR = "$(LUA_LIBDIR)";
    LUA = "$(LUA)";
  };
  install_variables = {
    LIBDIR = "$(LIBDIR)";
  };
}