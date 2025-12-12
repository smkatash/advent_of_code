package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)


func largestJolt(jolts []string) int {
	var largestJolt int
	var combination string
	for i := 0; i < len(jolts) - 1; i++ {
		for j := i + 1; j < len(jolts); j++ {
			combination = jolts[i] + jolts[j]
			num, err := strconv.Atoi(combination)
			if err != nil {
				log.Fatal(err)
			}
			if num > largestJolt {
				largestJolt = num
			}
		}
	}
	return largestJolt
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
		numbers := strings.Split(line, "")
		largestJolt := largestJolt(numbers)
		sum += largestJolt
	}

	fmt.Println("Sum is ", sum)
}
