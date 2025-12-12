package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
	"sort"
)

type Range struct {
	start int
	end   int
}

var ranges []Range

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
		if line == "" {
			break
		}
		numbers := strings.Split(line, "-")
		start, _ := strconv.Atoi(numbers[0])
		end, _ := strconv.Atoi(numbers[1])
		ranges = append(ranges, Range{start: start, end: end})
	}
	sort.Slice(ranges, func(i, j int) bool {
		return ranges[i].start < ranges[j].start
	})
	var merged []Range
	for _, r := range ranges {
		if len(merged) == 0 || r.start > merged[len(merged)-1].end+1 {
			merged = append(merged, r)
		} else {
			if r.end > merged[len(merged)-1].end {
				merged[len(merged)-1].end = r.end
			}
		}
	}
	for _, r := range merged {
		sum += r.end - r.start + 1
	}
	fmt.Println("Sum is ", sum)
}
