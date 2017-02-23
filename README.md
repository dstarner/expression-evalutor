## C Evaluation Expression

This calculator can take in valid mathematical expressions in 'infix notation' 
and evaluate their end values, 'post-fix' and 'pre-fix' notations and pipe them
to an output file of your choice.

It will follow valid precendence set forth by PEMDAS, so parentheses and
**'/'** and **'*'** precendence will be true. The calculator can also
take in valid Roman Numeral values, either in uppercase or lowercase. Invalid 
Roman Numerals will result in a failure.

To test and run this program, build it with `make`.

You can then run it by passing two parameters.

```bash
./main <input> <output>

# Example

./main input.txt output.txt
```

An example of the input file can be:
```
5 + (VII * iii) - 3
```

The output of the file will be such as below:

```
Prefix:  * -15 + 4 6
Postfix:  -15 4 6 + *
Value: -150
```
