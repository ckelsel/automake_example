#指定生成的二进制的名字

bin_PROGRAMS=test


#test依赖的C文件

test_SOURCES=main.c \
	usage.c

if USE_MSW
# Use old style suffix rule instead of the pattern one as automake only
# recognizes this kind of rules.
#
# Also notice that we use .res_o_o extension for the object files obtained by
# compiling resource files, instead of just the usual .o, because we'd have
# conflicts between object file names for foo.cpp and foo.rc otherwise. Due to
# this we have to add the .res_o files manually to LDADD later, but such is life.
.rc.res_o:
	$(AM_V_GEN) $(WINDRES) -I $(top_srcdir) $(WX_CPPFLAGS) -O coff $< $@
endif

#test依赖的库文件
test_LDADD=libmymath.la libmystatic_c.a libmycxx_shared.la \
		   -lgdi32 \
		   -lstdc++ \
		   /usr/i686-w64-mingw32/sys-root/mingw/lib/libmsimg32.a \
		   /usr/i686-w64-mingw32/sys-root/mingw/lib/libole32.a \
		   /usr/i686-w64-mingw32/sys-root/mingw/lib/libwindowscodecs.a

if USE_MSW
test_SOURCES += test.rc
test_LDADD += test.res_o
endif

include_HEADERS=del.h \
	add.h

#生成的共享库libmymath.so

lib_LTLIBRARIES=libmymath.la

#共享库的依赖文件

libmymath_la_SOURCES=add.c


#static cxx library
noinst_LIBRARIES = libmystatic_c.a
libmystatic_c_a_SOURCES = del.c
# NOTE: XXX
# libmystatic_c.a 不需要链接libmycxx_shared.la, 而是由test链接libmycxx_shared.la
# libmystatic_c_a_LIBADD = libmycxx_shared.la


#生成的共享库libmycxx_shared.so
lib_LTLIBRARIES += libmycxx_shared.la

#共享库的依赖文件

libmycxx_shared_la_SOURCES = mycxx.cpp win-png.cpp win-floatbar.cpp
libmycxx_shared_la_LIBADD = -lstdc++
