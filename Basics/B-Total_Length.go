/*
Given an array of 𝑛 integers 𝑎𝑖. Let's say that the segment of this array 𝑎[𝑙..𝑟] (1≤𝑙≤𝑟≤𝑛) is good
if the sum of elements on this segment is at most 𝑠. Your task is to find sum of lengths of all good segments.

Input
The first line contains integers 𝑛 and 𝑠 (1≤𝑛≤10^5, 1≤𝑠≤10^18).
The second line contains integers 𝑎𝑖 (1≤𝑎𝑖≤10^9).

Output
Print one integer, the sum of lengths of all good segments.
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

const maxInt64 = int64(1<<63 - 1)

func main() {
	defer writer.Flush()

	var n int
	var s int64
	scanf("%d %d\n", &n, &s)

	a := make([]int, n)
	for i := 0; i < n; i++ {
		scanf("%d ", &a[i])
	}

	printf("%d", calcTotalLength(&a, s))
}

func calcTotalLength(nums *[]int, s int64) int64 {
	totalLen := int64(0)
	sum, l := int64(0), 0

	for r := 0; r < len(*nums); r++ {
		sum += int64((*nums)[r])
		for sum > s {
			sum -= int64((*nums)[l])
			l++
		}

		if sum <= s {
			segmentLen := int64(r - l + 1)
			// 1 + 2 + ... + segmentLen = segmentLen * (segmentLen + 1) / 2
			totalLen += (segmentLen * (segmentLen + 1)) / 2
		}
	}

	return totalLen
}
