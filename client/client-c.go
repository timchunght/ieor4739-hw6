package main

import "github.com/Scalingo/go-workers"

func main() {
	workers.Configure(map[string]string{
		"process": "client1",
		"server":  "localhost:6379",
	})
	m := []interface{}{}
	// b := []byte(`{"Name":"Alice","Body":"Hello","Time":1294706395881547000}`)
	workers.Enqueue("tim_worker", "MyGoWorker", m)
}
