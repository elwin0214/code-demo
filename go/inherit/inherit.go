package main

import "fmt"

type A struct{}

func (p *A) Show1() {
	fmt.Println("A.Show1()")
	p.Show2()
}
func (p *A) Show2() {
	fmt.Println("A.show2()")
}

type B struct {
	A
}

func (t *B) Show2() {
	fmt.Println("B.show2()")
}


func main() {
	t := B{}
	t.Show1() // A.show1  A.show2
  t.Show2() //B.show2()
}
