# Mathematical Expression Parser

This program was written as a solution to Codewars "Evaluate Mathematical Expression" exercice, which you'll find [here](https://www.codewars.com/kata/52a78825cdfc2cfc87000005).

This program computes the result of an expression containing floating point numbers, additions, substractions, multiplications, divisions and negations.

Examples of valid expressions are:
- `3.24`
- `-(24 + 3 * 4.1)`
- `2 / 7 / 8`

## Usage

`./eval <expr>` prints the result of the expression
`./eval -p <expr>` prints the corresponding abstract syntax tree

## About parsing mathematical expressions

The algorithm for the parsing I used is called "recursive descent parsing".
Here is a link to the video which helped me understand how to go about this: [Recursive Descent Parsing - by hhp3](https://www.youtube.com/watch?v=SToUyjAsaFk&t=271s).

### Grammars

In this case, the concept of grammar can be very helpful.
A grammar is way of describing a formal language.
In computer science theory, a language is a set (which can be either finite or infinite) of words.
A word is a finite sequence of symbols.

The grammar of a language is a set of rules that allows us to produce all the words belonging to that language.

#### Examples

The following grammars are written in EBNF form. An article abut how to express grammars with the EBNF syntax can be found here:
[EBNF: How to describe the grammar of a language - by Federico Tomassetti](https://tomassetti.me/ebnf/)

An example of a grammar for a very simple language is:
```
word	: 'a' | x ;
x		: 'a' x | 'a' ;
```
This grammar describes the language consisting of all words in the form: `a`, `aa`, `aaa`, `aaaa`...
Note that this language is infinite.

An example of finite language could be:
```
word	: 'hello' | 'world' ;
```
This language only contains the words 'hello' and 'world'.

#### The grammar we will use

A grammar that describes the set of valid mathematical expressions can be expressed like this:
```
expr	: term {('+' | '-') term} ;

term	: factor {('*' | '/') factor} ;

factor	: FLOAT | '(' expr ')' | '-' factor ;
```

This grammar gives us three nice rules which we can translate into three functions.
