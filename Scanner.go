package main

type Scanner struct {
	Source string
	Tokens []Token
}

func NewScanner(src string) Scanner {
	return Scanner{
		Source: src,
	}
}
