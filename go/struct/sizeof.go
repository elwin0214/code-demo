package main

import "fmt"
import "unsafe"

type A struct {
	i   int
	i64 int64
	b   bool
}
type B struct {
	i64 int64
	i   int
	b   bool
}

type C struct {
	i64 int64
}

func main() {
	fmt.Printf("sizeof(struct{}{}) = %d\n", unsafe.Sizeof(struct{}{})) //0

	var s string
	fmt.Printf("sizeof(string) = %d\n", unsafe.Sizeof(s)) //16
	s = "123456789123456789"
	fmt.Printf("sizeof(string) = %d\n", unsafe.Sizeof(s)) //16

	var i interface{}
	fmt.Printf("sizeof(interface{}) = %d\n", unsafe.Sizeof(i)) //16

	var m map[int]int
	fmt.Printf("sizeof(map[int]int) = %d\n", unsafe.Sizeof(m))   //8
	fmt.Printf("sizeof(&map[int]int) = %d\n", unsafe.Sizeof(&m)) //8

	var slice []int
	fmt.Printf("sizeof([]int) = %d\n", unsafe.Sizeof(slice)) //24

	var a A
	fmt.Printf("sizeof(A) = %d\n", unsafe.Sizeof(a)) //24

	var b B
	fmt.Printf("sizeof(B) = %d\n", unsafe.Sizeof(b)) //24

	c := C{i64: 1}
	fmt.Printf("sizeof(c) = %d\n", unsafe.Sizeof(c)) //8

	var ci interface{}
	ci = c //copy

	v, _ := ci.(C)
	v.i64 = 2
	fmt.Printf("sizeof(ci) = %d\n", unsafe.Sizeof(ci)) //16
	fmt.Printf("c.i64 = %d\n", c.i64)                  //1

}
