package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

var counter int

func rotateLeft(steps int) {
	if counter-steps < 0 {
		counter = 100 - (steps - counter)
		if counter < 0 {
			counter = 100 + counter
		}
	} else if counter == 0 {
		counter = 99 - (steps - 1)
		if counter < 0 {
			counter = 100 + counter
		}
	} else {
		counter -= steps
	}
}

func rotateRight(steps int) {
	if (counter + steps) >= 100 {
		counter = (counter + steps) - 100
	} else {
		counter += steps
	}
}

func main() {	
	fileName := os.Args[1]
	file, err := os.Open(fileName)
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	counter = 50
	sum := 0
	for scanner.Scan() {
		line := scanner.Text()
		direction := line[0:1]
		stepsString := line[1:]
		steps, err := strconv.Atoi(stepsString)
		if (steps > 100) {
			steps = steps % 100
		}
		if err != nil {
			log.Fatal(err)
		}
		switch direction {
		case "L":
			rotateLeft(steps)
		case "R":
			rotateRight(steps)
		default:
			log.Fatal("Unknown direction")
		}
		if (counter == 0) {
			sum += 1
		}
	}

	fmt.Println("Sum: ", sum)
}