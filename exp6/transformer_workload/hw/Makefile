TARGET=*.ll

%.ll : %.c %.cpp
	clang -O1 -S -target armv7-pc-none-eabi -emit-llvm -o $@ $<

build : $(TARGET)

clean:
	rm -rf *.ll
