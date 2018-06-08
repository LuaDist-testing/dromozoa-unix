-- This file was automatically generated for the LuaDist project.

package = "dromozoa-unix"
version = "1.47-1"
-- LuaDist source
source = {
  tag = "1.47-1",
  url = "git://github.com/LuaDist-testing/dromozoa-unix.git"
}
-- Original source
-- source = {
--   url = "https://github.com/dromozoa/dromozoa-unix/releases/download/v1.47/dromozoa-unix-1.47.tar.gz";
-- }
description = {
  summary = "Lua bindings for UNIX system interface";
  license = "GPL-3";
  homepage = "https://github.com/dromozoa/dromozoa-unix/";
  maintainer = "Tomoyuki Fujimori <moyu@dromozoa.com>";
}
build = {
  type = "command";
  build_command = [[env PATH="$(LUA_BINDIR):$PATH" CPPFLAGS="$CPPFLAGS -I$(LUA_INCDIR)" CXXFLAGS="$CXXFLAGS -Wall -W -Wno-missing-field-initializers $(CFLAGS)" LDFLAGS="$LDFLAGS -L$(LUA_LIBDIR)" LUA="$(LUA)" ./configure --prefix="$(PREFIX)" && make]];
  install_command = [[make luadir="$(LUADIR)" luaexecdir="$(LIBDIR)/dromozoa" install]];
}