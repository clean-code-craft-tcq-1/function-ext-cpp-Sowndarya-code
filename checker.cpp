
#include <assert.h>
#include <string.h>
#include <iostream>
using namespace std;

const string parameter[3] = { "temperature", "soc", "charge"};

void warningCheck(float value, float min, float max, int index_param)
{
  bool minValueWarningCheck = (value < (5/100 * min + min));
  bool maxValueWarningCheck = (value > (5/100 * max + max));
  if(minValueWarningCheck)
  {
    cout << parameter[index_param] << "is about to reach the minimum limit "<<endl;
  }
  if(maxValueWarningCheck)
  {
    cout << parameter[index_param] << "is about to reach the maximum limit "<<endl;
  }
}

bool isValueOutOfRange (float value, float min, float max, int index_param)
{
  bool valueOutOfRange = (value < min) || (value > max); 
  if(valueOutOfRange)
  {
    cout << parameter[index_param] << "is out of range "<<endl;
  }
  else
  {
    cout << parameter[index_param] << "is okay "<<endl;
    warningCheck(value, min, max, index_param);
  }
  return valueOutOfRange;
}


bool batteryIsOk(float temperature, float soc, float chargeRate) 
{
  bool tempCheck = isValueOutOfRange(temperature , 0.0F, 45.0, 0);
  bool socCheck = isValueOutOfRange(soc , 20.0, 80.0F, 1);
  bool chargeCheck = isValueOutOfRange(chargeRate, 0.0F, 0.8F, 2);
  bool batteryIsNotOkay = tempCheck || socCheck || chargeCheck;
  return !batteryIsNotOkay;
}

int main() 
{
  assert(batteryIsOk(25.0F, 70.0F, 0.7F) == true);  // all okay
  assert(batteryIsOk(50.0F, 85.0F, 0.0F) == false); // temp and soc high
  assert(batteryIsOk(50.0F, 65.0F, 0.0F) == false); // temp high
  assert(batteryIsOk(-50.0F, 80.0F, 0.0F) == false); // temp low
  assert(batteryIsOk(40.0F, 15.0F, 0.0F) == false); // soc low
  assert(batteryIsOk(40.0F, 85.0F, 0.0F) == false); // soc high
  assert(batteryIsOk(40.0F, 65.0F, 0.81F) == false); // charge rate high
}
