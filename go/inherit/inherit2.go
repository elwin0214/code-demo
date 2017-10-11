package main

import (
	"bytes"
)

type A struct{}

func (a *A) f() {

}

type B A

func (b *B) g() {

}

type N1Buffer bytes.Buffer

// add a new method in Buffer
func (nb *N1Buffer) find(b byte) int {
	buffer := (*bytes.Buffer)(nb)
	buf := buffer.Bytes()
	for i := 0; i < len(buf); i++ {
		if buf[i] == b {
			return i
		}
	}
	return -1
}

func NewNBuffer() *N1Buffer {
	return (*N1Buffer)(bytes.NewBuffer(make([]byte, 0, 12)))
}

type C struct {
}
type N2Buffer struct {
	//bytes.Buffer
	C
}

func NewN2Buffer() *N2Buffer {
	//buffer := bytes.NewBuffer(make([]byte, 0, 12))
	//return N2Buffer{bytes.Buffer:*buffer}

	return &N2Buffer{C: C{}}
}

func main() {
	NewNBuffer()
}
