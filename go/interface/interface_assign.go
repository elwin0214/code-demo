package main

import (
	"fmt"
	"unsafe"
)

type C struct {
	i64 int64
	a   int64
	b   int64
	c   int64
	d   int64
}

func assign_interface() {
	var i interface{}
	var a int
	a = 1
	i = a
	fmt.Println(i)
}

func assign_int() {
	var a int
	a = 1
	var i interface{}
	i = a                     //copy
	fmt.Printf("i = %v\n", i) // 1
	a = 2
	fmt.Printf("i = %v\n", i) // 1
}

func assign_struct() {
	c := C{i64: 1}
	fmt.Printf("sizeof(c) = %d\n", unsafe.Sizeof(c)) //40

	var ci interface{}
	ci = c //copy
	v, _ := ci.(C)
	v.i64 = 2
	fmt.Printf("sizeof(ci) = %d\n", unsafe.Sizeof(ci)) //16
	fmt.Printf("c.i64 = %d\n", c.i64)                  //1
}

func main() {
	assign_interface()
	assign_int()
	assign_struct()
}
