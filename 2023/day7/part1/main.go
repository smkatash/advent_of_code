package main

import (
	"fmt"
	"os"
	"log"
	"bufio"
	"strings"
	"strconv"
	"sort"
)

type Record struct {
	five map[string]int
	four map[string]int
	full map[string]int
	three map[string]int
	two map[string]int
	one map[string]int
	high map[string]int
}

var rankMap = map[rune]int{
	'A': 14,
	'K': 13,
	'Q': 12,
	'J': 11,
	'T': 10,
	'9': 9,
	'8': 8,
	'7': 7,
	'6': 6,
	'5': 5,
	'4': 4,
	'3': 3,
	'2': 2,
}

func duplicateCounter(str string) map[rune]int {
	counts := make(map[rune]int)
	for _, char := range str {
		counts[char]++
	}
	return counts
}

func convertToNum(str string) int {
	num, err := strconv.Atoi(str)
	if err != nil {
		log.Fatal(err)
	}

	return num
}

func mapCardsToRanks(input string) []rune {
	var card []rune

	for _, char := range input {
		if value, isMapContainsKey := rankMap[char]; isMapContainsKey {
			card = append(card, rune(value)) 
		}
	}
	return card
}

func compareSlices(slice1, slice2 []rune) bool {
	for i := 0; i < len(slice1) && i < len(slice2); i++ {
		if slice1[i] != slice2[i] {
			return slice1[i] < slice2[i]
		}
	}
	return len(slice1) < len(slice2)
}

func calculateRanks(category map[string]int, startRank int) (int, int) {
	counts := make(map[string][]rune)
	for key := range category {
		counts[key] = mapCardsToRanks(key)
	}
	keys := make([]string, 0, len(counts))
	for key := range counts {
		keys = append(keys, key)
	}
	sort.Slice(keys, func(i, j int) bool {
		return compareSlices(counts[keys[i]], counts[keys[j]])
	})
	sum := 0
	for _, k := range keys {
		val := category[k]
		val *= startRank
		sum += val
		startRank++
	}
	return sum, startRank
}

func (rec *Record) GetCards(line string) {
	values := strings.Split(line, " ")
	counted := duplicateCounter(values[0])
	var sum []int
	for _, count := range counted {
		if count > 1 {
			sum = append(sum, count)
		}
	}
	if len(sum) == 1 && sum[0] == 5 {
		rec.five[values[0]] = convertToNum((values[1]))
	} else if len(sum) == 1 && sum[0] == 4 {
		rec.four[values[0]] = convertToNum((values[1]))
	} else if len(sum) == 0 {
		rec.high[values[0]] = convertToNum((values[1]))
	} else if len(sum) == 1 && sum[0] == 2 {
			rec.one[values[0]] = convertToNum((values[1]))
	} else if len(sum) == 1  && sum[0] == 3 {
		rec.three[values[0]] = convertToNum((values[1]))
	} else if len(sum) > 1  {
		if (sum[0] == 3 && sum[1] == 2) || (sum[1] == 3 && sum[0] == 2) {
			rec.full[values[0]] = convertToNum((values[1]))
		} else if sum[0] == 2 && sum[1] == 2 {
			rec.two[values[0]] = convertToNum((values[1]))
		}
	}
}

func (rec Record) GetResult () {
	sum := 0
	rankFields := []map[string]int{rec.high, rec.one, rec.two, rec.three, rec.full, rec.four, rec.five}

	var result int
	nextRank := 1
	for _, field := range rankFields {
		result, nextRank = calculateRanks(field, nextRank )
		sum += result
	}
	fmt.Println("Result ", sum)
}


func main() {
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}
	scanner := bufio.NewScanner(file)
	rec := &Record {
		five: make(map[string]int),
		four: make(map[string]int),
		full: make(map[string]int),
		three: make(map[string]int),
		two: make(map[string]int),
		one: make(map[string]int),
		high: make(map[string]int),
	}
	for scanner.Scan() {
		line := scanner.Text()
		rec.GetCards(line)
	}
	rec.GetResult()
}