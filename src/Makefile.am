#指定生成的二进制的名字

bin_PROGRAMS=test


#test依赖的C文件

test_SOURCES=main.c \
	usage.c


#test依赖的库文件

test_LDADD=libmymath.la libmystatic_c.a libmycxx_shared.la

include_HEADERS=del.h \
	add.h

#生成的共享库libmymath.so

lib_LTLIBRARIES=libmymath.la

#共享库的依赖文件

libmymath_la_SOURCES=add.c


#static cxx library
noinst_LIBRARIES = libmystatic_c.a
libmystatic_c_a_SOURCES = del.c
# libmystatic_c_a_LIBADD = libmycxx_shared.la


#生成的共享库libmycxx_shared.so
lib_LTLIBRARIES += libmycxx_shared.la

#共享库的依赖文件

libmycxx_shared_la_SOURCES = mycxx.cpp
libmycxx_shared_la_LIBADD = -lstdc++
