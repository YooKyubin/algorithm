#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Base
{
private:
    Base(int i)
    : a(i)
    {
        cout << "Constructor" << endl;
    }

    Base(const Base& cpy)
    {
        a = cpy.a;
        cout << "copy contructor" << endl;
    }
    
    Base(Base&& mv)
    {
        a = mv.a;
        cout << "move contructor" << endl;
    }

public:
    ~Base()
    {
        cout << "Destructor" << endl;
    }

    static unique_ptr<Base> CreateUnique(int a);
    static shared_ptr<Base> CreateShared(int a);

private:
    int a{ 0 };
};

class A
{
public:
    virtual void Fun()
    {
        cout << "call A" << endl;
    }
};

class B : public A
{
public:
    virtual void Fun() override
    {
        cout << "call B" << endl;    
    }
};

unique_ptr<Base> Base::CreateUnique(int a)
{
    // auto unique = new Base(a);
    return std::move(unique_ptr<Base>( new Base(a) ));
    // return unique_ptr<Base>(unique);
}

shared_ptr<Base> Base::CreateShared(int a)
{
    return std::move(shared_ptr<Base>( new Base(a) ));
}

int main()
{
    // auto pA = make_unique<Base>( Base::Create(3) );

    // B* pB = new B;
    // auto b = make_unique<B>(  );
    auto p = Base::CreateShared(3);
    // weak_ptr<Base>(p).lock().

    B* b = new B;
    b->Fun();

    A* a = b;
    a->Fun();

    // delete b;
    delete a;

    vector<int> vecA;
    for (int i = 1; i < 9; ++i)
    {
        vecA.push_back(i * 10);
    }

    auto iter = vecA.begin() + 2;
    cout << *iter << endl;
    cout << *(++iter) << endl;
    cout << *(iter++) << endl;
    cout << *iter << endl;


    vector<int> GG { 3, 2 };
    cout << GG.size() << endl;

    int foo = 3;
    int* pFoo = &foo;

    const int* cpFoo = pFoo;

    int bg { 3.f };
    return 0;
}