package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
	"math"
	"sort"
)


type Point struct {
	x int
	y int
	z int
}

type Junction struct {
	a, b int
	dist float64
}

type DSU struct {
	parent, size []int
}

var allPoints []Point

func calculate3DDistance(a Point, b Point) float64 {
	x := (a.x-b.x) 
	y := (a.y-b.y)
	z := (a.z-b.z)
	return math.Sqrt(float64(x*x + y*y + z*z))
}

func newDSU(n int) *DSU {
	p := make([]int, n)
	s := make([]int, n)
	for i := 0; i < n; i++ {
		p[i] = i
		s[i] = 1
	}
	return &DSU{parent: p, size: s}
}

func (d *DSU) find(x int) int {
	if d.parent[x] != x {
		d.parent[x] = d.find(d.parent[x])
	}
	return d.parent[x]
}

func (d *DSU) Union(a, b int) bool {
	ra := d.find(a)
	rb := d.find(b)
	if ra == rb {
		return false
	}
	if d.size[ra] < d.size[rb] {
		ra, rb = rb, ra
	}
	d.parent[rb] = ra
	d.size[ra] += d.size[rb]
	return true
}


func main() {	
	fileName := os.Args[1]
	file, err := os.Open(fileName)
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		position := strings.Split(line, ",")
		point := Point{}
		point.x, _ = strconv.Atoi(position[0])
		point.y, _ = strconv.Atoi(position[1])
		point.z, _ = strconv.Atoi(position[2])
		allPoints = append(allPoints, point)
	}

	var junction []Junction
	n := len(allPoints)
	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			junction = append(junction, Junction{i, j, calculate3DDistance(allPoints[i], allPoints[j])})
		}
	}
	sort.Slice(junction, func(i, j int) bool { return junction[i].dist < junction[j].dist })

	target := 1000
	if target > len(junction) {
		target = len(junction)
	}
	dsu := newDSU(n)
	for i := 0; i < target; i++ {
		e := junction[i]
		dsu.Union(e.a, e.b)
	}
	sizesMap := make(map[int]int)
	for i := 0; i < n; i++ {
		root := dsu.find(i)
		sizesMap[root]++
	}
	var sizes []int
	for _, s := range sizesMap {
		sizes = append(sizes, s)
	}
	sort.Sort(sort.Reverse(sort.IntSlice(sizes)))

	sum := int64(1)
	for i := 0; i < 3; i++ {
		if i < len(sizes) {
			sum *= int64(sizes[i])
		} else {
			sum *= 1
		}
	}

	fmt.Println("Sum is ", sum)
}
