/*
Given an array of 𝑛 integers 𝑎𝑖.
Let's say that a segment of this array 𝑎[𝑙..𝑟] (1≤𝑙≤𝑟≤𝑛) is good
if the difference between the maximum and minimum elements on this segment is at most 𝑘.
Your task is to find the number of different good segments.

Input
The first line contains integers 𝑛 and 𝑘 (1≤𝑛≤10^5, 0≤𝑘≤𝑛). The second line contains integers 𝑎𝑖 (1≤𝑎𝑖≤10^5).

Output
Print one integer, the number of good segments.
*/

// T - O(n), S - O(n)

package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
)

var reader *bufio.Reader = bufio.NewReader(os.Stdin)
var writer *bufio.Writer = bufio.NewWriter(os.Stdout)

func printf(f string, a ...interface{}) { fmt.Fprintf(writer, f, a...) }
func scanf(f string, a ...interface{})  { fmt.Fscanf(reader, f, a...) }

func main() {
	defer writer.Flush()

	var n int
	var k int64
	scanf("%d %d\n", &n, &k)

	a := make([]int64, n)
	for i := 0; i < n; i++ {
		scanf("%d ", &a[i])
	}

	printf("%d", smallSegmentSpread(&a, k))
}

func smallSegmentSpread(a *[]int64, k int64) int64 {
	l := 0
	res := int64(0)
	var q Queue
	for r := 0; r < len(*a); r++ {
		q.Push((*a)[r])
		for q.Max()-q.Min() > k {
			q.Pop()
			l++
		}
		res += int64(r - l + 1)
	}
	return res
}

type Stack []int64

func (s *Stack) Push(v int64) {
	*s = append(*s, v)
}

func (s *Stack) Top() int64 {
	l := len(*s)
	top := (*s)[l-1]
	return top
}

func (s *Stack) Pop() {
	*s = (*s)[:len(*s)-1]
}

func (s *Stack) Len() int {
	return len(*s)
}

type MinMaxStack struct {
	st    Stack
	minSt Stack
	maxSt Stack
}

func (s *MinMaxStack) Push(v int64) {
	s.st.Push(v)

	if s.minSt.Len() == 0 || v < s.minSt.Top() {
		s.minSt.Push(v)
	} else {
		s.minSt.Push(s.minSt.Top())
	}

	if s.maxSt.Len() == 0 || v > s.maxSt.Top() {
		s.maxSt.Push(v)
	} else {
		s.maxSt.Push(s.maxSt.Top())
	}
}

// Pop We do not need to get the exact value
func (s *MinMaxStack) Pop() {
	s.st.Pop()
	s.minSt.Pop()
	s.maxSt.Pop()
}

func (s *MinMaxStack) Min() int64 {
	if s.st.Len() == 0 {
		return math.MaxInt64
	}
	return s.minSt.Top()
}

func (s *MinMaxStack) Max() int64 {
	if s.st.Len() == 0 {
		return math.MinInt64
	}
	return s.maxSt.Top()
}

type Queue struct {
	pushSt MinMaxStack
	popSt  MinMaxStack
}

func (q *Queue) Push(v int64) {
	q.pushSt.Push(v)
}

func (q *Queue) Pop() {
	if q.popSt.st.Len() == 0 {
		for q.pushSt.st.Len() != 0 {
			v := q.pushSt.st.Top()
			q.popSt.Push(v)
			q.pushSt.Pop()
		}
	}
	q.popSt.Pop()
}

func (q *Queue) Min() int64 {
	return Min(q.popSt.Min(), q.pushSt.Min())
}

func (q *Queue) Max() int64 {
	return Max(q.popSt.Max(), q.pushSt.Max())
}

func Min(x, y int64) int64 {
	if x < y {
		return x
	}
	return y
}

func Max(x, y int64) int64 {
	if x > y {
		return x
	}
	return y
}
