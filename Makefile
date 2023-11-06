# === 各种路径变量 Begin
TOPDIR := $(shell pwd)
export TOPDIR

# TODO 链接脚本路径, 头文件搜索路径 Begin
LDPATH := imx6ull.lds

# 头文件搜索路径
INCDIRS := 	$(TOPDIR)/include \
			$(TOPDIR)/include/led

# mkimage 路径
MKIMAGEPATH := ./tools/mkimage
# NXP 官方提供的DCD信息
IMXIMAGECFGPATH := ./tools/imximage.cfg.cfgtmp
# TODO 链接脚本路径, 头文件搜索路径 End
# === 各种路径变量 End

# === 交叉编译工具链设置 Begin
ARCH  ?= arm
CROSS_COMPILE ?= arm-linux-

ifeq ($(ARCH),x86)
	CC := gcc
else
	CC := $(CROSS_COMPILE)gcc
endif

AS  	= $(CROSS_COMPILE)as
LD  	= $(CROSS_COMPILE)ld
CC      = $(CROSS_COMPILE)gcc
CPP     = $(CC) -E
AR      = $(CROSS_COMPILE)ar
NM	= $(CROSS_COMPILE)nm
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

export AS LD CC CPP AR NM
export STRIP OBJCOPY OBJDUMP

# 函数的作用是将 INCDIRS 变量中的每个元素（目录名）前面加上 -I, 以构建用于指定头文件搜索路径的参数
INCFLAGS := $(patsubst %, -I %, $(INCDIRS))

# == 编译选项 Begin
# 警告选项
# 	-Wall : 开启所有常见的警告提示 \
  	-Wextra : 开启额外的警告提示, 包括一些非常规的代码风格和一些潜在的问题 \
  	-Wpedantic : \
		开启更严格的警告提示, 符合 C 或 C++ 标准的要求, 它会提供更严格的警告, 帮助你编写遵循语言标准的代码 \
  	-Wmissing-prototypes : \
  		用于检查是否存在函数原型的缺失, 函数原型是函数声明的一种形式, 它指定了函数的参数和返回类型, 使用函数原型可以帮助编译器检查函数调用的正确性, 并捕捉潜在的类型不匹配错误 \
  	-Wstrict-prototypes : \
		用于检查函数声明的严格性, 它要求函数声明中必须显式指定参数类型, 不允许使用旧式的省略号参数声明方式
WARNFLAGS := -Wall -Wpedantic -Wextra
WARNFLAGS += -Wmissing-prototypes -Wstrict-prototypes

# 编译优化选项
# 	-O2 : \
		开启优化级别 2, 这是编译器提供的一种中等程度的代码优化级别, 优化级别越高, 编译器会进行更多的优化, 但也可能增加编译时间和可读性
OPTIMIZEFLAGS := -O2

# 字符编码选项
#   -fexec-charset=gbk : 告诉编译器在生成可执行文件时使用 GBK 字符集, 用于支持中文
CHARENCODINGFLAGS := -fexec-charset=gbk

CFLAGS := -fomit-frame-pointer -nostdlib
CFLAGS += $(WARNFLAGS) $(OPTIMIZEFLAGS) $(CHARENCODINGFLAGS) $(INCFLAGS)
# == 编译选项 End

# TODO 链接选项 Beign
# 链接选项
LDFLAGS := -nostdlib -T $(LDPATH)
# TODO 链接选项 End

export CFLAGS LDFLAGS INCFLAGS
# === 交叉编译工具链设置 End

# TODO 被编译的目录, 被编译的当前目录下的文件 Beign
# 编译目标文件的名称
TARGET := led

# 被编译的当前目录下的文件
obj-y +=

# 被编译的子目录
obj-y += src/
# TODO 被编译的目录, 被编译的当前目录下的文件 End

all : start_recursive_build $(TARGET).bin
	@echo $(TARGET) has been built!

start_recursive_build:
	$(MAKE) -C ./ -f $(TOPDIR)/Makefile.build

$(TARGET).bin : built-in.o
	$(CC) $(LDFLAGS) -o $(TARGET).elf built-in.o
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis
	$(MKIMAGEPATH) -n $(IMXIMAGECFGPATH) -T imximage -e 0x80100000 -d $(TARGET).bin $(TARGET).imx
	dd if=/dev/zero of=./tools/1k.bin bs=1024 count=1
	cat ./tools/1k.bin $(TARGET).imx > $(TARGET).img

# === 伪目标 Begin
.PHONY: clean
clean:
# make -C drivers clean
# make -C freertos clean
# rm -f *.o *.elf *.bin
	rm -f $(shell find -name "*.o")
	rm -f $(TARGET).elf $(TARGET).dis $(TARGET).bin $(TARGET).imx $(TARGET).img

.PHONY: distclean
distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.o.d")
	rm -f $(TARGET).elf $(TARGET).dis $(TARGET).bin $(TARGET).imx $(TARGET).img

.PHONY: copy_imx_file
copy_imx_file:
	cp ./$(TARGET).imx /mnt/d/Users/Desktop/

# Print Makefile variables
.PHONY: printvars
printvars:
	@printf "\
	ARCH:          \"$(ARCH)\"\n\
	CROSS_COMPILE: \"$(CROSS_COMPILE)\"\n\
	CC:            \"$(CC)\"\n\
	WARNFLAGS:     \"$(WARNFLAGS)\"\n\
	CFLAGS:        \"$(CFLAGS)\"\n\
	LDFLAGS:       \"$(LDFLAGS)\"\n\
	TARGET:        \"$(TARGET)\"\n"
# === 伪目标 End
