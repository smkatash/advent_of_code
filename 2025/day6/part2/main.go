package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)


type Worksheet struct {
	numbers []int
	symbol string
}

const numWorksheets = 1000
var worksheets [numWorksheets]Worksheet

func splitInt(n int) []int {
		slc := []int{}
		for n > 0 {
			slc = append(slc, n%10)
			n /= 10
		}

		result := []int{}
		for i := range slc {
			result = append(result, slc[len(slc)-1-i])
		}

		return result
}

func doMath(ws Worksheet) int {
	result := 0
	switch ws.symbol {
	case "+":
		for _, num := range ws.numbers {
			result += num
		}
	case "*":
		result = 1
		for _, num := range ws.numbers {
			result *= num
		}
	default:
		log.Fatalf("Unknown symbol %s", ws.symbol)
	}
	return result
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
	for scanner.Scan() {
		line := scanner.Text()
		numbers := string.Split(line, " ")
		for idx, numStr := range numbers {
			num, err := strconv.Atoi(numStr)
			if err != nil {
				worksheets[idx].symbol = numStr
			} else {
				worksheets[idx].numbers = append(worksheets[idx].numbers, num)
			}
		}
	}
	for _, ws := range worksheets {
		result := doMath(ws)
		sum += result
	}
	fmt.Println("Sum is ", sum)
}
