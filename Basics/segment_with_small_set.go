/*
Given an array of 𝑛 integers 𝑎𝑖.
Let's say that a segment of this array 𝑎[𝑙..𝑟] (1≤𝑙≤𝑟≤𝑛) is good
if there are no more than 𝑘 unique elements on this segment.
Your task is to find the number of different good segments.

Input
The first line contains integers 𝑛 and 𝑘 (1≤𝑛≤10^5, 0≤𝑘≤𝑛). The second line contains integers 𝑎𝑖 (1≤𝑎𝑖≤10^5).

Output
Print one integer, the number of good segments.
*/
package main

import (
	"bufio"
	"fmt"
	"os"
)

var reader *bufio.Reader = bufio.NewReader(os.Stdin)
var writer *bufio.Writer = bufio.NewWriter(os.Stdout)

func printf(f string, a ...interface{}) { fmt.Fprintf(writer, f, a...) }
func scanf(f string, a ...interface{})  { fmt.Fscanf(reader, f, a...) }

func main() {
	defer writer.Flush()

	var n, k int
	scanf("%d %d\n", &n, &k)

	a := make([]int, n)
	for i := 0; i < n; i++ {
		scanf("%d ", &a[i])
	}

	printf("%d", smallSegmentSet(&a, k))
}

func smallSegmentSet(a *[]int, k int) int64 {
	l, cnt := 0, 0
	res := int64(0)
	m := make(map[int]int)
	for r := 0; r < len(*a); r++ {
		m[(*a)[r]]++
		if m[(*a)[r]] == 1 {
			cnt++
		}
		for cnt > k {
			m[(*a)[l]]--
			if m[(*a)[l]] == 0 {
				cnt--
			}
			l++
		}
		res += int64(r - l + 1)
	}
	return res
}
