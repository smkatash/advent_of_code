package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

type Key struct {
	node   string
	dac    bool
	fft    bool
}
var connections map[string][]string

const startDevice = "svr"
const targetDevice = "out"

func countPathsMemo(connections map[string][]string, node string, hasDAC, hasFFT bool, memo map[Key]int) int {
	if node == targetDevice {
		if hasDAC && hasFFT {
			return 1
		}
		return 0
	}

	key := Key{node, hasDAC, hasFFT}
	if v, ok := memo[key]; ok {
		return v
	}

	total := 0
	for _, next := range connections[node] {
		total += countPathsMemo(
			connections,
			next,
			hasDAC || next == "dac",
			hasFFT || next == "fft",
			memo,
		)
	}

	memo[key] = total
	return total
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
	memo := make(map[Key]int)
	count := countPathsMemo(connections, startDevice, false, false, memo)
	fmt.Println("Len:", count)
}
