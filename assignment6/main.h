/*
 *  Name: Harsha Chamrajnagar Srikara
 *  NetID: hxc170009
 *  Course: CS3377.501
 *  Assignment: 6i
 *
 *  Description: main.h contains the two classes used by theis program
 */

using namespace std;
const int maxRecordStringLength = 25;

class BinaryFileHeader
{
  public:
     uint32_t magicNumber;
     uint32_t versionNumber;
     uint64_t numRecords;
};

class BinaryFileRecord
{
  public:
      uint8_t strLength;
      char stringBuffer[maxRecordStringLength];
};
