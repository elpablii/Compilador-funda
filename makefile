TARGET = compilador
FLEX_OUT = scanner.cpp
BISON_OUT = parser.cpp parser.hpp

all: $(TARGET)

$(TARGET): $(FLEX_OUT) $(BISON_OUT)
	g++ -o $@ $(FLEX_OUT) $(BISON_OUT) -lm

$(FLEX_OUT): scanner.l
	flex -o $(FLEX_OUT) scanner.l

$(BISON_OUT): parser.y
	bison -d -o parser.cpp parser.y

clean:
	rm -f $(FLEX_OUT) $(BISON_OUT) $(TARGET)