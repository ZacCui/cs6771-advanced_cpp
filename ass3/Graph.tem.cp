#include "Graph.h"


template <typename N, typename E> 
Graph<N,E>::Graph(){
    std::map<N, std::shared_ptr<Node>> nodes{};
}

template <typename N, typename E> 
Graph<N,E>::~Graph(){
    nodes.clear();
}

//copy constructor
template <typename N, typename E> 
Graph<N,E>::Graph(const Graph& g){
    for(const auto &n : g.nodes){
        addNode(n.first);
    }
    for(const auto &n : g.nodes){
        for(const auto &w : n.second->getWeight()){
            if(w.first.expired()) continue;
            addEdge(n.first, w.first.lock()->getNode(), w.second);
        }
    }

}

//move constructor
template <typename N, typename E> 
Graph<N,E>::Graph(Graph&& g) {
    nodes = std::move(g.nodes);
}

//copy assignment
template <typename N, typename E> 
Graph<N,E>& Graph<N,E>::operator=(const Graph &g){
    if(this != &g){
        clear();
        for(const auto &n : g.nodes){
            addNode(n.first);
        }
        for(const auto &n : g.nodes){
            for(const auto &w : n.second->getWeight()){
                if(w.first.expired()) continue;
                addEdge(n.first, w.first.lock()->getNode(), w.second);
            }
        }
    }
    return *this;
}

//move assignment
template <typename N, typename E> 
Graph<N,E>& Graph<N,E>::operator=(Graph &&g){
    if(this != &g){
        this->nodes = std::move(g.nodes);
    }
    return *this;
} 

template <typename N, typename E> 
void Graph<N,E>::deleteNode(const N& val) noexcept{
    if(!isNode(val)) return;
    auto old = nodes.at(val);
    for(const auto & n: nodes){
        n.second->deleteEdge(old);
    }
    nodes.erase(val);
}

template <typename N, typename E> 
void Graph<N,E>::deleteEdge(const N& src, const N& dst, const E& w) noexcept{
    if(!isNode(src) || !isNode(dst)) return;
    const auto& from = nodes.at(src);
    const auto& to = nodes.at(dst);
    from->deleteEdge(to,w);  
}

template <typename N, typename E> 
bool Graph<N,E>::replace(const N& oldData, const N& newData){
    if(!isNode(oldData)) throw std::runtime_error("Node not exists");
    if(isNode(newData)) return false;
    auto old = nodes.at(oldData);
    old->setNode(newData);
    deleteNode(oldData);
    nodes.insert(std::make_pair(newData,old));
    return true;
}

template <typename N, typename E> 
void Graph<N,E>::clear() noexcept{
    nodes.clear();
}


template <typename N, typename E> 
void Graph<N,E>::mergeReplace(const N& oldData, const N& newData){
    if(!isNode(oldData) || !isNode(newData)) throw std::runtime_error("Node not exists");
    if(oldData == newData) return;
    const auto& old = nodes.at(oldData);
    const auto& New = nodes.at(newData);
    //change all old in/outgoing edge to the new one
    for(const auto & n: nodes){
        n.second->changeEdge(old,New);
    }
    //add non-duplicate edge to new node
    New->mergeEdge(old);
    //delete old node
    deleteNode(oldData);
}


template <typename N, typename E> 
bool Graph<N,E>::isNode(const N& val) const{
    return (nodes.find(val) != nodes.cend());
}

template <typename N, typename E> 
bool Graph<N,E>::addNode(const N& val){
    if(isNode(val)) return false;
    Node n(val);
    const auto & temp = std::make_pair(val,std::make_shared<Node>(n));
    nodes.insert(temp);
    return true;
}


template <typename N, typename E> 
bool Graph<N,E>::addEdge(const N& src, const N& dst, const E& w){
    if(!isNode(src) || !isNode(dst)) throw std::runtime_error("Node not exists");
    const auto& from = nodes.at(src);
    const auto& to = nodes.at(dst);
    if(isConnected(src,dst)){
        if(from->getWeight(to) == w ) return false;
    }
    return from->link(to,w);
}

template <typename N, typename E> 
bool Graph<N,E>::isConnected(const N& src, const N& dst) const{
    if(!isNode(src) || !isNode(dst)) throw std::runtime_error("Node not exists");
    const auto& from = nodes.at(src);
    const auto& to = nodes.at(dst);
    return from->Connected(to);
}

template <typename N, typename E> 
void Graph<N,E>::printNodes() const{
    std::vector<std::pair<N, std::shared_ptr<Node>>> temp;
    for( const auto& n : nodes){
        temp.push_back(n);
    }
    std::sort(temp.begin(), temp.end(),
        [](const std::pair<N, std::shared_ptr<Node>> & a,
           const std::pair<N, std::shared_ptr<Node>> & b){
            if(a.second->getEdgeNum() == b.second->getEdgeNum()) return a.second->getNode() < b.second->getNode();
            return a.second->getEdgeNum() < b.second->getEdgeNum();

        });
    for(const auto &n : temp){
        std::cout << n.second->getNode() << '\n';
    }

}

template <typename N, typename E> 
void Graph<N,E>::printEdges(const N& val) const{
    if(!isNode(val)) throw std::runtime_error("Node not exists");
    const auto& n = nodes.at(val);
    n->printEdge();
}


