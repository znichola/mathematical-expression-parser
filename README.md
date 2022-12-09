# Mathematical Expression Parser

This program was written as a solution to Codewars "Evaluate Mathematical Expression" exercice, which you'll find [here](https://www.codewars.com/kata/52a78825cdfc2cfc87000005).

This program computes the result of an expression containing floating point numbers, additions, substractions, multiplications, divisions and negations.

Examples of valid expressions are:
- `3.24`
- `-(24 + 3 * 4.1)`
- `2 / 7 / 8`

The algorithm for the parsing I used is called "recursive descent parsing".
Here is a link to the video which helped me understand how to go about this: [Recursive Descent Parsing - hhp3](https://www.youtube.com/watch?v=SToUyjAsaFk&t=271s).

In this case, the concept of grammar can be very helpful.
A grammar is way of describing a formal language.
In computer science theory, a language is a set (which can be either finite or infinite) of words.
A word is a finite sequence of symbols.

The grammar of a language is a set of rules that allows us to produce all the words belonging to that language.

An example of a grammar is:
```
S->a
a->aa
```
This is a grammar that describes the language consisting of words in the form `a`, `aa`, `aaa`, `aaaa`...

A grammar that describes the set of valid mathematical expressions can be expressed like this:
```
E -> T + E
E -> T - E
E -> T
T -> F * T
T -> F / T
T -> F
F -> floating point number
F -> (E)
F -> -F
```
Which can be re-written as:
```
E -> T {+|- T}
T -> F {*|/ F}
F -> (E) | -F | floating point number
```
Which gives us three nice rules which we can elegantly translate into 3 functions.
