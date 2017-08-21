package main

import (
	"context"
	"fmt"
)

func main() {
	ctx, cancel := context.WithCancel(context.Background())
	ch := make(chan string, 1)
	defer func(ch chan string) {
		fmt.Println(<-ch)
	}(ch)
	defer cancel()
	go func() {
		select {
		case <-ctx.Done():
			ch <- "cancel"
			return
		}
	}()
}
