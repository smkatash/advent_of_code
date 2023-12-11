package main 
import (
	"fmt"
	"os"
	"log"
	"bufio"
	"strings"
	"strconv"
)

type Item struct {
    dest, src, rangeS int
}

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

func mapTheNumbers(line string, currentMap *[]Item) {
	values := strings.Split(line, " ")
	item := Item{
		dest:  convertToNum(values[0]),
		src:   convertToNum(values[1]),
		rangeS: convertToNum(values[2]),
	}
	*currentMap = append(*currentMap, item)
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

func inRange(x, min, max int) bool {
    return x >= min && x <= max
}

func checkAssignment(currentMap []Item, seed int) int {
	for _, item := range currentMap {
		if inRange(seed, item.src, item.src + item.rangeS) {
			return item.dest + (seed - item.src)
		}
	}
	return seed
}

func main() {
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}
	scanner := bufio.NewScanner(file)
	var seedToSoil []Item
	var soilToFert []Item
	var fertToWater []Item
	var waterToLight []Item
	var lightToTemp []Item
	var tempToHumidity []Item
	var humidityToLocation []Item
	var currentMap *[]Item
	var seeds []int

	for scanner.Scan() {
		line := scanner.Text()
		if len(line) == 0 {
			continue
		}

		if strings.Contains(line, "seeds:"){
			seeds = getSeeds(line)
			continue
		}

		switch line {
		case "seed-to-soil map:":
			currentMap = &seedToSoil
			continue
		case "soil-to-fertilizer map:":
			currentMap = &soilToFert
			continue
		case "fertilizer-to-water map:":
			currentMap = &fertToWater
			continue
		case "water-to-light map:":
			currentMap = &waterToLight
			continue
		case "light-to-temperature map:":
			currentMap = &lightToTemp
			continue
		case "temperature-to-humidity map:":
			currentMap = &tempToHumidity
			continue
		case "humidity-to-location map:":
			currentMap = &humidityToLocation
			continue
		}
		mapTheNumbers(line, currentMap)
	}
	
	arrayOfMaps := make([][]Item, 7)
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
		seed := seeds[x]
		current = seed
		for i := 0; i <= 6; i++ {
			next = checkAssignment(arrayOfMaps[i], current)
			current = next
		}
		minLocation = min(minLocation, current)
	}

	fmt.Println("Result ", minLocation)

}