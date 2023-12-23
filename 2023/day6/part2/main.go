package main 

import (
	"fmt"
	"log"
	"os"
	"bufio"
	"strings"
	"strconv"
)

type Record struct {
	time int
	distance int
}

func convertToNum(str string) int {
	num, err := strconv.Atoi(str)
	if err != nil {
		log.Fatal(err)
	}

	return num
}

func getNumber(str string) int {
	intValue := 0
	colonIndex := strings.Index(str, ":")
		if colonIndex != -1 {
			result := strings.TrimSpace(str[colonIndex+1:])
			values := strings.Join(strings.Fields(result), "")
			intValue = convertToNum(values)
			return intValue
	}
	return 0
}

func calculateNumberOfWays(time int) []int {
	var result []int
	for i := 0; i <= time; i++ {
		num := (time - i) * i
		result = append(result, num)
	}
	return result
}

func (rec *Record) GetNumbers(line string) {
	if strings.Contains(line, "Time:") {
		rec.time = getNumber(line)
	} else {
		rec.distance = getNumber(line)
	}
}


func (rec Record) GetResult () {
	counter := 0
	result := calculateNumberOfWays(rec.time)
	for _, num := range result {
		if num > rec.distance {
			counter++
		}
	}
	fmt.Println("Result ", counter)
}


func main() {
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}
	scanner := bufio.NewScanner(file)
	rec := &Record {
		time: 0,
		distance: 0,
	}
	
	for scanner.Scan() {
		line := scanner.Text()
		rec.GetNumbers(line)
	}
	rec.GetResult()
}