//=====================Node Class==============================
template <typename N, typename E> 
Graph<N, E>::Node::Node(const N& n): node{std::make_shared<N>(n)}{
     weight = std::list<std::pair<std::weak_ptr<Node>,E>>{};
}


template <typename N, typename E> 
Graph<N, E>::Node::~Node(){
    weight.clear();
}

template <typename N, typename E> 
N& Graph<N,E>::Node::getNode() const{
    return *node;
}

template <typename N, typename E> 
const int Graph<N, E>::Node::getEdgeNum() const{
    return weight.size();
}

template <typename N, typename E> 
bool Graph<N,E>::Node::link(const std::shared_ptr<Node> & dst, const E& w){
    std::weak_ptr<Node> to = dst;
    weight.push_back(std::make_pair(dst,w));
    return true;
}

template <typename N, typename E> 
bool Graph<N, E>::Node::Connected(const std::shared_ptr<Node> & dst) const{
    auto result = std::find_if(weight.cbegin(), weight.cend(),
        [&dst] (const std::pair<std::weak_ptr<Node>,E> & a) {
            if(a.first.expired()) return false;
            return a.first.lock()->getNode() == dst->getNode();
        });
    return (result != weight.cend());
}

template <typename N, typename E> 
void Graph<N, E>::Node::printEdge() const{
    std::vector<std::pair<std::weak_ptr<Node>,E>> temp;
    for( const auto& n : weight){
        temp.push_back(n);
    }
    std::sort(temp.begin(), temp.end(),
        [] (const std::pair<std::weak_ptr<Node>,E> & a,
            const std::pair<std::weak_ptr<Node>,E> & b) {
            return a.second < b.second;
        });
    std::cout << "Edges attached to Node "<< getNode() << '\n';
    if(!weight.empty()){
        for(const auto &w: temp){
            if(!w.first.expired()){
                std::cout << w.first.lock()->getNode()<< " " << w.second<< '\n';
            }
        }
    }else{
        std::cout << "(null)"<< '\n';
    }
}

template <typename N, typename E> 
const E& Graph<N,E>::Node::getWeight(const std::shared_ptr<Node> & dst) const{
    auto result = std::find_if(weight.cbegin(), weight.cend(),
        [&dst] (const std::pair<std::weak_ptr<Node>,E> & a) {
            if(a.first.expired()) return false;
            return (a.first.lock() == dst);
        });
    return result->second;
}

template <typename N, typename E> 
bool Graph<N,E>::Node::setNode(const N & val){
    node = std::make_shared<N>(val);
    return true;
}

template <typename N, typename E> 
void Graph<N,E>::Node::setWeight(const std::shared_ptr<Node> & old){
    weight = old->weight;
}

template <typename N, typename E> 
void Graph<N,E>::Node::changeEdge(const std::shared_ptr<Node> & old,const std::shared_ptr<Node> & New){
    auto result = std::find_if(weight.cbegin(),weight.cend(),
        [&old](const std::pair<std::weak_ptr<Node>,E> & a){
            if(a.first.expired()) return false;
            return a.first.lock() == old;
        });
    if(result == weight.cend()) return;
    auto w = result->second;
    std::weak_ptr<Node> wp = New;
    weight.push_back(make_pair(wp,w));
    weight.erase(result);
}

template <typename N, typename E> 
void Graph<N,E>::Node::mergeEdge(const std::shared_ptr<Node> & old){
    for(const auto &w : old->weight){
        if(w.first.expired()) continue;
        auto result = std::find_if(weight.cbegin(), weight.cend(),
            [&w] (const std::pair<std::weak_ptr<Node>,E> & a) {
                if(a.first.expired()) return false;
                return (a.first.lock() == w.first.lock() 
                    && a.second == w.second);
            });
        if(result != weight.cend()) continue;
        weight.push_back(w);
    }
}

template <typename N, typename E> 
void Graph<N,E>::Node::deleteEdge(const std::shared_ptr<Node> & to, const E &w){
    auto result = std::remove_if(weight.begin(),weight.end(),
        [&to,&w](const std::pair<std::weak_ptr<Node>,E> & a){
            if(a.first.expired()) return false;
            return (a.first.lock() == to && a.second == w);
        });
    weight.erase(result,weight.end());
}

template <typename N, typename E> 
const auto& Graph<N,E>::Node::getWeight()const {
    return weight;
}


template <typename N, typename E> 
void Graph<N,E>::Node::deleteEdge(const std::shared_ptr<Node> & to){ 
    auto result = std::remove_if(weight.begin(),weight.end(),
        [&to](const std::pair<std::weak_ptr<Node>,E> & a){
            if(a.first.expired()) return false;
            return (a.first.lock() == to);
        });
    weight.erase(result,weight.end());
}

template <typename N, typename E> 
void Graph<N,E>::Node::clear()noexcept{ 
    weight.clear();
}

//===================== Iterator ==============================
template <typename N, typename E> 
void Graph<N,E>::begin() const{
    MyIterator = nodes.cbegin();
}

template <typename N, typename E> 
bool Graph<N,E>::end() const{
    return MyIterator == nodes.cend();
}

template <typename N, typename E> 
void Graph<N,E>::next() const{
    ++MyIterator;
}

template <typename N, typename E> 
const N& Graph<N,E>::value() const{
    return MyIterator->first;
}









