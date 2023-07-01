/*
Given a string 𝑠 and 𝑚 cards with letters. Your task is to count the number of substrings of the string 𝑠 that can be made from these cards.

For example, if 𝑠=«aaab», and there are three cards with the letters «a», «a», and «b»,
then you can make three substrings «a», substring «b», two substrings «aa», substrings «ab» and «aab».
And you can not make the substrings «aaa» and «aaab», since there are only two cards with the letter «a».

Input
The first line of the input contains two integers 𝑛 and 𝑚 (1≤𝑛,𝑚≤105), the length of the string and the number of cards.
The second line of the input contains a string 𝑠 of length 𝑛
The third line of the input contains a string of length 𝑚 that specifies the letters written on the cards.

Both strings consist of only lowercase letters of the English alphabet.

Output
Print one integer, the number of substrings in 𝑠 that can be made from these cards.
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
var c []byte

func main() {
	defer writer.Flush()

	var n int
	var m int
	scanf("%d %d\n", &n, &m)

	s = make([]byte, n)
	for i := 0; i < n; i++ {
		scanf("%c", &s[i])
	}

	scanf("\n")

	c = make([]byte, m)
	for i := 0; i < m; i++ {
		scanf("%c", &c[i])
	}

	printf("%d", calcSubStrings(n, m))
}

func calcSubStrings(n, m int) int64 {
	res, l := int64(0), 0
	alphabet := makeAlphabet(m)

	for r := 0; r < n; r++ {
		for alphabet[s[r]-97] == 0 {
			alphabet[s[l]-97]++
			l++
		}
		alphabet[s[r]-97]--
		res += int64(r - l + 1)
	}

	return res
}

func makeAlphabet(m int) []int {
	alphabet := make([]int, 26)

	for i := 0; i < m; i++ {
		ind := c[i] - 97
		alphabet[ind]++
	}

	return alphabet
}
