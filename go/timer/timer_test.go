package tm

import (
	"testing"
	"time"
)
//go test go/timer/timer_test.go  -v
type A struct{}

func Test_Timer(t *testing.T) {
	timer := time.NewTimer(30 * time.Second)
	go func() {
		<-timer.C
		t.Logf("Timer has expired.") //马上输出
	}()
	timer.Reset(0 * time.Second)
	//time.Sleep(2 * time.Second)
}

func Test_ExpireTimer(t *testing.T) {
	timer := time.NewTimer(1 * time.Second)
	time.Sleep(2 * time.Second)
	<-timer.C
	t.Logf("Timer has expired.") // 输出
}

func Test_ResetExpireTimer(t *testing.T) {
	timer := time.NewTimer(1 * time.Second)
	time.Sleep(2 * time.Second)
	timer.Reset(2 * time.Second)
	<-timer.C
	t.Logf("Timer has expired. 1 ") // 输出
	<-timer.C
	t.Logf("Timer has expired. 2 ") // 输出
	select {
	case <-timer.C:
		t.Logf("Timer has expired.")
	default:
		t.Logf("Timer has not expired.") //输出
	}
}

func Test_StopExpireTimer(t *testing.T) {
	timer := time.NewTimer(2 * time.Second)
	timer.Stop()
	select {
	case <-timer.C:
		t.Logf("Timer has expired.") //输出
	default:
		t.Logf("Timer has not expired.")
	}

}
