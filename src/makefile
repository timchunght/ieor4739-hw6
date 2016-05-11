all:
	gofmt -e -s -w .
	go vet .
	$(CC) -g -fPIC -c -o algo/tim.o algo/tim.c
	$(CC) -g -fPIC -shared -o libtim.so algo/tim.o
	LD_LIBRARY_PATH=. go build -o worker

clean:
	rm -rf bin/*
	rm *.so
	rm algo/*.o
	rm worker