/*
You are given a string 𝑠, consisting of 𝑛 lowercase English letters.

Rudeness of a string 𝑡 of length 𝑘 is the number of pairs of integers (𝑖,𝑗), where 1≤𝑖<𝑗≤𝑘, for which𝑡𝑖=«a» and 𝑡𝑗=«b».
In other words, the rudeness of a string is the number of ways to delete all but two of its characters, so that the string «ab» remains.

Your task is to find a substring 𝑠𝑙 𝑠𝑙+1 … 𝑠𝑟, the rudeness of which does not exceed 𝑐, of maximum length.

Input
The first line of the input contains two integers 𝑛 and 𝑐 (1≤𝑛≤10^6, 0≤𝑐≤10^18).

The second line contains the string 𝑠. The string consists of 𝑛 lowercase English letters.

Output
Print a single integer, the maximum length of a substring of a string that has rudeness at most 𝑐.
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

var s []byte

func main() {
	defer writer.Flush()

	var n int
	var c int64
	scanf("%d %d\n", &n, &c)

	s = make([]byte, n)
	for i := 0; i < n; i++ {
		scanf("%c", &s[i])
	}

	printf("%d", findLargestRudeStr(n, c))
}

func findLargestRudeStr(n int, c int64) int {
	l, currRudeness := 0, int64(0)
	aCnt, bCnt := 0, 0
	res := 0

	for r := 0; r < n; r++ {
		if s[r] == byte('a') {
			aCnt++
		} else if s[r] == byte('b') {
			bCnt++
			currRudeness += int64(aCnt)
		}

		for currRudeness > c {
			if s[l] == byte('a') {
				aCnt--
				currRudeness -= int64(bCnt)
			} else if s[l] == byte('b') {
				bCnt--
			}
			l++
		}

		res = max(res, r-l+1)
	}

	return res
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
