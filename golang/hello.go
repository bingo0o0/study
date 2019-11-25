package main

import  "fmt"

func zero(ptr *[32]int) {
	*ptr = [32]int {}
}

func main() {
	var a [3]int = [...]int {1, 2, 3}
	fmt.Println(a[0])

	for i,v := range a {
		fmt.Println(i,v)
	}

	ss := a[:2]
	fmt.Println(ss)
	ss[0] = 6
	fmt.Println(a)

	var ss1 []int = make([]int, 3)
	copy(ss1, ss)
	fmt.Println(ss1)
	ss1 = append(ss1, 33)
	fmt.Println(ss1)

	ages := map[string]int {
		"alice" : 30,
	}

	fmt.Println(ages["alice"])
	age,ok := ages["snow"]
	if !ok {
		fmt.Println("###", age)
	}

	age,ok = ages["snow"]
	if ok {
		fmt.Println("###", age)
	}
}
