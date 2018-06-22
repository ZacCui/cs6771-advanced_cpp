// test 10: const correctness

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
	
	const auto& constGraph = gCopy;
	
	std::cout << std::boolalpha << constGraph.isNode("a") << std::endl;
	std::cout << std::boolalpha << constGraph.isConnected("a","b") << std::endl;
	std::cout << std::boolalpha << constGraph.isConnected("c","b") << std::endl;
	
	std::cout << "Const graph: " << std::endl;
	constGraph.printNodes();
	
}
