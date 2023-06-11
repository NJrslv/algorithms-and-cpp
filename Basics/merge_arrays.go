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
 
    var c = merge(a, b)
    for i := 0; i < n + m; i++ {
        printf("%d ", c[i])
    }
}
 
func merge(a, b []int) (c []int) {
    n, m := len(a), len(b)
    c = make([]int, n + m) 
    i, j := 0, 0
    for i < n || j < m {
        if j == m || i < n && a[i] < b[j] {
            c[i + j] = a[i]
            i++
        } else {
            c[i + j] = b[j]
            j++
        }
    }
    return
}
