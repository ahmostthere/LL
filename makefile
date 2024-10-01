

CC := g++
C11 := -std=c++11
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGET := bin/main

 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))


CFLAGS := -g -Wall
# LIB := -L lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
LIB := -L lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
INC := -I include -I assets


$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@$(CC) $(C11) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $(OBJECTS))
	@$(CC) $(C11) $(CFLAGS) $(INC) -c -o $@ $<
# $@ -- full name of current target 
# $$ -- name of first dependency

c: cl
cl: clean
clean:
	@echo " Cleaning..."; 
	@$(RM) -r $(BUILDDIR) $(TARGET) $(TSTTARG)

.PHONY: clean