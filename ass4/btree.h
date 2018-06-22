/**
 * The btree is a linked structure which operates much like
 * a binary search tree, save the fact that multiple client
 * elements are stored in a single node.  Whereas a single element
 * would partition the tree into two ordered subtrees, a node
 * that stores m client elements partition the tree
 * into m + 1 sorted subtrees.
 */

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstddef>
#include <utility>
#include <vector>
#include <queue>
#include <memory>
#include <algorithm>

// we better include the iterator
#include "btree_iterator.h"

// we do this to avoid compiler errors about non-template friends
// what do we do, remember? :)
template <typename T> class btree;
template <typename T> class btree_iterator;
template <typename T> class const_btree_iterator;
template <typename T> std::ostream& operator<<(std::ostream& os, const btree<T>& tree);

template <typename T>
class btree {
public:
    /** Hmm, need some iterator typedefs here... friends? **/
    friend class btree_iterator<T>;
    friend class const_btree_iterator<T>;
    typedef btree_iterator<T> iterator;
    typedef const_btree_iterator<T> const_iterator;
    typedef std::reverse_iterator<btree_iterator<T>> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    /**
     * Constructs an empty btree.  Note that
     * the elements stored in your btree must
     * have a well-defined copy constructor and destructor.
     * The elements must also know how to order themselves
     * relative to each other by implementing operator<
     * and operator==. (These are already implemented on
     * behalf of all built-ins: ints, doubles, strings, etc.)
     *
     * @param maxNodeElems the maximum number of elements
     *        that can be stored in each B-Tree node
     */

    btree(size_t maxNodeElems = 40);

    /**
     * The copy constructor and  assignment operator.
     * They allow us to pass around B-Trees by value.
     * Although these operations are likely to be expensive
     * they make for an interesting programming exercise.
     * Implement these operations using value semantics and
     * make sure they do not leak memory.
     */

    /**
     * Copy constructor
     * Creates a new B-Tree as a copy of original.
     *
     * @param original a const lvalue reference to a B-Tree object
     */
    btree(const btree<T>& original);

    /**
     * Move constructor
     * Creates a new B-Tree by "stealing" from original.
     *
     * @param original an rvalue reference to a B-Tree object
     */
    btree(btree<T>&& original);


    /**
     * Copy assignment
     * Replaces the contents of this object with a copy of rhs.
     *
     * @param rhs a const lvalue reference to a B-Tree object
     */
    btree<T>& operator=(const btree<T>& rhs);

    /**
     * Move assignment
     * Replaces the contents of this object with the "stolen"
     * contents of original.
     *
     * @param rhs a const reference to a B-Tree object
     */
    btree<T>& operator=(btree<T>&& rhs);

    /**
     * Puts a breadth-first traversal of the B-Tree onto the output
     * stream os. Elements must, in turn, support the output operator.
     * Elements are separated by space. Should not output any newlines.
     *
     * @param os a reference to a C++ output stream
     * @param tree a const reference to a B-Tree object
     * @return a reference to os
     */
    friend std::ostream& operator<< <T>(std::ostream& os, const btree<T>& tree);

    /**
     * The following can go here
     * -- begin()
     * -- end()
     * -- rbegin()
     * -- rend()
     * -- cbegin()
     * -- cend()
     * -- crbegin()
     * -- crend()
     */
    iterator begin() const;
    iterator end() const;
    reverse_iterator rbegin()const;
    reverse_iterator rend() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;


    /**
      * Returns an iterator to the matching element, or whatever
      * the non-const end() returns if the element could
      * not be found.
      *
      * @param elem the client element we are trying to match.  The elem,
      *        if an instance of a true class, relies on the operator< and
      *        and operator== methods to compare elem to elements already
      *        in the btree.  You must ensure that your class implements
      *        these things, else code making use of btree<T>::find will
      *        not compile.
      * @return an iterator to the matching element, or whatever the
      *         non-const end() returns if no such match was ever found.
      */
    iterator find(const T& elem);

    /**
      * Identical in functionality to the non-const version of find,
      * save the fact that what's pointed to by the returned iterator
      * is deemed as const and immutable.
      *
      * @param elem the client element we are trying to match.
      * @return an iterator to the matching element, or whatever the
      *         const end() returns if no such match was ever found.
      */
    const_iterator find(const T& elem) const;

