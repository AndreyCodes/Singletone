#include <iostream>
#include <atomic>
struct X
{
    X() { std::cout << "X()\n"; }
    ~X() { std::cout << "~X()\n"; }
    void foo() { std::cout << "foo()\n"; }
};
 
 
#include<iostream>
 
template<class Type>
struct Single : Type
{
    template<class... Args>
    static Single& init(Args&&... args)
    {
        if (!inst_ptr.load(std::memory_order_acquire))
            static Single inst(std::forward<Args>(args)...);
        else
            throw std::runtime_error("already exist");
 
        return *inst_ptr;
    }
    static Single& instance()
    {
        if (!inst_ptr.load(std::memory_order_acquire))
            throw std::runtime_error("Inst does not exist");
        return *inst_ptr;
    }
private:
    template<class... Args>
    Single(Args&&... args) : Type(std::forward<Args>(args)...)
    {
        Single::inst_ptr.store(this, std::memory_order_release);
    }
    Single& operator=(const Type&) = delete;
    Single& operator=(Type&&) = delete;
    Single(const Single&) = delete;
    Single(Single&&) = delete;
    ~Single() = default;
    static inline std::atomic<Single*> inst_ptr = nullptr;
};
struct B
{
    void fo()
    {
        std::cout << "FO";
    }
};
int main()
{
    try
    {
        auto& one = Single<B>::init();
        one.fo();
        
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what();
    }
}