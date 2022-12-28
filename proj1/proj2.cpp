#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// a structure that contains student information
struct Student {
	string name, id, admission, birth, depart, tel;
};

// This class manages several menu.
class project {
	private :
		int option_num = 1; // menu's sorting option number 
		int search_num = 0; // menu's searching option number
		
	public :
		vector <Student> v;
		void file_processing(char* argv);
		void insert(char* argv);
		void search(void);
		void sort_option(void);
};

// This method stores the information of an existing file "file1.txt" in a structure vector.
void project::file_processing(char* argv) {
	string line;

	ifstream ourfile(argv);
	if (ourfile.is_open()) {
		while (getline(ourfile, line)) {
			stringstream ss(line);
			string buffer;
			vector <string> str;

			while (getline(ss, buffer, '|')) {
				str.push_back(buffer);
			}
			Student current;
			current.name = str[0];
			current.admission = str[1];
			current.id = str[2];
			current.birth = str[3];
			current.depart = str[4];
			current.tel = str[5];
			v.push_back(current);
		}
		ourfile.close();
	}
	else
		ofstream ourfile(argv);
}

// This method puts the student's data into a text file.
void project::insert(char* argv) {
	
	Student student;
	cin.ignore();
	while (student.name.size() > 15 || student.name.size() <= 0 || student.name == " ") {
		cout << "Name ? ";
		getline(cin, student.name);
	} 
	while (student.id.size() != 10 || student.id == " ") {
		cout << "Student ID (10 digits) ? "; 
		cin >> student.id;
	}
	
	student.admission = student.id.substr(0, 4);

	while(student.birth.size() != 4) {
		cout << "Birth Year (4 digits) ? ";
		cin >> student.birth;
	}

	cout << "Department ? ";
	cin.ignore();
	getline(cin, student.depart);

	while (student.tel.size() > 12 || student.tel.size() <= 0) {
		cout << "Tel ? ";
		cin >> student.tel;
	}

	// check if the id is redundant and put it in the structure vector.
	for (int i = 0; i < v.size(); i++) {
		if (v[i].id == student.id) {
			cout << "Error : Already inserted\n";
			return;
		}
	}

	v.push_back(student);

	// put the student's data into a text file.
	ofstream myfile(argv, ios::app);
	if (myfile.is_open()) {
		myfile << student.name << '|' << student.admission << '|' << student.id << '|' << student.birth << '|' << student.depart << '|' << student.tel << '\n';
		myfile.close();
	}
	else cout << "Unable to open file";
}

// This function compares student's names.
int cmp1(const void* pa, const void* pb) {
	Student* a = (Student*)pa;
	Student* b = (Student*)pb;
	
	return a->name.compare(b->name);
}

// This function compares student's ids.
int cmp2(const void* pa, const void* pb) {
	Student* a = (Student*)pa;
	Student* b = (Student*)pb;

	return a->id.compare(b->id);
}

// This function compares student's admisson years.
int cmp3(const void* pa, const void* pb) {
	Student* a = (Student*)pa;
	Student* b = (Student*)pb;

	return a->admission.compare(b->admission);
}

// // This function compares student's department names.
int cmp4(const void* pa, const void* pb) {
	Student* a = (Student*)pa;
	Student* b = (Student*)pb;

	return a->depart.compare(b->depart);
}

