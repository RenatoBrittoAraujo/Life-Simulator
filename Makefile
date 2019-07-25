IDIR =include
CC=g++ -std=c++17
CFLAGS=-I$(IDIR) -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

ODIR=obj
LDIR=lib

SRCR=src

_DEPS = $(notdir $(shell find $(IDIR) -name '*.hpp'))
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
SOURCES = $(notdir $(shell find $(SRCR) -name '*.cpp'))
_OBJ = $(SOURCES:%.cpp=%.o)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm program

run {flags} :
	./program ${flags}

runv:
	./program -v

runf:
	./program -f

runc:
	./program -c