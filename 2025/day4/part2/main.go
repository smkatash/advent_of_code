package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

const totalX, totalY = 139, 139

var grid [totalX][totalY]bool

func adjacentPaperRolls(x, y int) int {
	dirs := [][2]int{
		{-1, 0}, {1, 0}, {0, -1}, {0, 1},
		{-1, -1}, {-1, 1}, {1, -1}, {1, 1},
	}
	
	count := 0
	for _, dir := range dirs {
		nx, ny := x + dir[0], y + dir[1]
		if nx >= 0 && nx < totalX && ny >= 0 && ny < totalY {
			if (grid[nx][ny]) {
				count++
			}
		}
	}
	return count
}

func deepCopyGrid(grid [totalX][totalY]bool) [totalX][totalY]bool {
	var newGrid [totalX][totalY]bool
	for i := 0; i < totalX; i++ {
		for j := 0; j < totalY; j++ {
			newGrid[i][j] = grid[i][j]
		}
	}
	return newGrid
}

func main() {	
	fileName := os.Args[1]
	file, err := os.Open(fileName)
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	sum := 0
	x, y := 0, 0
	for scanner.Scan() {
		line := scanner.Text()
		rolls := strings.Split(line, "")
		for _, r := range rolls {
			if r == "@" {
				grid[x][y] = true
			} else {
				grid[x][y] = false
			}
			y++
		}
		x++
		y = 0
	}
	count := 0
	for {
		newGrid := deepCopyGrid(grid)
		for i := 0; i < totalX; i++ {
			for j := 0; j < totalY; j++ {
				if grid[i][j] {
					paperRolls := adjacentPaperRolls(i, j)
					if paperRolls < 4 {
						sum++
					}
					if grid[i][j] == true && paperRolls < 4 {
						newGrid[i][j] = false
					}
				}
			}
		}
		grid = newGrid
		if (count == sum) {
			break
		}
		count = sum
	}
	fmt.Println("Sum is ", sum)
}
