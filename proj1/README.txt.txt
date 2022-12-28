which OS and compiler (which version)
OS is Microsoft Windows 10 and was coded in the version of visual studio 2019, and the compilation was performed in the command prompt port(cmd).

How to run :
1. Enter the command prompt window (cmd).
2. Enter the saved file path.
3. Enter OOP.exe and file1.txt as input arguments.
4. Run the program.

Class project :
In a class called project, the number that selects the sort_option menu, the number that selects the search menu, and the file_processing, insert, search, and sort_option methods are managed.

main function :
Role to select the menu you want to execute
In the main function, when the user enters 1 on the screen, insert when 2 is entered, search is performed
If you enter 3, sorting option, and if you enter 4, exit.

file_processing :
Role to check for text files and store them in data
When the main function is executed, if the text file entered as an argument is checked for data, the previously stored content is put into the structure vector.

insert :
Role to store entered student information in data
User enters your name, student ID, birth year, department, and phone number and store them in a text file and a structure vector.
The name was made to be re-entered if it was empty or more than 15 digits.
In the case of id, it was also made to re-enter it until it was exactly 10 digits.
The birth year was also re-entered until it reached exactly four digits.
The id made an error message output when duplicated.

search :
Role to search for student data according to the information you want
User enters 1 for name, 2 for student id, 3 to enter the school year, and enter 4 to search according to the department.
Entering 5 outputs all student information according to the selected sorting option. Sorting by name is default.
If user enters a number other than that, user is required to enter the number again.

sort_option :
Role to determine how to sort
User enters 1 for name, 2 for student id,3 to enter the school year, and enter 4 to sort according to the department.
The sorted result is printed in the "Print all" of the search.
If you enter a number other than that, you are required to enter the number again.

