package main

import "fmt"



type List []int   
type List2 *[]int 
func newList() List{
  l:= make([]int, 0, 8)
  return l
}
//error func (l List2) append(i int){ 

func (l *List) append(i int){  //
  *l = append(*l, i)
}

func share(){
  s1 := make([]int,0,2)
  s2  := s1
  s2 = append(s2, 1)

  fmt.Println("len(s1)", len(s1))  //0
  fmt.Println("len(s2)", len(s2))  //1
}

func share_pointer(){
  lst := newList()
  l1 := &lst
  l2 := l1
  l1.append(1)
  fmt.Println("len(l1)", len(*l1))  //1
  fmt.Println("len(l2)", len(*l2))  //1
}
func main(){
  share()
  share_pointer()
}