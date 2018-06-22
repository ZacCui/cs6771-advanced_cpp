// test 1: tests graph construction and node insertion 

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
	
	std::string s = "world";
	g2.addNode(s);
	g2.addNode("Hello");
	
	std::shared_ptr<int> sp = std::make_shared<int>(5);
	g3.addNode(sp);
	g3.addNode(std::make_shared<int>(6));
	
	// print the nodes from each graph. 
	std::cout << "Graph g nodes:" << std::endl;
	g.printNodes();
	std::cout << "Graph g2 nodes:" << std::endl;
	g2.printNodes();
	std::cout << "isNode test:" << std::endl;
	std::cout << std::boolalpha << g3.isNode(sp) << std::endl;
}
