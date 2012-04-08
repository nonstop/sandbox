package main

import (
    "os"
    "fmt"
    "strconv"
)

func search(str string, k int, c byte) int {
    l, j := 0, 0
    indexes := make([]int, k)
    for i := 0; i < len(str); i++ {
        if str[i] != c {
            continue
        }
        end := j % k
        start := 0
        if end < (k - 1) {
            start = end + 1
        } else {
            start = end - k +1
        }
        indexes[end] = i
        d := indexes[end] - indexes[start]
        if j < k {
            l = d
        } else if l > d {
            l = d
        }
        j++
    }
    if j < k {
        l = -1
    }
    return l + 1
}

func main() {
    if len(os.Args) < 3 {
        os.Exit(1)
    }
    var k, err = strconv.Atoi(os.Args[1])
    if err != nil {
        os.Exit(2)
    }
    fmt.Println(search(os.Args[2], k, '1'))
}
