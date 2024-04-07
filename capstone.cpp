#include <iostream>
using namespace std;
class random{
private:
       unsigned long long s;
public:
      random(){
        s=123456789ULL;
      }
// generate a random number
int next(int x){
  constexpr unsigned long long long modulus=0xFFFFFFFFFFFFFFFFULL;
  s=(6364136223846793005ULL * s + 1ULL) % modulus;
  return static_cast<int>((s>>32)%(x+1));
}
};
