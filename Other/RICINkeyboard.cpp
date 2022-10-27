#include <iostream>
using namespace std;

int main()
{	cout << "Center photoresistors against the two spots THEN press enter and connect this\n"
	     << "apparatus on the receiving machine. (Set terminal colors to white on black.)";
	for(int a = 0; a < 14; a++) {cout << "\n";}
	cout << "           ###        ###\n\n\n\n\n\n\n";
	char wait[1]; cin.getline(wait, 1);
	
	for(int a = 0; a < 50; a++) {cout << "\n";}
	cout << "                                               Press enter to generate 10 bytes.";
	cin.getline(wait, 1);
	
	long long timing = 30000000; //30,000,000 ok for 2.26Ghz, increase it if your spy-box is fancy.
	for(;;)
	{	//Scrolls down through emptyness.
		for(int a = 0; a < 80; a++)
		{	cout << "\n";
			
			//Wastefully consumes time. This too occupies RAM but quietly.
			for(int waste = 0; waste <= 10000000; waste++) {}
		}
		
		//n = bytes to generate (currently 10 bytes)
		for(int n = 0; n < 10; n++)
		{	cout << "                      ###";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n"; // 0
			
			cout << "                      ###";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n"; // 0
			
			cout << "           ###";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n"; // 1
			
			cout << "                      ###";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n"; // 0
			
			cout << "           ###";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n"; // 1
			
			cout << "                      ###";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n"; // 0
			
			cout << "           ###";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n"; // 1
			
			cout << "           ###";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n";
			for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n"; // 1
		}
		
		//Writing 2 bits to end the stream.
		cout << "           ###";
		for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n";
		for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n"; // 1
		
		cout << "           ###";
		for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n";
		for(int waste = 0; waste <= timing; waste++) {} cout << "\n\n"; // 1
		
		cout << "\n\n\n\n\n\n\n";
		cout << "                                         Press enter to generate 10 bytes again.";
		char wait[1]; cin.getline(wait, 1);
	}
}
