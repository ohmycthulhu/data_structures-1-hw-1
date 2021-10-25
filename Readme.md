# Programming 1 | Homework #1

## Description

<p>
The project is created to fulfill the requirements
of homework #1. It's written in C with the usage of Makefile
for compilation.
</p>
<p>
    The project consists of 5 parts that can be grouped in 2 groups:
</p>
<ol>
    <li>
        Printing the value from table:
        <ul>
            <li>Normal distribution</li>
            <li>Binomial distribution</li>
            <li>T distribution</li>
            <li>Chi-square distribution</li>
            <li>F distribution</li>
        </ul>
    </li>
    <li>
        Generating the table:
        <ul>
            <li>Student's T distribution</li>
            <li>Chi-square distribution</li>
            <li>F distribution</li>
        </ul>
    </li>
</ol>
<p>
    The first group receives the indices as an argument and returns
    the value from table.
</p>
<p>
    The second group receives parameters for table,
    generates the table, and returns the content and path of the file.
    This part doesn't work properly.
</p>
<p>
</p>

## Usage
<p>
    Keywords for distributions:
</p>
<table>
<tr>
    <th>Keyword</th>
    <th>Distribution</th>
</tr>
<tr>
    <td>main</td>
    <td>Main UI for using getting table values</td>
</tr>
<tr>
    <td>student</td>
    <td>Student's t distribution</td>
</tr>
<tr>
    <td>chi</td>
    <td>Chi-square distribution</td>
</tr>
<tr>
    <td>f_distribution</td>
    <td>F distribution</td>
</tr>
</table>

For compilation can be used keyword `all` that 
will generate binaries for all distributions.

    make $KEYWORD

where $KEYWORD is an available keyword

## Testing

There are also two programs for testing the implementation of library. 
They are called `distribution_test` and `math_test`.
For compiling all tests, you can use `tests`.

## Generating values

There are python scripts for generating some of tables.
The usage can be found in `generate_tables.sh`.

    bash generate_tables.sh


## Usage

### Normal distribution:

- At "[Input]: Insert the index to find:" you input number as "degree of freedom" + "alpha", so for finding the value at 7, 0.25 you enter 7.25.
- Get the result ("[Result] Value is 0.993960" for 2.51)

### T Distribution, Chi distribution:

- At "[Input]: Input degree of freedom:" input df
- At "[Input]: Input alpha:" input alpha
- Get the result ("[Result] Value is 0.267181" for t distribution and 5, 0.4)

### Binomial distribution:

- At "[Input]: Input iteration number: " input the number n (5, 10, etc.).
- At "[Input] Input p: " you enter value of p.
- At "[Input] Input x: " you enter value of n.
- Get the result ("[Result] Value is 0.672320" for 3, 0.8, 4)

[Input] Input p: 3
[Error] Value is not supported
[Info] Available values:
0.100000, 0.200000, 0.250000, 0.300000, 0.400000, 0.500000, 0.600000, 0.700000, 0.750000, 0.800000, 0.900000
[Input] Input p: 0.8
[Input] Input x: 4
[Result] Value is 0.672320

### F distribution:

- At "[Input]: Input iteration number:" input index of alpha.
- Input the first degree of freedom at "[Input] Input df1:"
- Input the second degree of freedom at "[Input] Input df2: "
- Get the result ("[Result] Value is 3.619477" for 1, 3, 5)

### Alpha values table

<table>
    <tr>
        <th>Index</th>
        <th>Alpha</th>
    </tr>
    <tr>
        <td>1</td>
        <td>0.1</td>
    </tr>
    <tr>
        <td>2</td>
        <td>0.05</td>
    </tr>
    <tr>
        <td>3</td>
        <td>0.01</td>
    </tr>
    <tr>
        <td>4</td>
        <td>0.005</td>
    </tr>
    <tr>
        <td>5</td>
        <td>0.001</td>
    </tr>
    <tr>
        <td>6</td>
        <td>0.0005</td>
    </tr>
    <tr>
        <td>7</td>
        <td>0.0001</td>
    </tr>
</table>