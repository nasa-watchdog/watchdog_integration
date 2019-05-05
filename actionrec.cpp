#include <thread>
#include <iostream>
#include "imu.h"
extern "C"{
   #include "nfc.h"
}
#include "camera.h"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;
//#include "nfc.h"
//#include "camera.h"

int main()
{
    imu_acc imu_acc_out;
    int nfc_out;
    //volatile int cam_out;
    
    std::thread imu_thread(run_imu, std::ref(imu_acc_out));
    std::thread nfc_thread(run_nfc, std::ref(nfc_out));
    std::thread cam_thread(run_cam);
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    imu_thread.join();
    nfc_thread.join();
    cam_thread.join();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();
  
    std::cout<<std::endl<<std::endl;
    cout << duration<<"ms"<<endl;
    std::cout<<imu_acc_out.x<<' '<<imu_acc_out.y<<' '<<imu_acc_out.z<<std::endl;
    std::cout<<nfc_out<<std::endl;
}
