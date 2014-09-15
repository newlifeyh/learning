
// this is not complete, just a flavor of the Binominal_heap.

#include <vector>

class BH_Element;
class BH_Tree;
class Binominal_heap;

struct BH_Element{
    BH_Element* _parent;
    int _key;
    int _degree;
    BH_Element* _child;
    BH_Element* _sibling;
};


class Binominal_heap{
    Binominal_heap();
    ~Binominal_heap();
    BH_Element* head();
    BH_Element* minimum();
    std::vector<BH_Element*> _bTrees;
    int _size;
};

Binominal_heap::Binominal_heap()
    : _size( 0 ){}

Binominal_heap::~Binominal_heap(){
    std::vector<BH_Element*>::iterator it = _bTrees.begin(), it_end = _bTrees.end();
    for( ; it != it_end; ++it ){
    
    }
}
BH_Element* Binominal_heap::head(){
    BH_Element* res = _bTress.front();
    return res;
}

Binominal_heap* make_binomial_heap(){
    Binominal_heap* res = new Binominal_heap();
    return res;
}

BH_Element * Binominal_heap::minimum(){
    BH_Element* element = head();
    BH_Element* res = element;
    if( element ){
        T value = element->_key;
        while( element ){
            if( value < element->_key ){
                value = element->_key;
                res = element;
            }
            element = element->_sibling;
        }
    }
    return res;
}

// merge the two bt into one, given the head of the two trees.
void binominal_link( BH_Element* large, BH_Element* small){
    assert( large && small );
    large->_parent = small;
    large->_sibling = small->_child;
    small->_child = large;
    small->_degree++;
}

// destory original two heaps, and return a new heap inculdes all of the trees sorted by degree. this is like merge sort.
BH_Element* binomial_heap_merge( Binominal_heap* lsh, Binominal_heap* rhs ){
    BH_Element* lsh_ptr = lsh->head();
    BH_Element* rsh_ptr = rsh->head();
    if( !lsh_ptr ){
        delete lsh;
        return rsh;
    }
    if( !rsh_ptr ){
        delete rsh;
        return lsh;
    }
    Binominal_heap* dest = new Binominal_heap;
    std::vector<BH_Element*> trees;
    while( lsh_ptr && rsh_ptr ){
        if( lsh_ptr->_degree <= rsh_ptr->_degree ){
            trees.push_back( lsh_ptr );
            lsh_ptr = lsh_ptr->_sibling;
        }
        else{
            trees.push_back( rsh_ptr );
            rsh_ptr = rsh_ptr->_sibling;
        }
    }
    BH_Element* left = lsh_ptr || rsh_ptr;
    while( left ){
        trees.push_back( left );
        left = left->_sibling;
    }
    delete lsh;
    delete rsh;
}

// 1. merge the two heaps into one by sorting on the degree.
// 2. merge the trees with the same degree.
Binominal_heap* binominal_heap_union( Binominal_heap* lhs, Binominal_heap* rhs ){
    Binominal_heap* curHeap = binomial_heap_merge( lhs, rhs );
    // if this is an empty heap, return it.
    if( !curHeap->head() ){
        return curHeap;
    }
    BH_Element* prev = NULL;
    BH_Element* curr = curHeap->head();
    BH_Element* next = curr->_sibling;

    while( next != NULL ){
        // if the current two are not the same degree, Or they are the same degree, but the following one has the same,
        // too. Note, there are at most 3 elements have the same degree.
        if( curr->_degree != next->_degree || (next->_sibling != NULL && next->_sibling->_degree == curr->_degree) ){
            // move the next step.
            prev = curr;
            curr = next;
        }
        // if current element is less than next, and they are the same degree, then remove next and link them.
        else if( curr->_key <= next->_key ){
            curr->_sibling = next->_sibling;
            binominal_link( next, curr );
        }
        // if current element is not less than next, and they are the same degree, then remove current, and link them
        else if( prev != NULL ){
            prev->_sibling = next;
            binominal_link( curr, next );
            curr = next;
        }
        // next.
        next = curr->_sibling;
    }
    return curHeap;
}

// functions to implement.
// binominal_heap_insert( heap, element )
// make a heap with single element and merge the two heaps by binominal_heap_union().

// binominal_heap_extract_min( heap )
// find the minimum and remove it, then flatten the tree below. then reverse it to have a new heap, then call
// binominal_heap_union() to merge into a new heap.

// binominal_heap_decrease_key( heap, element, key )
// exchange the element with it's parent until it's OK to be the heap.

// binominal_heap_delete( heap, element )
// decrease the element to negative infinity, and extract minimum by binominal_heap_extract_min().
