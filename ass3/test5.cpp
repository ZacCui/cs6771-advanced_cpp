// test 5: tests replace data

#include "Graph.h"

int main() {
	gdwg::Graph<std::string,int> gCopy;
	
	// create some data to store as nodes.
	std::string s = "a";
	std::string t = "b";
	std::string u = "c";
	
	// add this data into the graph
	gCopy.addNode(s);
	gCopy.addNode(t);
	gCopy.addNode(u);
	
	gCopy.addEdge(u,t,1);
	gCopy.addEdge(u,t,2);
	
	std::cout << "Graph before node replacement" << std::endl;
	gCopy.printNodes();
	
	// replace node
	gCopy.replace("a","e");
	std::cout << "Graph after node replacement" << std::endl;
	gCopy.printNodes();
	
	std::cout << "trying to replace node with an existing node" << std::endl;
	std::cout << std::boolalpha << gCopy.replace("b","c") << std::endl;
	
	std::cout << "trying to replace node with a node not in the graph" << std::endl;
	try {
		gCopy.replace("a","d");
	} catch( const std::exception &ex ) {
		//std::cerr << ex.what() << std::endl;
		std::cout << "exception caught" << std::endl;
	}
}
