package workers

/*
#include "../algo/tim.h"
#cgo LDFLAGS: -L. -ltim
*/
import "C"

import goworkers "github.com/Scalingo/go-workers"

func TimWorker(msg *goworkers.Msg) {

	fmt.Println(msg[0])
	// _ = C.caller()

	// printf("hello, tim\n");
	// caller();
	// int N = 1000;
	// int T = 10;
	// double alpha = 0.001;
	N := 1000
	T := 10
	alpha := 0.001
	modelType := "deterministic"
	C.tim_orchestrator(C.int(N), C.int(T), C.double(alpha), C.CString(modelType))

}

func Tester() {
	_ = C.caller()
}
