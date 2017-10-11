package main

import "fmt"
import "reflect"

type S struct {
}

type S1 S

func (s1 *S1) f() {

}

type SP *S

// 避免指针嵌套下去？一个对象不可能无限的使用取地址符,因为这里调用需要对struct 取地址
//func (sp SP) f() { //invalid receiver type SP (SP is a pointer type)

//}

type SPP *SP

type D struct {
	s *S
}

func (d *D) f() {

}

type A struct{}
type B A

func main() {
	var s S
	var sp SP
	var spp SPP
	fmt.Printf("%s\n", reflect.TypeOf(s).Name())
	fmt.Printf("%s\n", reflect.TypeOf(sp).Name())
	fmt.Printf("%s\n", reflect.TypeOf(spp).Name())

	var a A
	var b B
	fmt.Printf("%b\n", reflect.TypeOf(a) == reflect.TypeOf(b)) //false

}
