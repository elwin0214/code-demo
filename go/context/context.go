package main

import (
	"context"
	"fmt"
)

func main() {
	ctx, cancel := context.WithCancel(context.Background())
	ch := make(chan string, 1)

	defer func(ch chan string) {
		for i := 0; i < 10; i++ {
			fmt.Println(<-ch)
		}
	}(ch)
	defer cancel()
	for i := 0; i < 10; i++ {
		go func(index int) {
			select {
			case <-ctx.Done():
				ch <- fmt.Sprintf("cancel_%d", index)
				return
			}
		}(i)
	}
}
