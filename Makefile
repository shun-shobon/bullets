# 作成者: j19426 西澤駿太郎
TARGET = cubeworld

BINDIR = ./bin
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


UNAME = $(shell uname)

ifeq ($(UNAME),Darwin)
	CC = clang
	LD = clang
	LIBS = -framework OpenGL -framework GLUT
else ifeq ($(UNAME),Linux)
	CC = gcc
	LD = gcc
	LIBS = -lglut -lGLU -lGL
else
	CC = i686-pc-cygwin-gcc
	LD = i686-pc-cygwin-gcc
	OBJS += $(OBJDIR)/icon.o
	INCPATH = -I/usr/include/opengl
	LIBS = -lglut32 -lglu32 -lopengl32
endif

.PHONY: all debug release run clean

release: CCFLAGS += $(CC_RELEASE_FLAGS)
release: LDFLAGS += $(LD_RELEASE_FLAGS)
release: all

debug: CCFLAGS += $(CC_DEBUG_FLAGS)
debug: LDFLAGS += $(LD_DEBUG_FLAGS)
debug: all

all: $(BINDIR)/$(TARGET)

fmt: $(SRCS) $(INCS)
	clang-format -i $(SRCS) $(INCS)

lint: $(SRCS) compile_commands.json
	clang-tidy $(SRCS)

clean:
	rm -rf $(BINDIR) $(OBJDIR) compile_commands.json

$(BINDIR)/$(TARGET): $(OBJS)
	@[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
	$(LD) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	$(CC) $(STD) $(CCFLAGS) -o $@ -c -MMD -MP -MF $(@:.o=.d) $<

$(OBJDIR)/icon.o: $(SRCDIR)/icon.rc $(SRCDIR)/icon.ico
	i686-pc-cygwin-windres -i $(SRCDIR)/icon.rc -o $@

compile_commands.json: $(SRCS) Makefile
	bear -- make all

-include $(DEPS)
