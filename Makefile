SRC=$(wildcard *)
exe:$(SRC)
	rm -rf exe
	g++ *.cc *.h -o exe -w -std=c++11
	./exe
	rm -rf exe

.PHONY:clean

clean:
	rm -rf exe
