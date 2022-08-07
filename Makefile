# 作成者: j19426 西澤駿太郎
TARGET = j19426

SRCDIR = ./src
INCDIR = ./src
OBJDIR = ./obj

SRCS = $(wildcard $(SRCDIR)/*.c)
INCS = $(wildcard $(INCDIR)/*.h)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
DEPS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.d,$(SRCS))

STD = -std=c11

CCFLAGS = -Wall -Wextra -Wpedantic
CC_DEBUG_FLAGS = -g -O0 \
	-Werror \
	-fsanitize=address,undefined,integer,nullability \
	-fno-omit-frame-pointer
CC_RELEASE_FLAGS = -O3 -march=native -flto

LDFLAGS =
LD_DEBUG_FLAGS = -fsanitize=address
LD_RELEASE_FLAGS =

ifeq ($(CC),clang)
	CC_DEBUG_FLAGS += -Weverything
endif

INCPATH = -I./glpng/include

UNAME = $(shell uname)

ifeq ($(UNAME),Darwin)
	CC = clang
	LD = clang
	LIBPATH = -L./glpng/macos
	LIBS = -lglpng -framework OpenGL -framework GLUT
else ifeq ($(UNAME),Linux)
	CC = gcc
	LD = gcc
	LIBS = -lglpng -lglut -lGLU -lGL
else
	CC = i686-pc-cygwin-gcc
	LD = i686-pc-cygwin-gcc
	OBJS += $(OBJDIR)/icon.o
	LIBPATH = -L./glpng/cygwin
	INCPATH += -I/usr/include/opengl
	LIBS = -lglpng -lglut32 -lglu32 -lopengl32
endif

.PHONY: all debug release run clean tar

release: CCFLAGS += $(CC_RELEASE_FLAGS)
release: LDFLAGS += $(LD_RELEASE_FLAGS)
release: all

debug: CCFLAGS += $(CC_DEBUG_FLAGS)
debug: LDFLAGS += $(LD_DEBUG_FLAGS)
debug: all

all: $(TARGET)

fmt: $(SRCS) $(INCS)
	clang-format -i $(SRCS) $(INCS)

lint: $(SRCS) compile_commands.json
	clang-tidy --fix $(SRCS)

clean:
	rm -rf $(TARGET) $(OBJDIR) compile_commands.json

tar: clean
	mkdir $(TARGET)
	cp -r assets/ glpng/ src/ Makefile README.txt $(TARGET)/
	tar -zcvf j19426.tar.gz $(TARGET)/
	rm -rf $(TARGET)/

$(TARGET): $(OBJS)
	@[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
	$(LD) $(LDFLAGS) $(LIBPATH) $(OBJS) -o $@ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	$(CC) $(STD) $(CCFLAGS) $(INCPATH) -o $@ -c -MMD -MP -MF $(@:.o=.d) $<

$(OBJDIR)/icon.o: $(SRCDIR)/icon.rc $(SRCDIR)/icon.ico
	i686-pc-cygwin-windres -i $(SRCDIR)/icon.rc -o $@

compile_commands.json: $(SRCS) Makefile
	bear -- make all

-include $(DEPS)
