package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"regexp"
	"strconv"
	"strings"
)

type Factory struct {
	indicator string
	buttons  [][]int
}

func pressButtons(indicator string, button []int) string {
	state := []byte(indicator)

	for _, b := range button {
		if b < 0 || b >= len(state) {
			continue 
		}
		if (state[b] == '#') {
			state[b] = '.'
			continue
		}
		state[b] = '#'
	}

	return string(state)
}

func combinations(arr [][]int, k int) [][][]int {
	if k == 0 {
		return [][][]int{{}}
	}
	if len(arr) < k {
		return nil
	}

	var result [][][]int
	for i := 0; i <= len(arr)-k; i++ {
		for _, sub := range combinations(arr[i+1:], k-1) {
			result = append(result, append([][]int{arr[i]}, sub...))
		}
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
	re := regexp.MustCompile(
		`^\[([.#]+)\]\s*((?:\(\d+(?:,\d+)*\)\s*)+)\{(\d+(?:,\d+)*)\}$`,
	)
	groupRe := regexp.MustCompile(`\((\d+(?:,\d+)*)\)`)
	scanner := bufio.NewScanner(file)
	factories := []Factory{}
	for scanner.Scan() {
		line := scanner.Text()
		matches := re.FindStringSubmatch(line)
		if matches == nil {
			log.Fatalf("no match: %q", line)
		}

		pattern := matches[1]
		groups := groupRe.FindAllStringSubmatch(matches[2], -1)

		var intGroups [][]int
		for _, g := range groups {
			numStrs := strings.Split(g[1], ",")
			ints := make([]int, 0, len(numStrs))

			for _, s := range numStrs {
				v, err := strconv.Atoi(s)
				if err != nil {
					log.Fatalf("invalid number %q", s)
				}
				ints = append(ints, v)
			}

			intGroups = append(intGroups, ints)
		}
		factories = append(factories, Factory{
			indicator: pattern,
			buttons:   intGroups,
		})
	}
	sum := 0
	for _, factory := range factories {
		minCount := 0
		for k := 1; k <= len(factory.buttons); k++ {
			for _, buttons := range combinations(factory.buttons, k) {
				indicator := strings.Repeat(".", len(factory.indicator))

				for _, b := range buttons {
					indicator = pressButtons(indicator, b)
				}

				if indicator == factory.indicator {
					count := len(buttons)
					if minCount == 0 || count < minCount {
						minCount = count
					}
				}
			}
		}
		sum += minCount
	}

	fmt.Println("Sum is ", sum)
}
