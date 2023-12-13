package main 
import (
	"fmt"
	"os"
	"log"
	"bufio"
	"strings"
	"strconv"
	"sync"
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

func getSeeds(line string) map[int]int {
	colonIndex := strings.Index(line, ":")
	if colonIndex != -1 {
		result := strings.TrimSpace(line[colonIndex+1:])
		values := strings.Split(result, " ")
		seedMap := make(map[int]int)
		for x := 0; x < len(values); x += 2 {
			seed := convertToNum(values[x])
			rangeS := convertToNum(values[x+1])
			seedMap[seed] = rangeS
		}
		return seedMap
	}
	return nil
}

func inRange(x, min, max int) bool {
    return x >= min && x <= max
}

func checkAssignment(currentMap []Item, seed int, wg *sync.WaitGroup, resultChan chan int) {
	defer wg.Done()

	for _, item := range currentMap {
		if inRange(seed, item.src, item.src + item.rangeS) {
			resultChan <- item.dest + (seed - item.src)
			return
		}
	}
	resultChan <- seed
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
	var seeds map[int]int

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

	minLocation := 0
	resultChan := make(chan int, len(seeds))
	var mu sync.Mutex
	var wg sync.WaitGroup
	for key, value := range seeds {
		fmt.Println(key, "--", value)
		wg.Add(1)
		go func(seed, value int) {
			defer wg.Done()
			for i := 0; i < value; i++ {
				current := seed + i
				fmt.Println(value, "-", i)
				fmt.Println(current, " and ", seed +i)
				for j := 0; j <= 6; j++ {
					wg.Add(1)
					go func(currentMap []Item, current int) {
						defer wg.Done()
						checkAssignment(currentMap, current, &wg, resultChan)
					}(arrayOfMaps[j], current) 
					current = <-resultChan
					fmt.Println(current)
				}
				mu.Lock()
				minLocation = min(minLocation, current)
				mu.Unlock()
			}
		}(key, value)
	}

	go func() {
		wg.Wait()
		close(resultChan)
	}()

	for result := range resultChan {
		fmt.Printf("Processed result: %d\n", result)
	}

	fmt.Println("Result ", minLocation)

}