package main

import (
	"os"
	"log"
	"bufio"
	"fmt"
	"unicode"
	"strconv"
)

type Coordinate struct {
    X, Y int
}

var schema = [][]rune{}
var maxR = 140
var maxC = 140

func checkEdges(x, y int) bool {
	directions := [][]int{
		{-1, 1}, 
		{-1, -1},
		{1, -1}, 
		{1, 1}, 
		{0, 1},
		{0, -1},
		{1, 0},
		{-1, 0},
	}

	for _, dir := range directions { 
		dirX, dirY := x + dir[0], y + dir[1] 
		if dirX >= 0 && dirX < maxC && dirY >= 0 && dirY < maxR && schema[dirX][dirY] != '.' && !unicode.IsDigit(schema[dirX][dirY]) {
			return true
		}
	}
	return false
}


func scanSchema() int {
	var temp map[Coordinate]int
    temp = make(map[Coordinate]int)
	element := ""
	sum := 0

	for x, col := range schema {
		for y, _ := range col {
			if unicode.IsDigit(schema[x][y]) {
				element += string(schema[x][y])
				temp[Coordinate{X: x, Y: y}] = x
				continue
			} 
			for coord, _ := range temp {
				if checkEdges(coord.X,coord.Y) {
					num, err := strconv.Atoi(element)
					if err != nil {
						log.Fatal(err)
					}
					sum += num
					break
				}
			}
			temp = make(map[Coordinate]int)
			element = ""
		}
	}
	return sum

}

func main() {
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		if len(line) == 0 {
			break
		}
		var chars []rune
		for _, char := range line {
			chars = append(chars, rune(char))
		}
		schema = append(schema, chars)
	}
	sum := scanSchema()
	fmt.Println("Result ", sum)
}