// test for mergeReplace

#include "Graph.h"


int main() {
	
	// make a graph
	gdwg::Graph<unsigned int,std::string> g;
	
	g.addNode(1);
	g.addNode(2);
	g.addNode(3);
	g.addNode(4);

	g.addEdge(1,2,"1->2");
	g.addEdge(2,3,"2->3");
	g.addEdge(2,4,"2->4");
	g.addEdge(3,2,"3->2");
	g.addEdge(3,4,"3->4");
	g.addEdge(2,4,"cs6771");
	g.addEdge(3,4,"cs6771");

	std::cout << "Before calling mergReplace(2,3)" << std::endl;
	g.printEdges(1);
	g.printEdges(2);
	g.printEdges(3);
	g.printEdges(4);

	g.mergeReplace(2,3);

	std::cout << std::endl << "After calling mergReplace(2,3)" << std::endl;
	g.printEdges(1);
	std::cout << "checking that node 2 has been destroyed" << std::endl;
	try {
          g.printEdges(2);
	} catch( const std::exception &ex ) {
	   std::cout << "exception caught" << std::endl;
	}
	g.printEdges(3);
	g.printEdges(4);
}

