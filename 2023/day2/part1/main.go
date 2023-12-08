package main

import (
	"os"
	"strings"
	"bufio"
	"log"
	"fmt"
	"unicode"
	"strconv"
)

var cubes = map[string] int {
	"red": 12, 
	"green": 13,
	"blue": 14,
}

func scanCubes(item string)	bool {
	var count []rune
	var color []rune

	isValidCube := func() bool {
		maxValue := cubes[string(color)]
		countC, err := strconv.Atoi(string(count))
		if err != nil {
			return false
		}
		return maxValue >= countC
	}

	for _, char := range item {
		switch {
		case unicode.IsDigit(char):
			count = append(count, char)
		case unicode.IsLetter(char):
			color = append(color, char)
		case char == ',':
			if !isValidCube() {
				return false
			}
			color, count = nil, nil
		}
	}
	return isValidCube()
}

func main() {
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	sum := 0
	idx := 1
	valid := false

	for scanner.Scan() {
		line := scanner.Text()
		if len(line) == 0 {
			break
		}
		colonIndex := strings.Index(line, ":")
		if colonIndex != -1 {
			result := strings.TrimSpace(line[colonIndex+1:])
			rounds := strings.Split(result, ";")
			sum += idx
			for _, item := range rounds {
				valid = scanCubes(item)
				if !valid {
					sum -= idx
					break
				}
			}
		}
		idx++
	}
	fmt.Println("Result ", sum)
}