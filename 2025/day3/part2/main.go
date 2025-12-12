package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

const pick = 12

func largestJolt(jolts []string) (int64, error) {
	n := len(jolts)

	stack := make([]string, 0, pick)
	for i := 0; i < n; i++ {
		remaining := n - i
		for len(stack) > 0 &&
			stack[len(stack)-1] < jolts[i] &&
			(len(stack)-1+remaining) >= pick {
			stack = stack[:len(stack)-1]
		}
		if len(stack) < pick {
			stack = append(stack, jolts[i])
		}
	}

	selection := stack[:pick]
	s := strings.Join(selection, "")
	val, err := strconv.ParseInt(s, 10, 64)
	if err != nil {
		return 0, fmt.Errorf("parse error for %q: %w", s, err)
	}
	return val, nil
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
		largestJolt, _ := largestJolt(numbers)
		sum += int(largestJolt)
	}

	fmt.Println("Sum is ", sum)
}
