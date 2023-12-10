package main

import (
	"os"
	"fmt"
	"log"
	"bufio"
	"strings"
	"unicode"
)

func isEmptyOrWhitespace(s string) bool {
	trimmed := strings.TrimSpace(s)
	return len(trimmed) == 0
}

func contains(slice []string, element string) bool {
	for _, e := range slice {
		if strings.EqualFold(e, element) {
			return true
		}
	}
	return false
}

func compareNumbers(winningNumbers []string, myNumbers []string) int {
	match := 0
	for _, num := range myNumbers {
		if !isEmptyOrWhitespace(num) && contains(winningNumbers, num) {
			match++
		}
	}
	return match
}

func extractNumbers(set string, cards []string) []string {
	var str []rune
	
	for _, w := range set {
		if unicode.IsSpace(w) && len(str) != 0 {
			cards = append(cards, strings.ReplaceAll(string(str), " ", ""))
			str = nil
		}
		str = append(str, w)
	}

	if len(str) != 0 {
		cards = append(cards, strings.ReplaceAll(string(str), " ", ""))
	}

	return cards
}

func calculatePoints(matches int) int {
	if matches <= 1 {
		return matches
	}
	
	currentP := 1
	for i := 2; i <= matches; i++ {
        currentP *= 2
    }
	return currentP
}

func main() {
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}
	scanner := bufio.NewScanner(file)
	sum := 0
	var winningNumbers []string
	var myNumbers []string

	for scanner.Scan() {
		line := scanner.Text()
		if len(line) == 0 {
			break
		}
		colonIndex := strings.Index(line, ":")
		if colonIndex != -1 {
			result := strings.TrimSpace(line[colonIndex+1:])
			splitCards := strings.Split(result, "|")
			winningNumbers = extractNumbers(splitCards[0], winningNumbers)
			myNumbers = extractNumbers(splitCards[1], myNumbers)
			matches := compareNumbers(winningNumbers, myNumbers)
			sum += calculatePoints(matches)
			winningNumbers = nil
			myNumbers = nil
		}
	}
	fmt.Println("Result ", sum)
}