all:
	gofmt -e -s -w .
	go vet .
	gcc -std=c99 -g -fPIC -c -o algo/tim.o algo/tim.c
	gcc -std=c99 -g -fPIC -shared -o libtim.so algo/tim.o
	cp libtim.so workers/
	LD_LIBRARY_PATH=. go build -o worker
	go build client-cli/client.go

clean:
	rm -rf bin/*
	rm *.so
	rm -rf workers/*.so
	rm algo/*.o
	rm worker
	rm client