    /**
      * Operation which inserts the specified element
      * into the btree if a matching element isn't already
      * present.  In the event where the element truly needs
      * to be inserted, the size of the btree is effectively
      * increases by one, and the pair that gets returned contains
      * an iterator to the inserted element and true in its first and
      * second fields.
      *
      * If a matching element already exists in the btree, nothing
      * is added at all, and the size of the btree stays the same.  The
      * returned pair still returns an iterator to the matching element, but
      * the second field of the returned pair will store false.  This
      * second value can be checked to after an insertion to decide whether
      * or not the btree got bigger.
      *
      * The insert method makes use of T's copy constructor,
      * and if these things aren't available,
      * then the call to btree<T>::insert will not compile.  The implementation
      * also makes use of the class's operator== and operator< as well.
      *
      * @param elem the element to be inserted.
      * @return a pair whose first field is an iterator positioned at
      *         the matching element in the btree, and whose second field
      *         stores true if and only if the element needed to be added
      *         because no matching element was there prior to the insert call.
      */
    std::pair<iterator, bool> insert(const T& elem);

    /**
      * Disposes of all internal resources, which includes
      * the disposal of any client objects previously
      * inserted using the insert operation.
      * Check that your implementation does not leak memory!
      */
    ~btree() = default;

    const size_t getMaxNodeElems() const;


private:
    // The details of your implementation go here
    struct Node{
        Node();
        Node(Node& other);
        Node(const size_t& size);
        Node(std::shared_ptr<Node> par, const size_t & ind, const size_t& size);
        ~Node() = default;
        const unsigned int addElem(const T& e);
        bool isfull() const;
        bool hasChild() const;
        bool hasChildAt(const size_t& ind) const;
        bool hasParent() const;
        const auto&  getChilds() const;
        const auto&  getChilds(const size_t& index) const;
        const auto&  getVals() const;
        const T& getVals(const size_t& index) const;
        const size_t getSize() const;
        const size_t getPos() const;
        auto getParent() const;

        size_t pos ;
        std::weak_ptr<Node> parent;
        std::vector<T> vals;
        std::vector<std::shared_ptr<Node>> childs;
        size_t maxNodeElems;
    };
    std::shared_ptr<Node> root;
    size_t maxNodeElems{40U};
};

template <typename T>
const size_t btree<T>::getMaxNodeElems() const{
  return maxNodeElems;
}

template <typename T>
btree<T>::btree(size_t maxNodeElems):maxNodeElems{maxNodeElems}{
    Node n(maxNodeElems);
    root = std::make_shared<Node>(n);
}

template <typename T>
btree<T>::btree(const btree<T>& original){
  std::queue<std::shared_ptr<Node>> q;
  maxNodeElems = original.maxNodeElems;
  if(original.root != nullptr) q.push(original.root);
  while(!q.empty()){
    auto curr = q.front();
    q.pop();
    for(const auto& n: curr->getVals()) insert(n);
    for(const auto& n: curr->getChilds()){
      if(n == nullptr) continue;
      q.push(n);
    }
  }
}

template <typename T>
btree<T>::btree(btree<T>&& original){
  root = std::move(original.root);
  maxNodeElems = std::move(original.maxNodeElems);
}

template <typename T>
btree<T>& btree<T>::operator=(const btree<T>& rhs){
  if(this == &rhs) return *this;
  std::queue<std::shared_ptr<Node>> q;
  maxNodeElems = rhs.maxNodeElems;
  if(rhs.root != nullptr) q.push(rhs.root);
  while(!q.empty()){
    auto curr = q.front();
    q.pop();
    for(const auto& n: curr->getVals()) insert(n);
    for(const auto& n: curr->getChilds()){
      if(n == nullptr) continue;
      q.push(n);
    }
  }
  return *this;
}

template <typename T>
btree<T>& btree<T>::operator=(btree<T>&& rhs){
  if(this != &rhs){
    root = std::move(rhs.root);
    maxNodeElems = std::move(rhs.maxNodeElems);
  }
  return *this;
}


