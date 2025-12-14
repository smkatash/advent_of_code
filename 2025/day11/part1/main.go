package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

var connections map[string][]string

const startDevice = "you"
const targetDevice = "out"

func collectPaths(connections map[string][]string, start string) [][]string {
	queue := [][]string{{start}}
	var results [][]string

	for len(queue) > 0 {
		path := queue[0]
		queue = queue[1:]

		current := path[len(path)-1]

		for _, next := range connections[current] {
			if next == targetDevice {
				complete := append([]string{}, path...)
				complete = append(complete, targetDevice)
				results = append(results, complete)
				continue
			}

			skip := false
			for _, p := range path {
				if p == next {
					skip = true
					break
				}
			}
			if skip {
				continue
			}

			newPath := append([]string{}, path...)
			newPath = append(newPath, next)
			queue = append(queue, newPath)
		}
	}
	return results
}

func main() {
	fileName := os.Args[1]
	file, err := os.Open(fileName)
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	connections = make(map[string][]string)
	for scanner.Scan() {
		line := scanner.Text()
		devices := strings.Split(line, " ")
		connections[strings.Trim(devices[0], ":")] = devices[1:]
	}
	paths := collectPaths(connections, startDevice)
	fmt.Println("Len:", len(paths))
}
