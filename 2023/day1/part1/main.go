package main

import ("os"
		"log"
		"bufio"
		"fmt"
		"regexp"
		"strconv")

func main() {
	fileName := os.Args[1]
	file, err := os.Open(fileName)
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	re := regexp.MustCompile(`\d`)
	scanner := bufio.NewScanner(file)
	sum := 0
	var combinedStrings string
	for scanner.Scan() {
		submatchNumber := re.FindAllString(scanner.Text(), -1)

		if (len(submatchNumber) == 1) {
			combinedStrings = submatchNumber[0] + submatchNumber[0]
		} else {
			combinedStrings = submatchNumber[0] + submatchNumber[len(submatchNumber) - 1]
		}
		num, err1 := strconv.Atoi(combinedStrings)
		if err1 != nil {
			fmt.Println("Error ", err1)
			return
		}
		sum += num
    }
	fmt.Println("Result: ", sum)
}