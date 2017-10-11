package main

import "time"

//http://tonybai.com/2016/12/21/how-to-use-timer-reset-in-golang-correctly/
//https://golang.org/pkg/time/#Timer.Reset

//Reset changes the timer to expire after duration d. It returns true if the timer had been active,
//false if the timer had expired or been stopped.
// Resetting a timer must take care not to race with the send into t.C that happens when the current timer expires.
// If a program has already received a value from t.C, the timer is known to have expired, and t.Reset can be used directly.
// If a program has not yet received a value from t.C, however, the timer must be stopped and—if Stop reports that the timer
// expired before being stopped—the channel explicitly drained:

func main() {
	t := time.NewTimer(2 * time.Second)
	if !t.Stop() {
		select {
		case <-t.C:
		default:
		}
	}
	t.Reset(1 * time.Second)
}
