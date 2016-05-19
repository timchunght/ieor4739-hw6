package workers

/*
#include "../algo/tim.h"
#cgo LDFLAGS: -L. -ltim
*/
import "C"

import goworkers "github.com/Scalingo/go-workers"
import "encoding/json"
import "fmt"

// not dry
type Message struct {
	Shares  int
	Periods int
	Alpha   float64
	Model   string
}

func TimWorker(msg *goworkers.Msg) {

	args := msg.Args().ToJson()
	mArr := []Message{}

	err := json.Unmarshal([]byte(args), &mArr)
	if err != nil {
		fmt.Println("unmarshal error")
	} else {
		m := mArr[0]
		fmt.Println(m)
		// _ = C.caller()

		// printf("hello, tim\n");
		// caller();
		// int N = 1000;
		// int T = 10;
		// double alpha = 0.001;
		// N := 1000
		// T := 10
		// alpha := 0.001
		// modelType := "deterministic"
		C.tim_orchestrator(C.int(m.Shares), C.int(m.Periods), C.double(m.Alpha), C.CString(m.Model))
	}

}

func Tester() {
	_ = C.caller()
}
