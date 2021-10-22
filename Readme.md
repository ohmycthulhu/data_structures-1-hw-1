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

