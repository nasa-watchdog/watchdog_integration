#include "imu.h"
#include <string.h>
#include <iostream>

using namespace std;

int main()
{
  imu_acc imu_acc_out;
  run_imu(imu_acc_out);
  cout<<imu_acc_out.x<<' '<<imu_acc_out.y<<' '<<imu_acc_out.z<<endl;
}
