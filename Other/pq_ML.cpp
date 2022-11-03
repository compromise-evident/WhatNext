/// pqML - train a model to recognize 18-digit primes, all data unique.
/// Nikolay Valentinovich Repnitskiy - License: WTFPLv2+ (wtfpl.net)


/*Version 1.0.0. Purpose: if primes can be recognized, so might semiprimes. And
if that, perhaps their factors. Otherwise, this would serve as pretty-good-proof
that semiprimes are without reversal shortcuts; desirable  outcome  is  failure!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The next version is called pqMLzero--a natural approach that is a neural network
with activity-based gain  and  inactivity-based loss.  It's a copy of pqML which
interrupts to slow fire spread of lazy neurons, and advance it for busy neurons.
pqMLzero  differs in that neuron value also determines how many neurons to hash.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
How to run the program  -  Software package repositories for GNU+Linux operating
systems have all the tools you can imagine. Open a terminal and use this command
as root to install Geany and g++ on your computer: apt install geany g++   Geany
is a fast & lightweight text editor and Integrated Development Environment where
you can write and run code. g++ is the GNU compiler for C++ which allows written
code to run. The compiler operates in the background and displays errors in your
code as you will see in the lower Geany box. Make a new folder somewhere on your
machine. Paste this code into Geany. For clarity in auditing, enable indentation
guides: go to View >> Show Indentation Guides. Save the document as anything.cpp
within the newly-created folder. Use these shortcuts to run the program: F9, F5.
You may paste over this code with other  .cpp files, or open a new tab & repeat.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
How to make an executable with g++  -  Save this program as anything.cpp, open a
terminal, and type g++ then space. Drag & drop this saved file into the terminal
and its directory will be  appended to your pending entry. Click on the terminal
and press enter.   a.out now resides in the user directory, you may rename it to
anything.  To run that executable, simply drag and drop it into a terminal, then
click on the terminal and press enter.  Reminder:  executable's effect-directory
is the user directory on your machine, for example:  /home/nikolay    Enjoy. */

#include <fstream>
#include <iostream>
#include <sys/stat.h> //For mkdir() (creating folders.)
using namespace std;

