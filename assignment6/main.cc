/*
 * Name: Harsha Chamrajnagar Srikara
 * NetID: hxc170009
 * Course: CS3377.501
 * Assignment: 6
 *
 * Description: main.cc contains all the binary file reading and cdk code to visualize information
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdint.h>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 30
#define MATRIX_NAME_STRING "Binary File Contents"

#include "main.h"

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;          
  const char 	*rowTitles[] = {"a", "a", "b", "c", "d", "e"};
  const char 	*columnTitles[] = {"a", "a", "b", "c", "d", "e"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};
  
  window = initscr();
  cdkscreen = initCDKScreen(window);
  initCDKColor();
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);
  if (myMatrix ==NULL)
    {
      std::cout << "Error occurred in matrix creation" << std::endl;
      _exit(1);
    }

  drawCDKMatrix(myMatrix, true);

  BinaryFileRecord *myRecord = new BinaryFileRecord();
  BinaryFileHeader *binHeader = new BinaryFileHeader();

  ifstream binInfile ("/scratch/perkins/cs3377.bin", ios::in | ios::binary);
  if(binInfile)
  {
  	binInfile.read((char*)binHeader, sizeof(BinaryFileHeader));
	stringstream ss1, ss2, ss3;
	
	ss1  << "Magic: 0x" << hex << binHeader->magicNumber << endl;
  	string s = ss1.str();
	setCDKMatrixCell(myMatrix, 1, 1, s.c_str());;

	ss2 << "Version: "<< binHeader->versionNumber << endl;
  	s = ss2.str();
	setCDKMatrixCell(myMatrix, 1, 2, s.c_str());

	ss3 << "numRecords= " << binHeader->numRecords << endl;
	s = ss3.str();
	setCDKMatrixCell(myMatrix, 1, 3, s.c_str());
	
	int row = 2, col = 1;

	while(!binInfile.eof())
	{
	   binInfile.read((char*)myRecord, sizeof(BinaryFileRecord));	
 	   stringstream ss4, ss5;

	   ss4 << myRecord->stringBuffer << endl;
	   string s = ss4.str();
	   setCDKMatrixCell(myMatrix, row, col+1, s.c_str());
	   
	   ss5 << "strlen: " << strlen(myRecord->stringBuffer)<< endl;
	   s = ss5.str();
	   setCDKMatrixCell(myMatrix, row, col, s.c_str());

	   row++;
	}
 	binInfile.close();
 }
 else 
 	std::cout<< "ERROR: cannot find binary file" << std::endl;
 drawCDKMatrix(myMatrix, true);    
 unsigned char x;
 std::cin >> x;

 endCDK();
 return 0;
}
