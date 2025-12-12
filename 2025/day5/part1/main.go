package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)


type Range struct {
	start int
	end   int
}

var ranges []Range

func isFresh(ingredient int) bool {
	for _, r := range ranges {
		if ingredient >= r.start && ingredient <= r.end {
			return true
		}
	}
	return false
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
	ingredients := false
	var ingredient int
	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			continue
		}
		if !ingredients {
			numbers := strings.Split(line, "-")
			start, _ := strconv.Atoi(numbers[0])
			end, _ := strconv.Atoi(numbers[1])
			ranges = append(ranges, Range{start: start, end: end})
		}
		ingredient, _ = strconv.Atoi(line)
		if isFresh(ingredient) {
			sum += 1
		}
	}
	fmt.Println("Sum is ", sum)
}
