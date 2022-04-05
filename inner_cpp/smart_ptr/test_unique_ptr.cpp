/*
refer from https://en.cppreference.com/w/cpp/memory/unique_ptr. 
*/
#include <cassert>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include "unique_ptr.h" 
// helper class for runtime polymorphism demo below
struct B
{
    virtual ~B() = default;
 
    virtual void bar() { std::cout << "B::bar\n"; }
};
 
struct D : B
{
    D() { std::cout << "D::D\n"; }
    ~D() { std::cout << "D::~D\n"; }
 
    void bar() override { std::cout << "D::bar\n"; }
};
 
// a function consuming a unique_ptr can take it by value or by rvalue reference
unique_ptr<D> pass_through(unique_ptr<D> p)
{
    p->bar();
    return p;
}
 
 
// unique_ptr-based linked list demo
struct List
{
    struct Node
    {
        int data;
        unique_ptr<Node> next;
    };
 
    unique_ptr<Node> head;
 
    ~List()
    {
        // destroy list nodes sequentially in a loop, the default destructor
        // would have invoked its `next`'s destructor recursively, which would
        // cause stack overflow for sufficiently large lists.
        while (head)
            head = std::move(head->next);
    }
 
    void push(int data)
    {
        head = unique_ptr<Node>(new Node{data, std::move(head)});
    }
};
 
int main()
{
    std::cout << "1) Unique ownership semantics demo\n";
    {
        // Create a (uniquely owned) resource
        unique_ptr<D> p(new D);
 
        // Transfer ownership to `pass_through`,
        // which in turn transfers ownership back through the return value
        unique_ptr<D> q = pass_through(std::move(p));
 
        // `p` is now in a moved-from 'empty' state, equal to `nullptr`
        assert(!p);
    }
 
    std::cout << "\n" "2) Runtime polymorphism demo\n";
    {
        // Create a derived resource and point to it via base type
        unique_ptr<B> p(new D);
 
        // Dynamic dispatch works as expected
        p->bar();
    }
 
 
    std::cout << "\n" "6) Linked list demo\n";
    {
        List wall;
        for (int beer = 0; beer != 1000000; ++beer)
            wall.push(beer);
 
        std::cout << "1'000'000 bottles of beer on the wall...\n";
    } // destroys all the beers
}
/* possible out
1) Unique ownership semantics demo
D::D
D::bar
D::~D
 
2) Runtime polymorphism demo
D::D
D::bar
D::~D

6) Linked list demo
1'000'000 bottles of beer on the wall...
*/