// test 7: tests deleting data

#include "Graph.h"

int main() {
	gdwg::Graph<std::string,int> g;
	
	// add this data into the graph
	g.addNode("a");
	g.addNode("b");
	g.addNode("c");
	g.addNode("d");
	
	g.addEdge("b","a",3);
	g.addEdge("b","a",5);
	g.addEdge("c","a",3);
	
	std::cout << "Graph before node/edge deletion" << std::endl;
	g.printNodes();
	g.printEdges("b");
	g.printEdges("c");
	
	std::cout << "deleteing edge between b and a" << std::endl;
	g.deleteEdge("b","a",5);
	/*
	g.printEdges("b");
	
	std::cout << "deleting node a" << std::endl;
	g.deleteNode("a");
	g.printEdges("b");
	std::cout << "Graph after node/edge deletion" << std::endl;
	g.printNodes();
	
	try {
		g.deleteNode("a");
	} catch( const std::exception &ex ) {
		std::cout << "exception caught 1" << std::endl;
	}
	
	try {
		g.deleteEdge("c","a",5);
	} catch( const std::exception &ex ) {
		std::cout << "exception caught 2" << std::endl;
	}
	*/
}
