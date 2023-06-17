/*
Given an array of 𝑛 integers 𝑎𝑖. 
Let's say that the segment of this array 𝑎[𝑙..𝑟] (1≤𝑙≤𝑟≤𝑛) 
is good if the sum of elements on this segment is at most 𝑠. 
Your task is to find the longest good segment.

Input
The first line contains integers 𝑛 and 𝑠 (1≤𝑛≤10^5, 1≤𝑠≤10^18). The second line contains integers 𝑎𝑖(1≤𝑎𝑖≤10^9).

Output
Print one integer, the length of the longest good segment. If there are no such segments, print 0
.
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
func scanf(f string, a ...interface{}) { fmt.Fscanf(reader, f, a...) }
 
func main() {
    defer writer.Flush()
 
    var n int
    var s int64
    scanf("%d %d\n", &n, &s)
 
    a := make([]int, n)
    for i := 0; i < n; i++ {
        scanf("%d ", &a[i])
    }
 
    printf("%d", smallSumSegment(&a, s))
}

func smallSumSegment(a *[]int, s int64) int {
    l, res := 0, 0
    sum := int64(0)
    for r := 0; r < len(*a); r++ {
        sum += int64((*a)[r])
        for sum > s {
            sum -= int64((*a)[l])
            l++
        }
        res = Max(res, r - l + 1)
    }
    return res
}

func Max(x, y int) int {
	if x < y {
		return y
	}
	return x
}
