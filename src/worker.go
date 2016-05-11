package main

/*
#include "algo/tim.h"
#include <stdlib.h>       // for free()
#cgo LDFLAGS: -L. -ltim
*/
import "C"

// import "fmt"

func main() {
	_ = C.sample()
	// fmt.Println(int(C.bridge_int_func(f)))
	// Output: 42
}
