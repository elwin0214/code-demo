package main

import(
  "fmt"
)
//nil is actually the value of uninitialized variables in Go. 
//The nilvalues for slices, maps, functions, channels, pointers and interfaces are not the same type, and not comparable

type S struct{
  str string 
  p *int
} 

func compare_nil_succ(){
  var p *struct{}
  fmt.Println("p == nil", p == nil) // true

  var m map[int]int
  fmt.Println("m == nil", m == nil) // true

  m = make(map[int]int)
  fmt.Println("m == nil", m == nil) // false
  //fmt.Println("m == nil", m[1] == nil) // cannot convert nil to type int

  var i interface{}
  fmt.Println("i == nil", i == nil) // true

  m2 := make(map[int]*int)
  fmt.Println("m2[i] == nil", m2[1] == nil) // true

  var s S
  //fmt.Println("s.str == nil", s.str == nil) //  (mismatched types string and nil)
  fmt.Println("s.p == nil", s.p == nil) // true
}

func main(){
  compare_nil_succ()
}