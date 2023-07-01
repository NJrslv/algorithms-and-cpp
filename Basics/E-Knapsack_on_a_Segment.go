/*
Given an array of 𝑛 items, for each of them its weight is 𝑤𝑖 and cost is 𝑐𝑖.
You need to select a segment of this array, the total weight on which is not more than 𝑠, and the total cost is maximum.

Input
The first line contains integers 𝑛 and 𝑠 (1≤𝑛≤10^5, 1≤𝑠≤10^9).
The second line contains 𝑛 integers 𝑤𝑖(1≤𝑤𝑖≤10^9).
The third line contains 𝑛 integers 𝑐𝑖 (1≤𝑐𝑖≤10^9).

Output
Print one number, the maximum total cost of items that can be put into a knapsack.
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

var w []int
var c []int

func main() {
	defer writer.Flush()

	var n int
	var s int
	scanf("%d %d\n", &n, &s)

	w = make([]int, n)
	for i := 0; i < n; i++ {
		scanf("%d ", &w[i])
	}

	c = make([]int, n)
	for i := 0; i < n; i++ {
		scanf("%d ", &c[i])
	}

	printf("%d", calcMaxCost(n, s))
}

func calcMaxCost(n, s int) int64 {
	maxCost := int64(0)
	l, currCost := 0, int64(0)

	currWeight := 0
	for r := 0; r < n; r++ {
		currCost += int64(c[r])
		currWeight += w[r]

		for currWeight > s {
			currCost -= int64(c[l])
			currWeight -= w[l]
			l++
		}

		maxCost = max(currCost, maxCost)
	}

	return maxCost
}

func max(a, b int64) int64 {
	if a > b {
		return a
	}
	return b
}