template <typename T>
btree_iterator<T> btree<T>::find(const T& elem){
    if(root == nullptr) return end();
    std::queue<std::shared_ptr<Node>> q;
    q.push(root);
    while(!q.empty()){
        auto node = q.front();
        q.pop();
        if(node == nullptr) continue;
        auto result = std::find_if(node->vals.begin(),node->vals.end(),
                                   [&elem](const T & a){
                                       return (elem == a);
                                   });
        if(result == node->vals.end()){
            auto res = std::find_if(node->vals.begin(),node->vals.end(),
                                  [&elem](const T & a){
                                      return (elem < a);
                                  });
            ptrdiff_t index;
            if(res != node->vals.end()){
                index = result - node->vals.begin();
            }else{
                index = maxNodeElems;
            }
            if(node->hasChildAt(index)) q.push(node->childs[index]);
        }else{
            unsigned int pos = result - node->vals.begin();
            return btree_iterator<T>(node, pos,false);
        }
    }
    return end();
}

template <typename T>
const_btree_iterator<T> btree<T>::find(const T& elem) const{
    if(root == nullptr) return cend();
    std::queue<std::shared_ptr<Node>> q;
    q.push(root);
    while(!q.empty()){
        auto node = q.front();
        q.pop();
        if(node == nullptr) continue;
        auto result = std::find_if(node->vals.begin(),node->vals.end(),
                                   [&elem](const T & a){
                                       return (elem == a);
                                   });
        if(result == node->vals.end()){
            auto res = std::find_if(node->vals.begin(),node->vals.end(),
                                  [&elem](const T & a){
                                      return (elem < a);
                                  });
            ptrdiff_t index;
            if(res != node->vals.end()){
                index = result - node->vals.begin();
            }else{
                index = getMaxNodeElems();
            }
            if(node->hasChildAt(index)) q.push(node->childs[index]);
        }else{
            unsigned int pos = result - node->vals.begin();
            return const_btree_iterator<T>(node, pos,false);
        }
    }
    return cend();
}

template <typename T>
std::pair<btree_iterator<T>, bool> btree<T>::insert(const T& elem){
    if(root == nullptr ){
        Node n(maxNodeElems);
        root = std::make_shared<Node>(n);
        auto ind = root->addElem(elem);
        return std::make_pair(btree_iterator<T>(root,ind,false),true);
    }
    btree_iterator<T> result = find(elem);
    if(result != end()) return std::make_pair(result,false);
    std::queue<std::shared_ptr<Node>> q;
    q.push(root);
    auto par = q.front();
    auto node = q.front();
    while(!q.empty()){
        node = q.front();
        q.pop();
        while(node->isfull()){
            auto result = std::find_if(node->vals.begin(),node->vals.end(),
                                       [&elem](const T & a){
                                           return (elem < a);
                                       });
            ptrdiff_t index;
            if(result != node->vals.end()){
                index = result - node->vals.begin();
            }else{
                index = getMaxNodeElems();
            }
            if(node->hasChildAt(index)){
              q.push(node->childs[index]);
              break;
            }else{
              Node n(par,index,maxNodeElems);
              auto ind = n.addElem(elem);
              while(node->childs.size() < static_cast<unsigned int>(index)){
                Node a(par,node->childs.size(),maxNodeElems);
                node->childs.push_back(std::make_shared<Node>(a));
              }
              node->childs.push_back(std::make_shared<Node>(n));
              btree_iterator<T> it = btree_iterator<T>(node,ind,false);
              return std::make_pair(it,true);
            }
        }
        par = node;
        if(!node->isfull()) break;
    }
    //now we get not full node
    auto ind = node->addElem(elem);
    return std::make_pair(btree_iterator<T>(node,ind,false),true);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const btree<T>& tree){
    if(tree.root == nullptr) return os;
    std::queue<std::shared_ptr<typename btree<T>::Node>> q;
    q.push(tree.root);
    while(!q.empty()){
      auto curr = q.front();
      q.pop();
      for(const auto& n: curr->getVals()){
        os << n <<" ";
      }
      for(const auto& n: curr->getChilds()){
        if(n == nullptr) continue;
        q.push(n);
      }
    }
    return os;
}

