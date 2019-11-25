package main
import (
	"fmt"
	"strconv"
	"os"
)

type Person struct{
	name string
	id int
}

var PersonMap = []Person {{"snow", 1}, {"zhu", 2}}


func findPersonById(id int) (name string, err error) {
	for _, p := range PersonMap {
		if p.id == id {
			name = p.name
			err = nil
			return
		}
	}

	err = fmt.Errorf("Not find")
	return 
}


func squares() func()int {
	var x int
	return func () int {
		x++
		return x*x
	}
}


func main() {

	id, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Println("id is invalid")
		return
	}

	var f func(id int) (name string, err error);
	f = findPersonById
	name, err := f(id)
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(name)

	ff := squares()
	fmt.Println(ff())
	fmt.Println(ff())
	fmt.Println(ff())
	fmt.Println(ff())

	return 
}