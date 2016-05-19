package workers

/*
#include "../algo/tim.h"
#cgo LDFLAGS: -L. -ltim
*/
import "C"

import goworkers "github.com/Scalingo/go-workers"

func TimWorker(msg *goworkers.Msg) {

	_ = C.caller()

}

func Tester() {
	_ = C.caller()
}
