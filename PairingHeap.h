#ifndef PAIRINGHEAP_H_INCLUDED
#define PAIRINGHEAP_H_INCLUDED

/*
 * Michael Tripp
 * Project 6
 * 11/6/2020
 */

template <typename Comparable>
class PairingHeap
{
public:
    explicit PairingHeap ( ) : root { nullptr } {}
    explicit PairingHeap ( PairingNode & n ) : root { n } {}
    explicit PairingHeap ( PairingNode && n ) : root { std::move ( n ) } { }
    ~PairingHeap ( ) { makeEmpty( root ); }

    void makeEmpty ( PairingNode* &t )
    {
        if ( t != nullptr )
        {
            makeEmpty ( t->firstChild );
            makeEmpty ( t->nextSibling );
            delete t;
        }
        root = nullptr;
    }

    void insert ( const Comparable & x )
    {
       merge ( root, new PairingNode( x, nullptr, nullptr ) );
    }

    static PairingNode merge ( PairingNode* &p1, PairingNode* &p2 )
    {
        if ( p1 == nullptr ) {
            return p2;
        }
        if ( p2 == nullptr ) {
            return p1;
        }

        if ( p1->key < p2->key ) {
            p1->nextSibling = p2->nextSibling;
            p2->nextSibling = p1->firstChild;
            p1->firstChild = p2;
            return p1;
        }
        else {
            p1->nextSibling = p2->firstChild;
            p2->firstChild = p1;
            return p2;
        }
    }

    void deleteMinimum ( )
    {
        PairingNode p = root->firstChild;
        delete findMinimum( );

        merge( merge( p, p->nextSibling ), mergeRest( p->nextSibling->nextSibling ) );
    }

    static PairingNode mergeRest ( PairingNode* &p )
    {
        if ( p->nextSibling == nullptr || p == nullptr ) {
            return p;
        }
        return mergeRest( merge ( p, p->nextSibling ) );
    }

    PairingNode findMinimum ( ) const
    {
        return root;
    }

private:
    PairingNode root*;

friend PairingNode;
};

template <typename Comparable>
struct PairingNode
{
    public:
        PairingNode( const Comparable & k, PairingNode *ns, PairingNode *fc)
                : key { k }, firstChild { fc }, nextSibling { ns } { }

        PairingNode( const Comparable & theElement, PairingNode *ns, PairingNode *fc)
                : key { std::move( k ) }, firstChild { fc }, nextSibling { ns } { }

    private:
        Comparable key;
        Comparable *firstChild;
        Comparable *nextSibling;
};

#endif // PAIRINGHEAP_H_INCLUDED
