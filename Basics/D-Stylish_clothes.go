/*
Gleb loves shopping. Once, he got the idea to choose a cap, a shirt, pants and shoes so that they look as stylish as possible.
In Gleb's understanding clothes are more stylish when the difference in color of the elements of his clothes is small.

There are n1 caps, n2 shirts, n3 pants and n4 shoes (1≤ni≤100,000).
Each clothes element has its color (an integer from 1 to 100,000).
A set of clothes is one cap, shirt, pants and one pair of boots.
Each set is characterized by the maximum difference between any two of its elements.
Help Gleb to choose the most stylish set, that is the set with the minimum color difference.

Input
For each clothes element i (i = 1, 2, 3, 4) given its count ni, and ni integers in next line which is their color.
First clothes element in input is caps, second is shirts, third is pants and forth is shoes.
All numbers in input are positive integers not bigger than 100,000.

Output
Write 4 integers in output, color of cap, shirt, pants and shoes Gleb will choose.
If there are several most stylish sets output any of them.
*/

// ! Codeforces has an old Golang compiler 29.06.2023 -> RTE on CF
package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"sort"
)

var reader *bufio.Reader = bufio.NewReader(os.Stdin)
var writer *bufio.Writer = bufio.NewWriter(os.Stdout)

func printf(f string, a ...interface{}) { fmt.Fprintf(writer, f, a...) }
func scanf(f string, a ...interface{})  { fmt.Fscanf(reader, f, a...) }

var caps []Unit
var shirts []Unit
var pants []Unit
var shoes []Unit

type Unit struct {
	t int // type
	c int // color
}

func main() {
	defer writer.Flush()

	n1 := fillСlothes(0, &caps)
	n2 := fillСlothes(1, &shirts)
	n3 := fillСlothes(2, &pants)
	n4 := fillСlothes(3, &shoes)

	res := findStyleClothes(n1, n2, n3, n4)
	printf("%d %d %d %d", res[0], res[1], res[2], res[3])
}

func findStyleClothes(n1 int, n2 int, n3 int, n4 int) [4]int {
	var styleClothes [4]int
	var packedClothes [4]Queue
	styleIndex := math.MaxInt
	allClothes := combineSortClothes(n1, n2, n3, n4)
	size := len(allClothes)

	r := 0
	for l := 0; l < size; l++ {
		for ; r < size && isSkipClothes(&packedClothes); r++ {
			packedClothes[allClothes[r].t].Push(allClothes[r].c)
		}

		if allClothes[r-1].c-allClothes[l].c < styleIndex {
			styleIndex = allClothes[r-1].c - allClothes[l].c
			for i, q := range packedClothes {
				styleClothes[i] = q.Top()
			}
		}

		packedClothes[allClothes[l].t].Pop()
	}

	return styleClothes
}

func isSkipClothes(packedClothes *[4]Queue) bool {
	for _, q := range packedClothes {
		if q.len() == 0 {
			return true
		}
	}
	return false
}

func combineSortClothes(n1 int, n2 int, n3 int, n4 int) []Unit {
	allClothes := append(append(append(caps, shirts...), pants...), shoes...)
	sort.Slice(allClothes, func(i, j int) bool {
		return allClothes[i].c < allClothes[j].c
	})
	return allClothes
}

func fillСlothes(typeСlothes int, a *[]Unit) int {
	var n int
	scanf("%d\n", &n)
	*a = make([]Unit, n)

	for i := 0; i < n; i++ {
		var color int
		scanf("%d ", &color)
		(*a)[i] = Unit{typeСlothes, color}
	}

	return n
}

type Stack []int

func (s *Stack) Push(v int) {
	*s = append(*s, v)
}

func (s *Stack) Top() int {
	l := len(*s)
	top := (*s)[l-1]
	return top
}

func (s *Stack) Pop() {
	*s = (*s)[:len(*s)-1]
}

func (s *Stack) Len() int {
	return len(*s)
}

type Queue struct {
	pushSt Stack
	popSt  Stack
}

func (q *Queue) Push(v int) {
	q.pushSt.Push(v)
}

func (q *Queue) Top() int {
	if q.popSt.Len() == 0 {
		for q.pushSt.Len() != 0 {
			v := q.pushSt.Top()
			q.popSt.Push(v)
			q.pushSt.Pop()
		}
	}
	return q.popSt.Top()
}

func (q *Queue) Pop() {
	if q.popSt.Len() == 0 {
		for q.pushSt.Len() != 0 {
			v := q.pushSt.Top()
			q.popSt.Push(v)
			q.pushSt.Pop()
		}
	}
	q.popSt.Pop()
}

func (q *Queue) len() int {
	return q.popSt.Len() + q.pushSt.Len()
}
