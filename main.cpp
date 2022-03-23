#include<iostream>

struct SingleException: std::exception
{
    //todo what() override
};
template<class Type>
struct Single : Type
{
    template<class... Args>
    static Single& init(Args&&... args)
    {
        if(!inst_ptr)
        {
            static Single inst(std::forward<Args>(args)...);
        }
        else
        {
            throw std::runtime_error("already exist");
        }
        return *inst_ptr;
    }
    static Single& instance()
    {
        if(inst_ptr == nullptr)
        {
            //throw SingleException("Instance does not exist");
            throw std::runtime_error("Inst does not exist");
        }
        return *inst_ptr;
    }   
private:
    template<class... Args>
    Single(Args&&... args): Type(std::forward<Args>(args)...)
    {
        Single::inst_ptr = this;
    }
    Single& operator=(const Type&) = delete;
    Single& operator=(Type&&) = delete;
    Single(const Single&) = delete;
    Single(Single&&) = delete;
    using Type::Type;
    static inline Single* inst_ptr = nullptr;
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
    auto& one = Single<B>::init();
    one.fo();
}