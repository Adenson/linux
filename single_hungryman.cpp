#include<iostream>
#include<mutex>
#include<thread>
using namespace std;
mutex mtx;
template<class T>
class singleton
{
  private:
   volatile static T* _data;
  public:
   volatile T *GetInstance()
    {
      if(_data == NULL)
      {
        mtx.lock();
        if(_data == NULL)
        {
            _data = new T(123);
        }
        mtx.unlock();
      }
      return _data;
    }
};

template<class T>
volatile T* singleton<T>:: _data = NULL;

int main()
{
  singleton<int> A,B;
  printf("%p\n",A.GetInstance());
  cout << *A.GetInstance() << " " << A.GetInstance() << endl;
  cout << *B.GetInstance() << " " << A.GetInstance() << endl;
  return 0;
}
