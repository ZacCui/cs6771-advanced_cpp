// test 9: tests move assignment

#include "Graph.h"

int main() {
	auto gHeap = new gdwg::Graph<std::string,int>{};
	
	// add this data into the graph
	gHeap->addNode("a");
	gHeap->addNode("b");
	gHeap->addNode("c");
	gHeap->addNode("d");
	
	gHeap->addEdge("b","a",3);
	gHeap->addEdge("b","a",5);
	gHeap->addEdge("c","a",3);
	
	std::cout << "original graph" << std::endl;
	gHeap->printNodes();
	gHeap->printEdges("b");
	
	gdwg::Graph<std::string,int> gHeapCopy;
	gHeapCopy.addNode("z");
	std::cout << "Graph before copy assignment" << std::endl;
	gHeapCopy.printNodes();
	
	gHeapCopy = std::move(*gHeap);	// move assignment

	// We shouldn't use a moved-from object, in general.
	// However, here, for testing purposes, we assumed
	// a moved-from graph is an empty graph.
	std::cout << "moved-from graph (expected to be empty)" << std::endl;
	gHeap->printNodes();
	delete gHeap;

	std::cout << "moved-to graph" << std::endl;
	gHeapCopy.printNodes();
	gHeapCopy.printEdges("b");
	
}
