// test 3: tests error handling

#include "Graph.h"

int main() {
	
	// create 3 graphs
	gdwg::Graph<int,int> g;
	gdwg::Graph<std::string,double> g2{};
	gdwg::Graph<std::shared_ptr<int>,std::string> g3{};
	
	// add some nodes to each graph. 
	g.addNode(1);
	int i = 2;
	g.addNode(i);
	double d = 3.41;
	g.addNode(static_cast<int>(d));
	
	g2.addNode("Hello");
	std::string s = "world";
	g2.addNode(s);
	
	std::shared_ptr<int> sp = std::make_shared<int>(5);
	g3.addNode(sp);
	g3.addNode(std::make_shared<int>(6));
	
	// try to add some duplicated data
	i = 1;
	std::cout << "testing adding duplicate data" << std::endl;
	std::cout << std::boolalpha << g.addNode(i) << std::endl;
	std::cout << g2.addNode("Hello") << std::endl;
	std::cout << g3.addNode(sp) << " " << g3.addNode(std::make_shared<int>(6)) << std::endl;
	
	// add some edges 
	g.addEdge(2,1,3);
	int j = 3;
	g.addEdge(i,j,1);
	g2.addEdge("Hello","world",d);
	
	std::cout << "testing adding duplicate edges" << std::endl;
	// try to add some duplicated edges
	std::cout << g.addEdge(2,1,3) << std::endl;
	// try to add an edge with a different weight
	std::cout << g.addEdge(2,1,2) << std::endl;
	
	std::cout << "testing adding edges between nodes not in the graph" << std::endl;
	// try to add an edge to somewhere not in the graph
	try {
		g.addEdge(7,1,3);
	} catch( const std::exception &ex ) {
		//std::cerr << ex.what() << std::endl;
		std::cout << "exception caught" << std::endl;
	}
	try {
		g.addEdge(2,7,3);
	} catch( const std::exception &ex ) {
		std::cout << "exception caught" << std::endl;
	}
	
	std::cout << "testing isConnected" << std::endl;
	try {
		std::cout << g2.isConnected("world","Hello") << std::endl;
		std::cout << g2.isConnected("hello","pluto") << std::endl;
	} catch( const std::exception &ex ) {
		std::cout << "exception caught" << std::endl;
	}
	
	std::cout << "testing print with an unknown node" << std::endl;
	try {
		g.printEdges(5);
	} catch( const std::exception &ex ) {
		std::cout << "exception caught" << std::endl;
	}

}
