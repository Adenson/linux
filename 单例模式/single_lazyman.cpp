#include<iostream>
using namespace std;
template <class T>
class single
{
  private:
    static T data;
  public:
   static T* GetInstance()
    {
      return &data;
    }
};

template <class T>
T single<T>::data = 123;
int main()
{
  single<int> A,B;
  cout << *A.GetInstance() << " " << A.GetInstance() << endl;
  cout << *B.GetInstance() << " " << B.GetInstance() << endl;
  return 0;
}
