package main

import "fmt"
type A struct{

}

func (a *A) f1(){
  fmt.Println("f1")
}

func (a A) g1(){
  fmt.Println("g1")
}

func main(){
  a := A{}
  pa := &a
  a.g1()
  a.f1()
  pa.g1()
  pa.f1()

}