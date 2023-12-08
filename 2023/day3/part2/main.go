package main

import (
	"os"
	"log"
	"bufio"
	"fmt"
	"unicode"
	"strconv"
	"strings"
)

var schema = [][]rune{}
var maxR = 140
var maxC = 140
var adjacentNumber = ""

func getFullAdjacentNumber(dirX, dirY int) string {	
	element := ""

	x, y := dirX, dirY 
	for y >=0 && unicode.IsDigit(schema[x][y]) {
		element = string(schema[x][y]) + element
		y--
	}
	y = dirY + 1
	for y < maxC && unicode.IsDigit(schema[x][y]) {
		element += string(schema[x][y])
		y++
	}
	return element
}

func checkEdges(x, y int) string {
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

	num := ""
	for _, dir := range directions { 
		dirX, dirY := x + dir[0], y + dir[1] 
		if dirX >= 0 && dirX < maxC && dirY >= 0 && dirY < maxR && unicode.IsDigit(schema[dirX][dirY]){
			num = getFullAdjacentNumber(dirX, dirY)
			if num != adjacentNumber {
				return num
			}
		}
	}
	return num
}


func convertToNum(str string) int {
	num, err := strconv.Atoi(str)
	if err != nil {
		log.Fatal(err)
	}
	return num
}

func scanSchema() int {
	sum := 0
	for x, col := range schema {
		for y, _ := range col {
			if schema[x][y] == '*' {
				schema[x][y] = '.'
				numOne := checkEdges(x,y)
				adjacentNumber = numOne
				numTwo:= checkEdges(x,y)
				if numOne != "" && numTwo != "" && strings.Compare(numOne, numTwo) != 0 {
					sum += convertToNum(numOne) * convertToNum(numTwo) 
				}
			} 
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