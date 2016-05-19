package main

import (
	"C"
	goworkers "github.com/Scalingo/go-workers"
	"ieor4739-hw6/workers"
)

func main() {

	goworkers.Configure(map[string]string{
		"process": "worker1",
		"server":  "localhost:6379",
	})

	goworkers.Process("tim_worker", workers.TimWorker, 3)
	goworkers.Run()
}
