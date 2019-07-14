SRC=$(wildcard *)
exe:$(SRC)
	rm -rf exe
	g++ *.cc *.h -o exe -w
	./exe
	rm -rf exe

