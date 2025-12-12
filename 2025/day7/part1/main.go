package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)


const rows = 142
const cols = 142

var grid [cols][rows]string


func setTachyonBeams(i int, j int, sum *int) {
	if j - 1 >= 0 && j - 1 < cols && grid[i][j - 1] == "." { 
			grid[i][j - 1 ] = "|"
			for k := 1; k < cols; k++ { 
				if j - 1 >= 0 && j - 1 < cols && 
				i + k >= 0 && i + k < rows &&
				grid[i + k][j - 1] == "."{
					grid[i + k][j - 1] = "|"
				} else if j - 1 >= 0 && j - 1 < cols && 
					i + k >= 0 && i + k < rows &&
					grid[i + k][j - 1] == "^" {
						*sum++
						break
				} else {
					break
				}
			}
	}
	if j + 1 >= 0 && j + 1 < cols && grid[i][j + 1] == "." {
		grid[i][j + 1] = "|"
		for k := 1; k < cols; k++ { 
				if j + 1 >= 0 && j + 1 < cols && 
				i + k >= 0 && i + k < rows &&
				grid[i + k][j + 1] == "."{
					grid[i + k][j + 1] = "|"
				} else if j + 1 >= 0 && j + 1 < cols && 
					i + k >= 0 && i + k < rows &&
					grid[i + k][j + 1] == "^" {
						*sum++
						break
				} else {
					break
				}
			}
	}
}

func transformGrid(sum *int) {
	for i := 0; i < rows; i++  {
		for j := 0; j < cols; j++ {
			if grid[i][j] == "^" {
				setTachyonBeams(i, j, sum)
			}
		}
	} 
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
	col := 0
	for scanner.Scan() {
		line := scanner.Text()
		puzzle := strings.Split(line, "")
		for idx, tachyon := range puzzle {
			grid[col][idx] = tachyon
		}
		col++
	}
	transformGrid(&sum)
	fmt.Println("Sum is ", sum + 1)
}
