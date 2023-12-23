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
	time []int
	distance []int
}

func convertToNum(str string) int {
	num, err := strconv.Atoi(str)
	if err != nil {
		log.Fatal(err)
	}

	return num
}

func getNumbers(str string) []int {
	var intValues []int
	colonIndex := strings.Index(str, ":")
		if colonIndex != -1 {
			result := strings.TrimSpace(str[colonIndex+1:])
			values := strings.Split(result, " ")
			for _, val := range values {
				if val != "" && val != " " {
					intValues = append(intValues, convertToNum(val))
				}
			}
			return intValues
	}
	return nil
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
		rec.time = getNumbers(line)
	} else {
		rec.distance = getNumbers(line)
	}
}


func (rec Record) GetResult () {
	numOfWays := 1
	counter := 0
	for i, time := range rec.time {
		result := calculateNumberOfWays(time)
		for _, num := range result {
			if num > rec.distance[i] {
				counter++
			}
		}
		numOfWays *= counter
		counter = 0
	}
	fmt.Println("Result ", numOfWays)
}


func main() {
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}
	scanner := bufio.NewScanner(file)
	rec := &Record {
		time: nil,
		distance: nil,
	}
	
	for scanner.Scan() {
		line := scanner.Text()
		rec.GetNumbers(line)
	}
	rec.GetResult()
}