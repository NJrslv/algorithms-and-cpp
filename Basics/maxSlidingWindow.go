// my solution of max sliding window 
// from https://leetcode.com/problems/sliding-window-maximum/description/
// without using monotonicaly decreasing deque

func maxSlidingWindow(nums []int, k int) []int {
    l := 0
	var res []int
	var q Queue
	for r := 0; r < len(nums); r++ {
		q.Push(nums[r])
		if r - l + 1 == k {
            res = append(res, q.Max())
            l += 1
            q.Pop()
        }
	}
	return res
}

type Stack []int

func (s *Stack) Push(v int) {
	*s = append(*s, v)
}

func (s *Stack) Top() int {
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

type MaxStack struct {
	st    Stack
	maxSt Stack
}

func (s *MaxStack) Push(v int) {
	s.st.Push(v)

	if s.maxSt.Len() == 0 || v > s.maxSt.Top() {
		s.maxSt.Push(v)
	} else {
		s.maxSt.Push(s.maxSt.Top())
	}
}

func (s *MaxStack) Pop() {
	s.st.Pop()
	s.maxSt.Pop()
}

func (s *MaxStack) Max() int {
	if s.st.Len() == 0 {
		return math.MinInt64
	}
	return s.maxSt.Top()
}

type Queue struct {
	pushSt MaxStack
	popSt  MaxStack
}

func (q *Queue) Push(v int) {
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

func (q *Queue) Max() int {
	return Max(q.popSt.Max(), q.pushSt.Max())
}

func Max(x, y int) int {
	if x > y {
		return x
	}
	return y
}