//======================== Iterator implement =========================
template <typename T>
typename btree<T>::iterator btree<T>::begin() const{
    if(root == nullptr ) return end();
    auto curr = root;
    while(curr->hasChildAt(0)){
        curr = curr->getChilds(0);
    }
    return iterator(curr,0,false);
}

template <typename T>
typename btree<T>::iterator btree<T>::end() const{
    auto curr = root;
    while(curr->hasChildAt(curr->getSize())){
        curr = curr->getChilds(curr->getSize());
    }
    unsigned int ind = curr->getSize() - 1;

    return iterator(curr,ind,true);
}

template <typename T>
std::reverse_iterator<btree_iterator<T>> btree<T>::rbegin() const{
    return reverse_iterator(end());
}

template <typename T>
std::reverse_iterator<btree_iterator<T>> btree<T>::rend() const{
    auto curr = root;
    while(curr->hasChildAt(0)){
        curr = curr->getChilds(0);
    }
    return reverse_iterator(iterator(curr,0,true));
}

template <typename T>
const_btree_iterator<T> btree<T>::cbegin() const {
    if(root == nullptr) return cend();
    auto curr = root;
    while(curr->hasChildAt(0)){
        curr = curr->getChilds(0);
    }
    return const_btree_iterator<T>(curr,0,false);
}

template <typename T>
const_btree_iterator<T> btree<T>::cend() const {
    auto curr = root;
    while(curr->hasChildAt(curr->getSize())){
        curr = curr->getChilds(curr->getSize());
    }
    unsigned int ind = curr->getSize()-1;
    return const_btree_iterator<T>(curr,ind,true);
}

template <typename T>
std::reverse_iterator<const_btree_iterator<T>> btree<T>::crbegin() const {
    return const_reverse_iterator(cend());
}

template <typename T>
std::reverse_iterator<const_btree_iterator<T>> btree<T>::crend() const {
    auto curr = root;
    while(curr->hasChildAt(0)){
        curr = curr->getChilds(0);
    }
    return const_reverse_iterator(const_btree_iterator<T>(curr,0,true));
}

//======================== Nodes implement =========================
template <typename T>
btree<T>::Node::Node(std::shared_ptr<Node> par, const size_t & ind, const size_t& size){
    parent = par;
    pos = ind;
    maxNodeElems = size;
}

template <typename T>
btree<T>::Node::Node(const size_t& size){
    pos = 0U;
    maxNodeElems = size;
}

template <typename T>
btree<T>::Node::Node(Node& other){
    pos = other.pos;
    parent = other.parent;
    vals = other.vals;
    childs = other.childs;
    maxNodeElems = other.maxNodeElems;
}


template <typename T>
const unsigned int btree<T>::Node::addElem(const T& e){
    auto result = std::find_if(vals.begin(),vals.end(),
                               [&e](const T& a){
                                   return (e < a);
                               });
    ptrdiff_t index = result- vals.begin() ;
    vals.insert(vals.begin()+index,e);
    return static_cast<unsigned int>(index);
}

template <typename T>
bool btree<T>::Node::isfull() const{
    return (vals.size()==maxNodeElems);
}

template <typename T>
bool btree<T>::Node::hasChild() const{
    return childs.size() > 0;
}

template <typename T>
bool btree<T>::Node::hasParent() const{
    return (!parent.expired() && parent.lock() != nullptr);
}

template <typename T>
bool btree<T>::Node::hasChildAt(const size_t& ind) const{
    if(childs.empty() || ind > childs.size()-1) return false;
    if(childs.at(ind) != nullptr && childs.at(ind)->vals.empty()){
      return false;
    }
    return (childs.at(ind) != nullptr);
}

template <typename T>
auto btree<T>::Node::getParent() const{
    return parent.lock();
}

template <typename T>
const size_t btree<T>::Node::getSize() const{
    return vals.size();
}

template <typename T>
const auto& btree<T>::Node::getChilds() const{
    return childs;
}

template <typename T>
const auto&  btree<T>::Node::getChilds(const size_t& index) const{
    return childs.at(index);
}

template <typename T>
const auto&  btree<T>::Node::getVals() const{
    return vals;
}

template <typename T>
const T& btree<T>::Node::getVals(const size_t& index) const{
    return vals.at(index);
}

template <typename T>
const size_t btree<T>::Node::getPos() const{
    return pos;
}


#endif

