CC := g++ #compiler

SRCDIR := src
BUILDDIR := build
TARGET := bin/GMTK-Editor

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g # -Wall
LIB := -lSDL2 -lSDL2_image
INC := -I include

$(TARGET): $(OBJECTS)
		@echo "Linking..."
		@echo "$(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
		@mkdir -p $(BUILDDIR)
		@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ @<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
		@echo "Cleaning..."
		@echo "$(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

