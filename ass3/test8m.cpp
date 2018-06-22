// test 8: tests move construction

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
	gHeap->addEdge("b","d",4);
	gHeap->addEdge("c","a",3);
	
	std::cout << "original graph" << std::endl;
	gHeap->printNodes();
	gHeap->printEdges("b");
	
	auto gHeapCopy = std::move(*gHeap);
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
