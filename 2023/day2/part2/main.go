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

var g_cubes = map[string] int {
	"red": 0, 
	"green": 0,
	"blue": 0,
}

func max(a, b int) int {
    if a >= b {
        return a
    }
    return b
}

func scanCubes(item string) {
	var count []rune
	var color []rune

	setMinPossibleValue := func() {
		countC, err := strconv.Atoi(string(count))
		if err != nil {
			log.Fatal(err)
		}
		g_cubes[string(color)] = max(g_cubes[string(color)], countC)
	}

	for _, char := range item {
		switch {
		case unicode.IsDigit(char):
			count = append(count, char)
		case unicode.IsLetter(char):
			color = append(color, char)
		case char == ',':
			setMinPossibleValue()
			color, count = nil, nil
		}
	}
	setMinPossibleValue()
}

func getPowerOfMinCubes() int {
	sum := g_cubes["red"] * g_cubes["green"] * g_cubes["blue"]
	for k := range g_cubes {
        g_cubes[k] = 0
    }
	return sum
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
	for scanner.Scan() {
		line := scanner.Text()
		if len(line) == 0 {
			break
		}
		colonIndex := strings.Index(line, ":")
		if colonIndex != -1 {
			result := strings.TrimSpace(line[colonIndex+1:])
			rounds := strings.Split(result, ";")
			for _ , item := range rounds {
				scanCubes(item)
			}
		}
		sum += getPowerOfMinCubes()
		idx++
	}
	fmt.Println("Result ", sum)

}