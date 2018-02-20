/*****************************************************************************
*                                                                            *
*    This is program for computing euler path in graph (if possible).        *
*    Copyright (c) 2011 by Nedeljko Stefanović                               *
*                                                                            *
*    MIT License                                                             *
*                                                                            *
*    Permission is hereby granted, free of charge, to any person             *
*    obtaining a copy of this software and associated documentation files    *
*    (the "Software"), to deal in the Software without restriction,          *
*    including without limitation the rights to use, copy, modify, merge,    *
*    publish, distribute, sublicense, and/or sell copies of the Software,    *
*    and to permit persons to whom the Software is furnished to do so,       *
*    subject to the following conditions:                                    *
*                                                                            *
*    The above copyright notice and this permission notice shall be          *
*    included in all copies or substantial portions of the Software.         *
*                                                                            *
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,         *
*    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF      *
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                   *
*    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS     *
*    BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN      *
*    ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN       *
*    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE        *
*    SOFTWARE.                                                               *
*                                                                            *
*****************************************************************************/

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <list>
#ifndef __USE_GNU
#include <malloc.h>
#endif

using namespace std;

class Graph {
	typedef bool *PBOOL;

	bool *buffer;
	PBOOL *adj;
	int order;

	virtual void create(int order = 0) {
		this->order = order;
		
		if (order == 0) {
			buffer = 0;
			adj = 0;

			return;
		}

		buffer = new bool[order*(order + 1)/2];
		adj = new PBOOL[order];

		for (int i = 0; i < order; ++i) {
			adj[i] = buffer + i*(2*order - i + 1)/2;
		}
	}

	virtual void clear() {
		delete [] buffer;
		delete [] adj;
		buffer = 0;
		adj = 0;
		order = 0;
	}

	virtual void copy(const Graph &object) {
		int order2 = object.order*(object.order + 1)/2;

		Graph::create(object.order);

		for (int i = 0; i < order2; ++i) {
			buffer[i] = object.buffer[i];
		}
	}

public:
	Graph() {
		create();
	}

	Graph(const Graph &object) {
		Graph::copy(object);
	}

	~Graph() {
		Graph::clear();
	}

	Graph& operator=(const Graph &object) {
		if (this == &object) {
			return *this;
		}

		clear();
		copy(object);

		return *this;
	}

	bool operator==(const Graph &object) const {
		if (order != object.order) {
			return false;
		}

		if (order == 0) {
			return true;
		}

		int order2 = order*(order + 1)/2;

		for (int i = 0; i < order2; ++i) {
			if (buffer[i] != object.buffer[i]) {
				return false;
			}
		}

		return true;
	}

	bool operator!=(const Graph &object) const {
		return !operator==(object);
	}

	bool operator()(int i, int j) const {
		int order2 = order*(order + 1)/2;

		if (i > j) {
			return adj[j][i - j];
		}

		return adj[i][j - i];
	}

	bool& operator()(int i, int j) {
		int order2 = order*(order + 1)/2;

		if (i > j) {
			return adj[j][i - j];
		}

		return adj[i][j - i];
	}

	void get(istream &istr = cin) {
		istr >> order;
		Graph::create(order);

		int order2 = order*(order + 1)/2;

		for (int i = 0; i < order2; ++i) {
			istr >> buffer[i];
		}
	}

	void put(ostream &ostr = cout) const {
		ostr << order << "\n";

		for (int i = 0; i < order; ++i) {
			for (int j = i; j < order; ++j) {
				ostr << " " << operator()(i, j);
			}

			ostr << "\n";
		}
	}

	int nodeDegree(int n) const {
		int counter = 0;

		for (int i = 0; i < order; ++i) {
			if (operator()(n, i)) {
				++counter;

				if (n == i) {
					++counter;
				}
			}
		}

		return counter;
	}

