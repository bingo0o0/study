package main

import "fmt"

func main() {
	fmt.Println("test")

	persons  := [...]string {"snow", "abc", "asd"}
	subPer := persons[:2]
	fmt.Println(subPer)
	
	fmt.Println(len(subPer), cap(subPer))
	subPer = append(subPer, "vbn", "bfe")
	fmt.Println(len(subPer), cap(subPer))

	aliasPer := make([]string, 10)
	copy(aliasPer, subPer)
	fmt.Println(aliasPer)

	var runes []rune
	for _,r := range "hello, 世界" {
		runes = append(runes, r)
	}

	fmt.Printf("%q\n", runes)
}