package main

import ("os"
		"log"
		"bufio"
		"fmt"
		"strings"
	 	"strconv")

var wordToNumber = map[string] string {
	"one": "1",
	"two": "2", 
	"three": "3",
	"four": "4",
	"five": "5",
	"six": "6",
	"seven": "7",
	"eight": "8",
	"nine": "9",
}
	
func findFirstMatch(word string, idx int) string {
	firstMatchedNumber := ""
	for key, value := range wordToNumber {
		valueMatch := strings.Index(word, value)
		keyMatch := strings.Index(word, key)
		
		if keyMatch != -1 && keyMatch < idx {
			idx = keyMatch
			firstMatchedNumber = value
		}
		if valueMatch != -1 && valueMatch < idx {
			idx = valueMatch
			firstMatchedNumber = value
		}
	}
	return firstMatchedNumber
}


func findLastMatch(word string) string {
	idx := 0
	lastMatchedNumber := ""
	for key, value := range wordToNumber {
		valueMatch := strings.LastIndex(word, value)
		keyMatch := strings.LastIndex(word, key)
		
		if keyMatch != -1 && keyMatch >= idx {
			idx = keyMatch
			lastMatchedNumber = value
		}
		if valueMatch != -1 && valueMatch >= idx {
			idx = valueMatch
			lastMatchedNumber = value
		}
	}
	return lastMatchedNumber
}

func main() {
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	sum := 0
	matchedNumbers := ""
	for scanner.Scan() {
		line := scanner.Text()
		if len(line) == 0 {
            break
        }
		matchedNumbers = findFirstMatch(line, len(line) + 1) + findLastMatch(line)
		num, err1 := strconv.Atoi(matchedNumbers)
		if err1 != nil {
			fmt.Println("Error ", err1)
			return
		}
		sum += num
    }
	fmt.Println("Result: ", sum)
}