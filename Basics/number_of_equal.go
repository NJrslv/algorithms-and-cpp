/*
You are given two arrays 𝑎 and 𝑏, sorted in non-decreasing order. 
Find the number of pairs (𝑖,𝑗) for which 𝑎𝑖=𝑏𝑗

Input
The first line contains integers 𝑛 and 𝑚, the sizes of the arrays (1≤𝑛,𝑚≤105). 
The second line contains 𝑛 integers 𝑎𝑖, elements of the first array, 
the third line contains 𝑚 integers 𝑏𝑖, elements of the second array (−109≤𝑎𝑖,𝑏𝑖≤109).

Output
Print one number, the answer to the problem.
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
 
    var n, m int
    scanf("%d %d\n", &n, &m)
 
    a := make([]int, n)
    for i := 0; i < n; i++ {
        scanf("%d ", &a[i])
    }
 
    b := make([]int, m)
    for i := 0; i < m; i++ {
        scanf("%d ", &b[i])
    }

    printf("%d", numOfEqual(a, b))
}

func numOfEqual(a, b []int) int64 {
    n, m := len(a), len(b)
    var cnt int64 = 0 
    i, j := 0, 0

    for i < n || j < m {
        if i < n && j < m && a[i] == b[j] {
            aCnt, bCnt := 1, 1
            i, j = i + 1, j + 1
            for i < n && a[i - 1] == a[i] {
                aCnt++
                i++
            }
            for j < m && b[j - 1] == b[j] {
                bCnt++
                j++
            }
            cnt += int64(aCnt * bCnt)
        } else if j == m || i < n && a[i] < b[j] {
            i++
        } else {
            j++
        }
    }

    return cnt
}
