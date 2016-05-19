package main

import (
	"C"
	goworkers "github.com/Scalingo/go-workers"
	"ieor-hw6/src/workers"
)

func main() {
	workers.Tester()
	goworkers.Configure(map[string]string{
		"process": "worker1",
		"server":  "localhost:6379",
	})

	goworkers.Process("tim_worker", workers.TimWorker, 10)
	goworkers.Run()
}
