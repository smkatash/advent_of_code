package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

type ID struct {
	firstId int
	secondId int
}

func isRepeated(id string) bool {
    len := len(id)
    if len % 2 != 0 {
        return false
    }

    for size := 1; size <= len/2; size++ {
        if len%size != 0 {
            continue
        }
        unit := id[:size]
        repeats := len / size
        if repeats % 2 != 0 {
            continue
        }

        ok := true
        for i := size; i < len; i += size {
            if id[i:i+size] != unit {
                ok = false
                break
            }
        }

        if ok {
            return true
        }
    }

    return false
}

func findRepeatedSequence(ids ID) int {
	sum := 0
	for i:= ids.firstId; i <= ids.secondId; i++ {
		idStr := strconv.Itoa(i)
		if isRepeated(idStr) {
			fmt.Println("Found repeated sequence in ID: ", i)
			sum += i
		}
	}
	return sum
}



func main() {	
	fileName := os.Args[1]
	file, err := os.Open(fileName)
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	ids := []ID{}
	sum := 0
	counter := 0
	var allIdCombinations []string
	for scanner.Scan() {
		line := scanner.Text()
		allIdCombinations = strings.Split(line, ",")
		for _, combination := range allIdCombinations {
			idCombination := strings.Split(combination, "-")
			id := ID{}
			id.firstId, err = strconv.Atoi(idCombination[0])
			if err != nil {
				log.Fatal(err)
			}
			id.secondId, err = strconv.Atoi(idCombination[1])
			if err != nil {
				log.Fatal(err)
			}
			ids = append(ids, id)
		}
		for _, id := range ids {
			counter = findRepeatedSequence(id)
			//fmt.Println("Combination of first ", id.firstId, " and second ", id.secondId)
			sum += counter
			//fmt.Println("Current sum is ", sum)
		}
	}

	fmt.Println("Sum is ", sum)
}
