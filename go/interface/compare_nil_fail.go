package main

import(
  "fmt"
)
//nil is actually the value of uninitialized variables in Go. 
//The nilvalues for slices, maps, functions, channels, pointers and interfaces are not the same type, and not comparable

func compare_nil_fail(){
  var i int
  fmt.Println("i == nil", i == nil)//cannot convert nil to type int

  var s struct{}
  fmt.Println("s == nil", s == nil)//cannot convert nil to type struct {}

  var str string
  fmt.Println("str == nil", str == nil)//invalid operation: str == nil (mismatched types string and nil)

}

func main(){
  compare_nil_fail() 
}
