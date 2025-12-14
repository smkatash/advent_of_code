package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)


type Point struct {
	x int
	y int
}


var allPoints []Point

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
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
		allPoints = append(allPoints, point)
	}

	maxArea := 0

	for i := 0; i < len(allPoints); i++ {
		for j := i + 1; j < len(allPoints); j++ {
			p1 := allPoints[i]
			p2 := allPoints[j]
			if p1.x != p2.x && p1.y != p2.y {
				area := (abs(p1.x-p2.x) + 1) * (abs(p1.y-p2.y) + 1)
				if area > maxArea {
					maxArea = area
				}
			}
		}
	}

	fmt.Println("Max area is ", maxArea)
}
