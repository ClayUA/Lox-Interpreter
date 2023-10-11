package main

import (
	"fmt"
)

type Token struct {
	Type    TokenType
	Lexeme  string
	Literal interface{}
	Line    int
}

func NewToken(ttype TokenType, lexeme string, literal interface{}, line int) Token {
	return Token{
		Type:    ttype,
		Lexeme:  lexeme,
		Literal: literal,
		Line:    line,
	}
}
func (t Token) String() string {
	return (fmt.Sprint(t.Type) + " " + t.Lexeme + " " + fmt.Sprint(t.Literal))

}
