/*
This is a problem from the Russia High School Team Programming Contest 2013

In the center of Che city there is a pedestrian street, one of the most popular walking places for city residents.
This street is very pleasant to walk, because along the street there are 𝑛 funny monuments.

The girl Masha from the city of Che likes two boys from her school, and she cannot make a choice between them.
To make the final decision, she decided to date both boys at the same time.
Masha wants to choose two monuments on the pedestrian street, near which the boys will be waiting for her.
At the same time, she wants to choose such monuments so that the boys do not see each other.
Masha knows that because of the fog, the boys will see each other only if they are on distance not more than 𝑟 meters.
Masha got interested in how many ways there are to choose two different monuments for organizing dates.

Input
The first line of the input file contains two integers 𝑛 and 𝑟 (2≤𝑛≤300000, 1≤𝑟≤10^9),
the number of monuments and the maximum distance at which boys can see each other.

The second line contains 𝑛 positive numbers 𝑑1,…,𝑑𝑛,
where 𝑑𝑖 is the distance from the 𝑖-th monument to the beginning of the street.
All monuments are located at different distances from the beginning of the street.
Monuments are listed in ascending order of distance from the beginning of the street (1≤𝑑1<𝑑2<…<𝑑𝑛≤10^9).

Output
Print one number, the number of ways to choose two monuments for organizing dates.
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
	var r int
	scanf("%d %d\n", &n, &r)

	a := make([]int, n)
	for i := 0; i < n; i++ {
		scanf("%d ", &a[i])
	}

	printf("%d", calcBigPairs(&a, r))
}

func calcBigPairs(in *[]int, rad int) int64 {
	cntPairs := int64(0)
	r, size := 0, len(*in)

	for l := 0; l < size; l++ {
		for r < size && (*in)[r]-(*in)[l] <= rad {
			r++
		}
		cntPairs += int64(size - r)
	}

	return cntPairs
}
