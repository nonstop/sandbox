PHONY: all

all: search_c search_cc search_go

search_c: search.c
	gcc -Wall -g search.c -o search_c
search_cc: search.cc
	g++ -Wall -g search.cc -o search_cc
search_go: search.go
	go build -o search_go search.go
search_hs: search.hs
	echo lol
test:
	python test.py

clean:
	rm -f search search_c search_cc search_go
