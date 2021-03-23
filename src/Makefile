CSRCS     = $(wildcard *.c)
CHDRS     = $(wildcard *.h)
COBJS     = $(addsuffix .o, $(basename $(CSRCS)))

CXX       = gcc

#CFLAGS = -g -Wall
CFLAGS = -O3

BINDIR    = ../bin
TARGET    = $(BINDIR)/$(EXEC)

%.o : %.c
	@echo "> compiling: $<"
	@$(CXX) $(CFLAGS) -c -o $@ $<

top: target
	@echo -n

clean:
	@rm -f $(COBJS)

target: $(TARGET)

$(TARGET): $(COBJS)
	@echo "> building $(EXEC)..."
	@$(CXX) $(CFLAGS) $(COBJS) -o $@ -lm

