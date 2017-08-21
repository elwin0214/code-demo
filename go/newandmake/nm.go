package main

import (
	"fmt"
	"reflect"
)

func main() {
	a := new([]int)
	b := make([]int, 2)

	fmt.Println("%s\n", reflect.TypeOf(a))
	fmt.Println("%s\n", reflect.TypeOf(b))
	*a = b
	(*a)[0] = 1
}