int main()
{	cout << "\n(pq Machine Learning)\n\n"
	
	     << "(1) Train\n"
	     << "(2) Test\n\n"
	
	     << "Enter option: ";
	
	int user_option; cin >> user_option;
	ifstream in_stream;
	ofstream out_stream;
	static bool sieve[1000000000] = {1, 1};
	
	
	
	
	
	//_____________________________________________________________________________________________________________________
	//________________________________________________________Train_______________________________________________________/
	if(user_option == 1)
	{	//Checks if training data already exists.
		bool existence_of_file_Training_data = true;
		in_stream.open("./pqML_data/Training_data");
		if(in_stream.fail() == true) {existence_of_file_Training_data = false;}
		in_stream.close();
		
		//Creates training data if none exists.
		if(existence_of_file_Training_data == false)
		{	cout << "\nCreating training data. Wait 7 hours...\n\n";
			
			//Boolean sieve of Eratosthenes. Zeros are mapped to prime elements. Laughably, bool[] & char[] both consume 1 Byte.
			for(int prime = 2; prime < 31623; prime++) //31,623 is sqrt(1,000,000,000) Sieve is 10^9 because 18-digit candidates must be tested with primes up to 10^9.
			{	for(; sieve[prime] == 1;) {prime++;} //Moves up the list if number already marked off.
				for(int a = prime + prime; a < 1000000000; a += prime) {sieve[a] = 1;} //Marks multiples (composites.)
			}
			
			//Creates 5000 random 18-digit composites (~15 minutes.)
			long primes    [5000] = {0};
			long composites[5000] = {0};
			int  composites_write_bookmark = 0;
			int  primes_write_bookmark     = 0;
			srand(time(0));
			
			for(; composites_write_bookmark < 5000;)
			{	//..........Creates 18-digit candidate.
				long candidate = 0;
				long multiplier = 1;
				for(int a = 0; a < 18; a++)
				{	long place_value = (rand() % 10);
					place_value *= multiplier;
					multiplier *= 10;
					
					candidate += place_value;
				}
				
				if(candidate < 100000000000000000) {candidate += 100000000000000000;}
				
				//..........Tests, not adjusts for compositeness. If prime, breaks out of for() & creates new candidate.
				long prime_divisor = 0;
				for(int a = 0; a < 1000000000; a++)
				{	if(sieve[a] == 0)
					{	if((candidate % prime_divisor) == 0)
						{	//..........Writes composite to composites[].
							composites[composites_write_bookmark] = candidate;
							composites_write_bookmark++;
							break;
						}
					}
					
					prime_divisor++; //..........Actually hops with zeros in sieve.
				}
			}
			
			//Creates 5,000 random 18-digit primes (~7 hours.)
			for(; primes_write_bookmark < 5000;)
			{	//..........Creates 18-digit candidate.
				long candidate = 0;
				long multiplier = 1;
				for(int a = 0; a < 18; a++)
				{	long place_value = (rand() % 10);
					place_value *= multiplier;
					multiplier *= 10;
					
					candidate += place_value;
				}
				
				if(candidate < 100000000000000000) {candidate += 100000000000000000;}
				
				//..........Adjusts for primality. for() is not exited until candidate is made prime.
				if((candidate % 2) == 0) {candidate++;} //..........Makes candidate odd.
				long prime_divisor = 0;
				for(int a = 0; a < 1000000000; a++)
				{	if(sieve[a] == 0)
					{	if((candidate % prime_divisor) == 0)
						{	candidate += 2;
							a = -1;
							prime_divisor = 0;
							continue;
						}
					}
					
					prime_divisor++; //..........Actually hops with zeros in sieve.
				}
				
				//..........Writes prime to primes[].
				primes[primes_write_bookmark] = candidate;
				primes_write_bookmark++;
				
				cout << primes_write_bookmark << " of 5000\n";
			}
			
			//Writes training data to file "Training_data" (alternates writing composite, prime, composite, prime...)
			mkdir("pqML_data",  0777); //Creates a folder.
			out_stream.open("./pqML_data/Training_data");
			for(int a = 0; a < 5000; a++)
			{	out_stream << composites[a] << "\r\n";
				out_stream << primes    [a] << "\r\n";
			}
			out_stream.close();
		}
		
		//Checks if model already exists.
		bool existence_of_file_Model = true;
		in_stream.open("./pqML_data/Model");
		if(in_stream.fail() == true) {existence_of_file_Model = false;}
		in_stream.close();
		
		/*Creates model if missing (92 neurons total.)
		
		
		in  h1  h2  h3  h4  out
		
		o   o   o   o   o
		o   o   o   o   o
		o   o   o   o   o
		o   o   o   o   o
		o   o   o   o   o
		o   o   o   o   o
		o   o   o   o   o
		o   o   o   o   o
		o   o   o   o   o   o
		o   o   o   o   o   o
		o   o   o   o   o
		o   o   o   o   o
		o   o   o   o   o
		o   o   o   o   o
		o   o   o   o   o
		o   o   o   o   o
		o   o   o   o   o
		o   o   o   o   o
		
		Input: 18 neurons. Hidden layers: 4 (18 neurons each.)
		Output neurons: 2--classes "prime" and "composite."
		Each neuron is 1 of 95 different hash algorithms.
		This way, neurons have bias, they affect, and are
		affected. Hashing is a simplification of "neuron
		connected to neurons before itself" and "weight."
		
		Each input  neuron takes a hash of the 18-digit input.
		Each h1     neuron takes a hash of the previous column.
		Each h2     neuron takes a hash of the previous column.
		Each h3     neuron takes a hash of the previous column.
		Each h4     neuron takes a hash of the previous column.
		Each output neuron takes a hash of the previous column.
		
		
		*/
		if(existence_of_file_Model == false)
		{	srand(time(0));
			
			out_stream.open("./pqML_data/Model");
			for(int a = 0; a < 92; a++)
			{	int neuron = (rand() % 95);
				out_stream << char(neuron + 32);
			}
			out_stream.close();
		}
		
		///Trains on data.
		cout << "\nTraining model. You may exit and continue at any time...\n\n";
		
		//..........Loads model.
		in_stream.open("./pqML_data/Model");
		char Model[92];
		for(int a = 0; a < 92; a++) {in_stream.get(Model[a]); Model[a] -= 32;}
		in_stream.close();
		
		//..........Loads training data.
		in_stream.open("./pqML_data/Training_data");
		char training_data[180000];
		int training_data_write_bookmark = 0;
		char garbage_byte;
		for(int a = 0; a < 10000; a++)
		{	for(int b = 0; b < 18; b++)
			{	in_stream.get(training_data[training_data_write_bookmark]);
				training_data[a] -= 48; //..........-48 means actual value of digit.
				
				training_data_write_bookmark++;
			}
			in_stream.get(garbage_byte); //..........Skips \r
			in_stream.get(garbage_byte); //..........Skips \n
		}
		in_stream.close();
		
		//..........Training.
		
	}
	
	
	
	
	
	//_____________________________________________________________________________________________________________________
	//________________________________________________________Test________________________________________________________/
	else if(user_option == 2)
	{	//Checks if model is missing.
		
		cout << "\nPreparing, wait a minute...\n\n";
		//Needs the sieve; option 2 generates random primes AND composites to be run through the model.
		//Boolean sieve of Eratosthenes. Zeros are mapped to prime elements. Laughably, bool[] & char[] both consume 1 Byte.
		for(int prime = 2; prime < 31623; prime++) //31,623 is sqrt(1,000,000,000) Sieve is 10^9 because 18-digit candidates must be tested with primes up to 10^9.
		{	for(; sieve[prime] == 1;) {prime++;} //Moves up the list if number already marked off.
			for(int a = prime + prime; a < 1000000000; a += prime) {sieve[a] = 1;} //Marks multiples (composites.)
		}
		
		//Loops test ("press enter to test another prime & composite".)
		//Generates 1 prime AND 1 composite (per test.)
		
		
	}
	
	else {cout << "\nInvalid option, program ended.\n"; return 0;}
}
