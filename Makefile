# Makefile for Student Grade Management System

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = mana
OBJS = main.o student.o fileop.o sort.o print.o calculate.o analysis.o search.o speak.o menu.o

# 默认目标：编译所有源文件生成可执行程序
all: $(TARGET)

# 链接所有目标文件生成可执行程序
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# 编译主程序
main.o: main.c student.h fileop.h sort.h print.h calculate.h analysis.h search.h speak.h menu.h
	$(CC) $(CFLAGS) -c main.c

# 编译学生模块
student.o: student.c student.h
	$(CC) $(CFLAGS) -c student.c

# 编译文件操作模块
fileop.o: fileop.c fileop.h student.h
	$(CC) $(CFLAGS) -c fileop.c

# 编译排序模块
sort.o: sort.c sort.h student.h
	$(CC) $(CFLAGS) -c sort.c

# 编译打印模块
print.o: print.c print.h student.h
	$(CC) $(CFLAGS) -c print.c

# 编译计算模块
calculate.o: calculate.c calculate.h student.h
	$(CC) $(CFLAGS) -c calculate.c

# 编译分析模块
analysis.o: analysis.c analysis.h student.h
	$(CC) $(CFLAGS) -c analysis.c

# 编译搜索模块
search.o: search.c search.h student.h
	$(CC) $(CFLAGS) -c search.c

#编译语音模块
speak.o: speak.c speak.h
	$(CC) $(CFLAGS) -c speak.c

# 编译菜单模块
menu.o: menu.c menu.h
	$(CC) $(CFLAGS) -c menu.c

# 单独编译目标文件（符合要求的方式）
compile_objects:
	$(CC) $(CFLAGS) -c student.c
	$(CC) $(CFLAGS) -c fileop.c
	$(CC) $(CFLAGS) -c sort.c
	$(CC) $(CFLAGS) -c print.c
	$(CC) $(CFLAGS) -c calculate.c
	$(CC) $(CFLAGS) -c analysis.c
	$(CC) $(CFLAGS) -c search.c
	$(CC) $(CFLAGS) -c speak.c
	$(CC) $(CFLAGS) -c menu.c

# 使用目标文件编译主程序
build_with_objects: compile_objects
	$(CC) $(CFLAGS) -o $(TARGET) main.c student.o fileop.o sort.o print.o calculate.o analysis.o search.o speak.o menu.o

# 清理生成的文件
clean:
	rm -f $(TARGET) *.o

# 运行程序
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run compile_objects build_with_objects
