LEGAL INFORMATIONS

This is program for computing euler path in graph (if possible).
Copyright (c) 2011 by Nedeljko Stefanović


MIT License


Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
---------------------------------------------------------------------

COMPILING

Compiling is possible by most C++ compilers.
To compile by GNU compiler type

g++ -oeuler euler.cpp

---------------------------------------------------------------------

USAGE

From command line You can use it by typing

./euler input_files

On Windows systems prefix "./" is needless. Type

euler input_files

If no input file is specified, then program expects input graph
from standard input.

Input format is:
Number of vertices
Adjacency of the first vertex to all vertices.
Adjacency of the second vertex to all vertices but first.
...
Adjacency of the last vertex to itself.

Example of input for complete graph of three vertices is:

3
0 1 1
0 1
0

Do not forget spaces!

Output gives path by vertices numbers where numbers starting by 0.

Example of output for complete graph of three vertices is:

0
1
2