	bool connected() const {
		if (order == 0) {
			return true;
		}

		Graph other(*this);

		for (int i = 0; i < order; ++i) {
			if (nodeDegree(i) > 0) {
				other(i, i) = true;
			}
		}

		bool stop = false;

		while(stop == false) {
			stop = true;

			for (int i = 0; i < order; ++i) {
				for (int j = i + 1; j < order; ++j) {
					if (other(i, j) == false) {
						for (int k = 0; k < order; ++k) {
							if (other(i, k) && other(k, j)) {
								stop = false;
								other(i, j) = true;

								break;
							}
						}
					}
				}
			}
		}

#ifdef __USE_GNU
		bool excludedNode[order];
#else
                bool *excludedNode = (bool*)alloca(order*sizeof(bool));
#endif
		for (int i = 0; i < order; ++i) {
			excludedNode[i] = true;

			for (int j = 0; j <= i; ++j) {
				if (other(i, j)) {
					excludedNode[i] = false;

					break;
				}
			}

			if (excludedNode[i]) {
				continue;
			}

			for (int j = 0; j <= i; ++j) {
				if (excludedNode[j] == false && other(i, j) == false) {
					return false;
				}
			}
		}

		return true;
	}

	bool empty() const {
		int order2 = order*(order + 1)/2;

		for (int i = 0; i < order2; ++i) {
			if (buffer[i]) {
				return false;
			}
		}

		return true;
	}

	int nodes() const {
		return order;
	}

	bool eulerPath(list<int> &path) const {
		if (connected() == false) {
			return false;
		}

		if (empty()) {
			path.clear();

			return true;
		}

		int oddNodes = 0;
		int startNode = 0;

		for (int i = 0; i < order; ++i) {
			if (nodeDegree(i)%2 == 1) {
				++oddNodes;
				startNode = i;

				if (oddNodes > 2) {
					return false;
				}
			}
		}

		if (oddNodes == 1) {
			return false;
		}

		path.clear();
		path.push_back(startNode);

		int &currentNode = startNode;
		Graph other(*this);
		int i;

		do {
			for (i = 0; i < order; ++i) {
				if (other(i, currentNode)) {
					bool loop = other(i, i);
					
					other(i, currentNode) = false;

					if (currentNode != i) {
						other(i, i) = true;
					}

					bool isConnected = other.connected();

					other(i, i) = loop;

					if (isConnected) {
						other(i, i) = false;
						other(i, currentNode) = false;
						currentNode = i;
						path.push_back(currentNode);

						break;
					} else {
						other(i, currentNode) = true;
					}
				}
			}
		} while(i < order);

		return true;
	}
};

istream& operator>>(istream &istr, Graph &object) {
	object.get(istr);
	
	return istr;
}

ostream& operator<<(ostream &ostr, const Graph &object) {
	object.put(ostr);

	return ostr;
}

void processGraph(Graph g)
{
    list<int> path;
    
    if (g.eulerPath(path)) {
            cout << "Euler path is:\n" << endl;

            for (list<int>::const_iterator i = path.begin(); i != path.end(); ++i) {
                    cout << *i << endl;
            }
    } else {
            cout << "This is not euler graph.\n" << endl;
    }
}

int main(int argc, char* argv[]) {    
    cout <<
        "This is program for computing euler path in graph (if possible).\n"
        "Copyright (C) 2011 Nedeljko Stefanovic.\n"
        "\n"
        "GNU All-Permissive License\n"                                                                          
        "\n"
        "Copying and distribution of this file, with or without modification,\n"
        "are permitted in any medium without royalty provided the copyright\n"
        "notice and this notice are preserved.  This file is offered as-is,\n"
        "without any warranty.\n"
        "\n"
        "Input format is:\n"
        "Number of vertices\n"
        "Adjacency of the first vertex to all vertices.\n"
        "Adjacency of the second vertex to all vertices but first.\n"
        "...\n"
        "Adjacency of the second vertex to itself.\n"
        "\n"
        "Example of input for complete graph of three vertices is:\n"
        "\n"
        "3\n"
        "0 1 1\n"
        "0 1\n"
        "0\n"
        "\n"
        "Do not forget spaces!\n"
        "\n"
        "Output gives path by vertices numbers where numbers starting by 0.\n"
        "\n"
        "Example of output for complete graph of three vertices is:\n"
        "\n"
        "0\n"
        "1\n"
        "2\n"
        << endl;
    
    if (argc==1) {
        Graph g;

        cout << "Еnter the graph:" << endl;
        cin >> g;
        processGraph(g);
    } else {
        for (int i=1; i<argc; ++i) {
            ifstream in(argv[i]);
            
            if (in) {
                cout << "Processing file \"" << argv[i] << "\"" << endl;
                
                Graph g;

                in >> g;
                processGraph(g);
            } else {
                cout << "Can't read from file \"" << argv[i] << "\"" << endl;
            }
        }
    }

    return EXIT_SUCCESS;
}
