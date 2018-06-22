// test 8: tests copy construction

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
	
	auto gHeapCopy = *gHeap;
	gHeap->deleteNode("a");
	std::cout << "original graph after delete" << std::endl;
	gHeap->printNodes();
	gHeap->printEdges("b");
	std::cout << "copied graph after delete in other graph" << std::endl;
	gHeapCopy.printNodes();
	gHeapCopy.printEdges("b");
	
	delete gHeap;
	std::cout << "copied graph after other graph is deleted" << std::endl;
	gHeapCopy.printNodes();
}