// This method searchs student's information in the student's vector. 
void project::search(void) { 
	
	// There is no data.
	if (v.empty()) {
		cout << "There is no data yet.\n";
		return;
	}

	cout << "1.Search by name\n2. Search by student ID (10 numbers)\n3. Search by admission year (4 numbers)\n4. Search by department name\n5. List All\n>";
	cin >> search_num; // search's option number

	while (search_num < 1 || search_num > 5) {
		cout << "repeat the number\n";
		cout << "1.Search by name\n2. Search by student ID (10 numbers)\n3. Search by admission year (4 numbers)\n4. Search by department name\n5. List All\n>";
		cin >> search_num; // search's option number
	}

	string search_name = ""; // the data user wants to search
	cout.setf(ios::right);

	switch (search_num) {
	case 1: // // The input student's name is searched from the structure vector.
		cout << "Name keyword? ";
		cin.ignore();
		getline(cin, search_name);
		cout << setw(15) << "Name" << setw(15) << "StudentID" << setw(20) << "Dept" << setw(15) << "Birth Year" << setw(15) << "Tel\n";
		for (int i = 0; i < v.size(); i++) {
			if (v[i].name == search_name) {
				cout << setw(15) << v[i].name << setw(15) << v[i].id << setw(20) << v[i].depart << setw(15) << v[i].birth << setw(15) << v[i].tel << '\n';
			}
		}
		break;
	case 2: // The input student's id is searched from the structure vector.
		cout << "student ID keyword? ";
		cin >> search_name;
		cout << setw(15) << "Name" << setw(15) << "StudentID" << setw(20) << "Dept" << setw(15) << "Birth Year" << setw(15) << "Tel\n";
		for (int i = 0; i < v.size(); i++) {
			if (v[i].id == search_name) {
				cout << setw(15) << v[i].name << setw(15) << v[i].id << setw(20) << v[i].depart << setw(15) << v[i].birth << setw(15) << v[i].tel << '\n';
			}
		}
		break;
	case 3: // The input student's admission year is searched from the structure vector.
		cout << "admission year keyword? ";
		cin >> search_name;
		cout << setw(15) << "Name" << setw(15) << "StudentID" << setw(20) << "Dept" << setw(15) << "Birth Year" << setw(15) << "Tel\n";
		for (int i = 0; i < v.size(); i++) {
			if (v[i].admission == search_name) {
				cout << setw(15) << v[i].name << setw(15) << v[i].id << setw(20) << v[i].depart << setw(15) << v[i].birth << setw(15) << v[i].tel << '\n';
			}
		}
		break;
	case 4: // The input student's department name is searched from the structure vector.
		cout << "department name keyword? ";
		cin.ignore();
		getline(cin, search_name);

		cout << setw(15) << "Name" << setw(15) << "StudentID" << setw(20) << "Dept" << setw(15) << "Birth Year" << setw(15) << "Tel\n";
		for (int i = 0; i < v.size(); i++) {
			if (v[i].depart == search_name) {
				cout << setw(15) << v[i].name << setw(15) << v[i].id << setw(20) << v[i].depart << setw(15) << v[i].birth << setw(15) << v[i].tel << '\n';
			}
		}
		break;
	case 5: // prints all data stored in the selected sorting method.
		switch (option_num) {
		case 1:
			qsort(&v[0], v.size(), sizeof(v[0]), cmp1);
			break;
		case 2:
			qsort(&v[0], v.size(), sizeof(v[0]), cmp2);
			break;
		case 3:
			qsort(&v[0], v.size(), sizeof(v[0]), cmp3);
			break;
		case 4:
			qsort(&v[0], v.size(), sizeof(v[0]), cmp4);
			break;
		}
		cout << setw(15) << "Name" << setw(15) << "StudentID" << setw(20) << "Dept" << setw(15) << "Birth Year" << setw(15) << "Tel\n";
		for (int i = 0; i < v.size(); i++) {
			cout << setw(15) << v[i].name << setw(15) << v[i].id << setw(20) << v[i].depart << setw(15) << v[i].birth << setw(15) << v[i].tel << '\n';
		}
		break;
	default:
		cout << "repeat the number\n";
		cout << "1.Search by name\n2. Search by student ID (10 numbers)\n3. Search by admission year (4 numbers)\n4. Search by department name\n5. List All\n>";
		cin >> search_num;
		break;
	}
}

void project::sort_option(void) { 
	cout << "1.Sort by name\n2. Sort by student ID (10 numbers)\n3. Sort by admission year\n4. Sort by department name\n>";
	cin >> option_num; 
	while (option_num < 1 || option_num > 4) {
		cout << "Invalid number. Please enter again the number\n";
		cout << "1.Sort by name\n2. Sort by student ID (10 numbers)\n3. Sort by admission year\n4. Sort by department name\n>";
		cin >> option_num;
	}
	cout << "Go back to the main menu, after selecting the sorting option..\n";
}

int main(int argc, char *argv[]) {

	project proj;

	proj.file_processing(argv[1]);
	
	int menu = 0;

	while (menu != 4) { 
		cout << "1. Insertion\n2. Search\n3. Sorting Option\n4. Exit\n>";
		cin >> menu;
		if (menu == 1) proj.insert(argv[1]);
		else if (menu == 2) proj.search();
		else if (menu == 3) proj.sort_option();
	}
	cout << "program is over.";
	return 0;
}