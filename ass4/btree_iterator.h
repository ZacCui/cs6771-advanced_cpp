#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>
#include <memory>
#include <list>

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/
template <typename T> class btree;
template <typename T> class btree_iterator;
template <typename T> class const_btree_iterator;


template <typename T>
class btree_iterator {
public:
    friend class const_btree_iterator<T>;
    typedef ptrdiff_t                  		difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                          		value_type;
    typedef T*                         		pointer;
    typedef T&                         		reference;
    typedef typename btree<T>::Node 		Node;

    reference operator*() const;
    pointer operator->() const {return &(operator*());}
    btree_iterator& operator++();
    btree_iterator& operator++(int);
    btree_iterator& operator--();
    btree_iterator& operator--(int);

    bool operator==(const btree_iterator& other) const;
    bool operator!=(const btree_iterator& other) const {return !(operator==(other));}
    bool operator==(const const_btree_iterator<T>& other) const;
    bool operator!=(const const_btree_iterator<T>& other) const {return !(operator==(other));}

    btree_iterator(std::shared_ptr<Node> n, unsigned int index, bool e);
    btree_iterator(Node& n, unsigned int  pos, bool e);
    btree_iterator() = default;
    btree_iterator(const btree_iterator& b) = default;
    btree_iterator(btree_iterator&& b) noexcept = default;


private:
    std::weak_ptr<Node> curr;
    unsigned int pos;
    bool ends {false};
};

template <typename T>
class const_btree_iterator {
public:
    friend class btree_iterator<T>;
    typedef std::ptrdiff_t              	difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                           	value_type;
    typedef T*                          	pointer;
    typedef T&                          	reference;
    typedef typename btree<T>::Node 		Node;

    const_btree_iterator() = default;
    const_btree_iterator(std::shared_ptr<Node> &n, unsigned int pos, bool e):it{btree_iterator<T>(n,pos,e)} {}
    const_btree_iterator(const btree_iterator<T>& b) :it{btree_iterator<T>{b}} {}
    const_btree_iterator(const const_btree_iterator& b) = default;
    const_btree_iterator(const_btree_iterator&& b) noexcept = default;

    reference operator*() const {
        return *it;
    }
    pointer operator->() const {
        return &(operator*());
    }
    const_btree_iterator& operator++() {
        ++it;
        return *this;
    }
    const_btree_iterator& operator--() {
        --it;
        return *this;
    }

    const_btree_iterator& operator++(int) {
        auto temp = *this;
        ++it;
        return temp;
    }
    const_btree_iterator& operator--(int) {
        auto temp = *this;
        --it;
        return temp;
    }

    bool operator==(const const_btree_iterator& other) const {
        return it == other.it;
    }
    bool operator!=(const const_btree_iterator& other) const {
        return !operator==(other.it);
    }
    bool operator==(const btree_iterator<T>& other) const {
        return it == other;
    }
    bool operator!=(const btree_iterator<T>& other) const {
        return it != other;
    }

private:
    btree_iterator<T> it;
};

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)
template <typename T>
btree_iterator<T>::btree_iterator(std::shared_ptr<Node> n, unsigned int index,bool e){
    curr = n;
    pos = index;
    ends = e;
}

template <typename T>
btree_iterator<T>::btree_iterator(Node &n, unsigned int index,bool e){
    curr = std::make_shared<Node>(n);
    pos = index;
    ends = e;
}

template <typename T>
typename btree_iterator<T>::reference btree_iterator<T>::operator*() const {
    return	curr.lock()->vals[pos];
}

template <typename T>
bool btree_iterator<T>::operator==(const btree_iterator& other) const{
    if(this == &other) return true;
    if(curr.expired() || other.curr.expired()) return false;
    return (curr.lock() == other.curr.lock() && pos == other.pos && ends == other.ends);
}

template <typename T>
bool btree_iterator<T>::operator==(const const_btree_iterator<T>& other) const{
    if(this == &other) return true;
    if(curr.expired() || other.curr.expired()) return false;
    return (curr.lock() == other.curr.lock() && pos == other.pos&& ends == other.ends);
}

template <typename T>
btree_iterator<T>& btree_iterator<T>::operator++(){
    if(curr.expired()) return *this;
    auto pivt = curr.lock()->getVals(pos);
    while(curr.lock()->getVals(pos) <= pivt && !curr.expired()){
        if(pos < curr.lock()->getSize()-1){
            ++pos;
            if(curr.lock()->hasChildAt(pos)){
                curr = curr.lock()->getChilds(pos);
                pos = 0U;
            }
            break;
        }else if(pos == curr.lock()->getSize()-1){
            if(curr.lock()->hasChildAt(pos+1)){
                //search childs
                curr = curr.lock()->getChilds(pos+1);
                pos = 0U;
                break;
            }else if(!curr.lock()->hasChildAt(pos+1) && curr.lock()->hasParent()){
                //search parent
                auto old_curr = curr;
                auto old_pos = pos;
                auto par_pos = curr.lock()->getPos();
                curr = curr.lock()->getParent();
                pos = 0;
                if(par_pos != curr.lock()->getSize()) break;
                par_pos = curr.lock()->getPos();
                auto flag = false;
                if(curr.lock()->hasParent()){
                    auto check = curr.lock()->getParent();
                    if(check->getVals(pos) <= pivt) flag = true;
                }
                if(flag || !curr.lock()->hasParent()){
                    curr = old_curr;
                    pos = old_pos;
                    ends = true;
                    break;
                }
            }else if(!curr.lock()->hasChildAt(pos+1) && !curr.lock()->hasParent()){
                ends = true;
                break;
            }
        }
    }
    return *this;
}

template <typename T>
btree_iterator<T>& btree_iterator<T>::operator++(int){
    auto temp = *this;
    ++*this;
    return temp;
}

template <typename T>
btree_iterator<T>& btree_iterator<T>::operator--(){
    if(curr.expired()) return *this;
    auto pivt = curr.lock()->getVals(pos);
    while(curr.lock()->getVals(pos) >= pivt && !curr.expired()){
        if(pos > 0){
            --pos;
            if(curr.lock()->hasChildAt(pos+1)){
                curr = curr.lock()->getChilds(pos+1);
                pos = curr.lock()->getSize()-1;
            }
            break;
        }else if(pos == 0){
            if(curr.lock()->hasChildAt(pos)){
                //search childs
                curr = curr.lock()->getChilds(pos);
                pos = curr.lock()->getSize()-1;
                break;
            }else if(!curr.lock()->hasChildAt(pos) && curr.lock()->hasParent()){
                //search parents
                auto old_curr = curr;
                auto old_pos = pos;
                curr = curr.lock()->getParent();
                pos = curr.lock()->getSize() - 1;
                if(curr.lock()->getVals(pos) < pivt) break;
                auto flag = false;
                if(curr.lock()->hasParent()){
                    auto check = curr.lock()->getParent();
                    if(check->getVals(pos) >= pivt) flag = true;
                }
                if(flag || !curr.lock()->hasParent()){
                    curr = old_curr;
                    pos = old_pos;
                    ends = true;
                    break;
                }
            }else if(!curr.lock()->hasChildAt(pos) && !curr.lock()->hasParent()){
                ends = true;
                break;
            }
        }
    }
    return *this;
}

template <typename T>
btree_iterator<T>& btree_iterator<T>::operator--(int){
    auto temp = *this;
    --*this;
    return temp;
}

#endif

