extern "C"{
   #include "nfc.h"
}
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

int main(){
   int x;
   high_resolution_clock::time_point t1 = high_resolution_clock::now();
   //needs 3 seconds to finish polling, recommend sample at every 3 seconds 
   x = NFCresult();
   high_resolution_clock::time_point t2 = high_resolution_clock::now();

   auto duration = duration_cast<milliseconds>( t2 - t1 ).count();
  
   cout << duration<<"ms"<<endl;
   printf("%d\n",x);
   return 0;
}
