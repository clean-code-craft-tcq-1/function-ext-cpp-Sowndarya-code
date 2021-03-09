
#include <assert.h>
#include <string.h>
#include <iostream>
using namespace std;

const string parameter[3] = { "temperature", "soc", "charge"};

string language[2] = {"English", "German"};

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

bool isValueOutOfRange (float value, float min, float max, int index_param, string s)
{
  bool valueOutOfRange = (value < min) || (value > max); 
  if(valueOutOfRange)
  {
    cout << parameter[index_param] << "is out of range "<<endl
   //(s==language[0])?cout << parameter[index_param] << "is out of range "<<endl:cout << parameter[index_param] << "ist aerata "<<endl;
  }
  else
  {
    cout << parameter[index_param] << "is okay "<<endl;
   //(s==language[0])?cout << parameter[index_param] << "is okay "<<endl:cout << parameter[index_param] << "ist ok "<<endl;
    warningCheck(value, min, max, index_param);
  }
  return valueOutOfRange;
}


bool batteryIsOk(float temperature, float soc, float chargeRate, string s) 
{
  bool tempCheck = isValueOutOfRange(temperature , 0.0F, 45.0, 0, s);
  bool socCheck = isValueOutOfRange(soc , 20.0, 80.0F, 1, s);
  bool chargeCheck = isValueOutOfRange(chargeRate, 0.0F, 0.8F, 2, s);
  bool batteryIsNotOkay = tempCheck || socCheck || chargeCheck;
  return !batteryIsNotOkay;
}

int main() 
{
  assert(batteryIsOk(25.0F, 70.0F, 0.7F, language[0]) == true);  // all okay
  assert(batteryIsOk(50.0F, 85.0F, 0.0F,language[1]) == false); // temp and soc high
  assert(batteryIsOk(50.0F, 65.0F, 0.0F,language[0]) == false); // temp high
  assert(batteryIsOk(-50.0F, 80.0F, 0.0F,language[1]) == false); // temp low
  assert(batteryIsOk(40.0F, 15.0F, 0.0F,language[0]) == false); // soc low
  assert(batteryIsOk(40.0F, 85.0F, 0.0F,language[1]) == false); // soc high
  assert(batteryIsOk(40.0F, 65.0F, 0.81F,language[0]) == false); // charge rate high
}
