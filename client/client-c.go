package main

import "flag"
import "fmt"
import "github.com/Scalingo/go-workers"

type Message struct {
	Shares  int
	Periods int
	Alpha   float64
	Model   string
}

func main() {

	sharesPtr := flag.Int("shares", -1, "Number of shares you own")
	periodsPtr := flag.Int("periods", -1, "Number of periods you want to run the trading impact model")
	modelPtr := flag.String("model", "", "Type of model you want to run: squareinv or deterministic")
	alphaPtr := flag.Float64("alpha", -1.0, "Alpha you want to run for alpha log in the trading impact model")

	flag.Parse()

	fmt.Println(*sharesPtr)
	fmt.Println(*periodsPtr)
	fmt.Println(*modelPtr)
	fmt.Println(*alphaPtr)

	workers.Configure(map[string]string{
		"process": "client1",
		"server":  "localhost:6379",
	})
	m := []interface{}{Message{Shares: 1000, Periods: 10, Alpha: 0.005, Model: "deterministic"}}
	workers.Enqueue("tim_worker", "TimWorker", m)

}
