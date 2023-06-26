/*
Misha listens to music on his player, his playlist consists of n songs that are played in a specific order.
After the last song ends, the first one starts playing. Each song has its own characteristic, positivity ai, given by an integer.
After listening to the i-h song, Misha's mood increases by ai.

Misha can start listening to any of the songs and listen to any number of songs in a row, while he may listen to some songs more than once.

Misha feels happy if his mood after listening to the songs has increased by at least p.
He wants to feel happy listening to as few songs as possible.
Help him choose the song to start listening to and the number of songs to listen to to be happy.

Input
The first line contains two integers n and p (1<=n≤1000, 1≤p≤10^18), the number of songs in the playlist and the amount that Misha wants increase his mood.

The second line contains n integers ai (1≤ai≤10^9), positivity of the songs.

Output
Print two numbers, the index of the song k, with which you should start listening, and the number of songs c, which you should listen to.
If there are several possible answers, print any.
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
	var p int64
	scanf("%d %d\n", &n, &p)

	a := make([]int, n)
	for i := 0; i < n; i++ {
		scanf("%d ", &a[i])
	}

	start, cnt := loopedPlayist(&a, p)
	printf("%d %d", start, cnt)
}

func loopedPlayist(nums *[]int, p int64) (int, int64) {
	sum := int64(0)
	for _, num := range *nums {
		sum += int64(num)
	}

	loops := p / sum
	p %= sum
	start, cnt := -1, maxInt64

	cycle, l := append(*nums, *nums...), 0
	sum = int64(0)
	for r := 0; r < len(cycle); r++ {
		sum += int64(cycle[r])
		for sum >= p {
			if sum >= p && int64(r-l+1) < cnt {
				cnt = int64(r - l + 1)
				start = l
			}
			sum -= int64(cycle[l])
			l++
		}
	}

	if loops > 0 {
		cnt += int64(len(*nums)) * loops
		start = 0
	} else {
		start %= len(*nums)
	}

	return start + 1, cnt
}
