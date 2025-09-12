#include <iostream>

using namespace std;

class A
{
public:
     ~A()
    {
        cout << "Destruct A" << endl;
    }
    A()
    {
        cout << "Default Construct A" << endl;
    }

    A(const A& rhs)
    {
        cout << "Copy Construct A" << endl;
    }

    A(A&& rhs)
    {
        cout << "Move Construct A" << endl;
    }

    A& operator=(const A&)
    {
        cout << "operator const A&" << endl;
        return *this;
    }

    A& operator=(A&&)
    {
        cout << "operator A&&" << endl;
        return *this;
    }

    int m_var;

    virtual void vFunc()
    {
        cout << "Base" << endl;
    }
};

class B : public A
{
public:
     ~B()
    {
        cout << "Destruct B" << endl;
    }
    B()
    : A()
    {
        cout << "Default Construct B" << endl;
    }

    B(const B& rhs)
    // : A(std::move(rhs))
    : A(rhs)
    {
        cout << "Copy Construct B" << endl;
    }

    B(B&& rhs)
    // : A(std::move(rhs))
    : A(rhs)
    {
        cout << "Move Construct B" << endl;
    }

    virtual void vFunc() override
    {
        cout << "Derived" << endl;
    }
};

// void Func(A a)
// {
//     cout << "Call A Func" << endl;
//     A InstanceA(std::move(a));
// }

void Func(const A& a)
{
    cout << "Call const A& Func" << endl;
    A InstanceA(std::move(a));
}

void Func(A&& a)
{
    cout << "Call A&& Func" << endl;
    A InstanceA(std::move(a));
}

A GetA()
{
    return A();
}

void Print(A a)
{
    a.vFunc();
}

int main()
{
    // A instanceA("adsf");
    // Func(instanceA);

    // Func(A("sdlfkj"));

    // decltype(A( "dslfjs" )) a("ds");

    // A* pA = new B();
    // if (nullptr == dynamic_cast<B*>(pA))
    // {
    //     cout << "nullptr" << endl;
    // }
    // else
    // {
    //     cout << "cast " << endl;
    // }
    // delete pA;

    Func(B());
    Func(A());

    // A a = B();
    // a.vFunc();

    // B b = B();
    // b.vFunc();

    return 0;
}