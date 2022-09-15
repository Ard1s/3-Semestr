#include <iostream> 
#include <string> 
#include <fstream>  


using namespace std;

int main()
{
	int exit = 1;
	while (exit != 0)
	{

		string word;
		string verb;
		string preposition;


		int EXITCODE = 1;
		int found = 1;

		while (EXITCODE == 1)
		{

			ifstream myfile1("a.txt", ios::in);


			if (!myfile1)
				cout << "Sorry! Could not open file. Program ending ..." << endl << "Program ended with exit code: ";


			cout << "Which verb would you like to check? (no spaces and no preposition): ";
			cin >> verb;
			int found = 1;

			while (!myfile1.eof())
			{
				myfile1 >> word;


				if (word == verb)
				{
					cout << "verb  " << verb << "  COI  " << endl;
					cout << "Thank you for using this program" << endl;
					found = 0;
				}

			}
			myfile1.close();

			if (found == 1)
			{
				string verb;
				cout << "The verb is not in the list, please try again to make it in the NewVerb.dat file :  ";
				cin >> verb;
				ofstream myfile2("NewVerb.dat", ios::out | ios::app);


				if (!myfile2)
				{
					cout << "The wrong file" << endl;
					cin >> exit;
				}

				myfile2 << endl << verb << "	 " << verb;
				myfile2.close();

				cout << "It has been written into the file Newverb.dat successfully " << endl << endl;

			}

			string L;
			int N, Len;
			cout << "Please enetr the object:  " << preposition << endl;
			cin >> preposition;
			N = preposition.length() - 1;
			Len = verb.length();




			if (preposition.substr(N) == "e")
			{


				cout << "for the verb  " << verb << " with  " << preposition << " always use: der for male object" << endl;
				cout << "The correct form is" << endl;
				cout << "der  " << verb << endl;
				if (verb == "Butter" || "Leiter" || "Mutter")
					cout << "die" << verb << endl;
			}
			else if (preposition.substr(N) == "a")
			{

				cout << "for the verb  " << verb << " with  " << preposition << " always use: das for neuter object" << endl;
				cout << "The correct form is" << endl;
				cout << "das  " << verb << endl;
				if (verb == "Irrtum" || "Reichtum")
					cout << "der" << verb << endl;

				else
				{

					cout << "for the verb  " << verb << " with  " << preposition << " always use: die for female object" << endl;
					cout << "The correct form is" << endl;
					cout << "die  " << verb << endl;
					if (verb == "Kaffee" || "Klee" || "Tee" || "See" || "Schnee")
						cout << "der" << verb << endl;

				}


			}

			cout << endl;



			cout << "(0 for exit) - (1 else to continue)" << endl;
			cout << "Program ended with exit code: ";
			cin >> EXITCODE;

		}
	}
	return 0;
}
