#指定生成的二进制的名字

bin_PROGRAMS=test


#test依赖的C文件

test_SOURCES=main.c \
	usage.c


#test依赖的库文件

test_LDADD=libmymath.la

include_HEADERS=del.h \
	add.h


#生成的共享库libmymath.so

lib_LTLIBRARIES=libmymath.la

#共享库的依赖文件

libmymath_la_SOURCES=add.c \
	del.c
