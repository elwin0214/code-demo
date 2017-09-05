package main

import (
	"fmt"
)

type People interface {
	Show()
}

type Student struct{}

func (stu *Student) Show() {

}

func live() People {
	var stu *Student
	return stu
}

type Pa struct{}

func (pa Pa) Show(){}

type Pb struct{}
func (pb *Pb) Show(){}

func newPa() People{
  return &Pa{}
}

func newPb() People{
  return &Pb{}
}
func main() {
	if live() == nil {
		fmt.Println("A")
	} else {
		fmt.Println("B") // B
	}

  var p1 Pa
  var p2 *Pa
  //fmt.Println("boy1 == nil ", boy1 == nil) //cannot convert nil to type Boy
  fmt.Println("p1 == nil ", &p1 == nil) //false
  fmt.Println("p2 == nil ", p2 == nil) //true

  //p1 := createBoy()
    
}
