package main 
import (
	"fmt"
	"os"
	"log"
	"bufio"
	"strings"
	"strconv"
)

func min(a, b int) int {
	if a == 0 {
		return b
	}
	if a >= b {
		return b
	}
	return a
}

func convertToNum(str string) int {
	num, err := strconv.Atoi(str)
	if err != nil {
		log.Fatal(err)
	}

	return num
}

func mapTheNumbers(line string, currentMap map[int]int) {
	values := strings.Split(line, " ")
	dest :=  convertToNum(values[0])
	src := convertToNum(values[1])
	rangeS := convertToNum(values[2])
	for i := 0; i < rangeS; i++ {
		currentMap[src + i] = dest + i
	}
}

func getSeeds(line string) []int {
	colonIndex := strings.Index(line, ":")
	if colonIndex != -1 {
		result := strings.TrimSpace(line[colonIndex+1:])
		values := strings.Split(result, " ")
		intValues := make([]int, len(values))
		for x := range values {
			intValues[x] = convertToNum(values[x])
		}
		return intValues
	}
	return nil
}

func checkAssignment(num, alt int) int {
	if num != 0 {
		return num
	}
	return alt
}

func main() {
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}
	scanner := bufio.NewScanner(file)
	seedToSoil := make(map[int]int)
	soilToFert := make(map[int]int)
	fertToWater := make(map[int]int)
	waterToLight := make(map[int]int)
	lightToTemp := make(map[int]int)
	tempToHumidity := make(map[int]int)
	humidityToLocation := make(map[int]int)
	var currentMap map[int]int
	var seeds []int

	for scanner.Scan() {
		line := scanner.Text()
		if len(line) == 0 {
			continue
		}

		if strings.Contains(line, "seeds:"){
			seeds = getSeeds(line)
			fmt.Println(seeds)
			continue
		}

		switch line {
		case "seed-to-soil map:":
			currentMap = seedToSoil
			continue
		case "soil-to-fertilizer map:":
			currentMap = soilToFert
			continue
		case "fertilizer-to-water map:":
			currentMap = fertToWater
			continue
		case "water-to-light map:":
			currentMap = waterToLight
			continue
		case "light-to-temperature map:":
			currentMap = lightToTemp
			continue
		case "temperature-to-humidity map:":
			currentMap = tempToHumidity
			continue
		case "humidity-to-location map:":
			currentMap = humidityToLocation
			continue
		}
		mapTheNumbers(line, currentMap)
	}
	
	arrayOfMaps := make([]map[int]int, 7)
	arrayOfMaps[0] = seedToSoil
    arrayOfMaps[1] = soilToFert
    arrayOfMaps[2] = fertToWater
    arrayOfMaps[3] = waterToLight
    arrayOfMaps[4] = lightToTemp
    arrayOfMaps[5] = tempToHumidity
    arrayOfMaps[6] = humidityToLocation
	var current int
	var next int
	minLocation := 0
	for x := range seeds {
		fmt.Println("--------------------")
		seed := seeds[x]
		fmt.Println(seed)
		current = seed
		for i := 0; i <= 6; i++ {
			currentMap := arrayOfMaps[i]
			next = checkAssignment(currentMap[current], current)
			fmt.Println("Value ", next)
			current = next
		}
		minLocation = min(minLocation, current)
	}

	fmt.Println(minLocation)

}