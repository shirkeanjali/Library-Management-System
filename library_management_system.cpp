#include<iostream>
#include<fstream>
#include <sstream>
#include <string>
using namespace std;

//admin file: admin username phone password
//student file: student username phone password
//issued_books: bookcode student_username

void main_menu();
void interface1();
void interface2();

void admin_login(){
    string username,password;
    long long int phone; 
    string target_phone;
    string target_password;
    bool isPhone=false;

    try{
    cout<<"Enter your login phone number: ";
    cin>>target_phone;

    if (target_phone.length() != 10) {
        throw invalid_argument("Phone number must be exactly 10 digits.");
    }

    long long int phone1=stoll(target_phone);

    ifstream file("admin.txt");

    if(!file){
        cout<<"No account found!!";
        main_menu();
        return;
    }

    while(file>>username>>phone>>password){
        if(phone1==phone){
            cout<<"Enter password: ";
            cin>>target_password;
            if(target_password==password){
                isPhone=true;
            }
        }else{
            isPhone;
        }
    }
    file.close();
    }catch(const invalid_argument &e){
        cout<<"Invalid value."<<endl;
        cin.clear();
        main_menu();
    }
        
    if(isPhone){
        interface1();
    }else{
        char select;
        cout<<"Invalid password!!"<<endl;
        cout<<"Do you want to re-enter the credentials?(y/n): ";
        cin>>select;
        if(select=='y'){
           admin_login();
        }else{
           main_menu();
        }
    }
}

void create_acc(){
    string username,password,phone_str;
    fstream file;
    
    file.open("admin.txt",ios::app);

    if(!file){
        cout<<"No account found!!";
        interface1();
        return;
    }

    try{
    cout<<"Enter username\n(Note: Do not use space while choosing username and use lowercase alphabets only): ";
    cin>>username;
    cin.ignore();

    cout<<"Enter phone number: ";
    cin>>phone_str;

    if (phone_str.length() != 10) {
            throw invalid_argument("Phone number must be exactly 10 digits.");
        }

    long long int phone=stoll(phone_str);

    cout<<"Set a password: ";
    cin>>password;

    file<<username<<" "<<phone<<" "<<password<<endl;

    cout<<"Account created successfully!!"<<endl;
    interface1(); 

    }catch(const invalid_argument &e){
        cout<<"Invalid value.Oops you will have to re-fill the credentials!!";
        cin.clear(); 
        interface1();
    }

    file.close();
}

void delete_acc(){
    string target_phone;
    string username,password;
    long long int phone;
    bool found=false;

    cout<<"Enter the phone number you want to delete: ";
    cin>>target_phone;

    ifstream file("admin.txt");
    ofstream tempFile("temp.txt");

    if(!file){
        cout<<"No account found!!";
        interface1();
        return;
    }
    
    try{
        if(target_phone=="0000000000"){
            cout<<"Cannot delete!!Default admin"<<endl;
            main_menu();
        }

        if (target_phone.length() != 10 ) {
            throw invalid_argument("Phone number must be exactly 10 digits.");
        }

        long long int phone1=stoll(target_phone);

        while(file>>username>>phone>>password){
            if(phone1!=phone){
                tempFile<<username<<" "<<phone<<" "<<password<<endl;
            }else{
                found=true;
            }
        }
    }catch(const invalid_argument &e){
        cout<<"Invalid value.Oops you will have to re-fill the credentials!!";
        cin.clear();
        interface1();
    }

    file.close();
    tempFile.close();
        
    remove("admin.txt");
    rename("temp.txt","admin.txt");

    if(found){
        cout<<"Account deleted successfully!!"<<endl;
        interface1();
    }else{
        cout<<"Account not found!!"<<endl;
        interface1();
    }
}

void view_student_accounts(){
    fstream file("student.txt");
        
    if(!file){
        cout<<"No account found!!";
        interface1();
        return;
    }

    string line;

    while(getline(file,line)){
        cout<<line<<endl;
    }

    file.close();

    interface1();
}

void view_books(){
    fstream file;

    string line;

    file.open("books.txt",ios::in);

    if(!file){
        cout<<"No books found!!";
        interface1();
        return;
    }

    while(getline(file,line)){
        cout<<line<<endl;
    }

    file.close();

    interface1();
}

void issued_books(){
    string line;

    fstream file;

    file.open("issued_books.txt",ios::in);

    if(!file){
        cout<<"No issued books found!!";
        interface1();
        return;
    }
   
    while(getline(file,line)){
        cout<<line<<endl;
    }
        
    file.close();

    interface1();
}

void add_new_book(){
    string bookcode;
    string bookname,author;
    
    try{
    cout<<"Enter the code of the book to be added: ";
    cin>>bookcode;

    int bookcode1=stoi(bookcode);
    cin.ignore();

    cout<<"Enter the name of book: ";
    getline(cin,bookname);

    cout<<"Enter the name of author: ";
    getline(cin,author);

    fstream file;

    file.open("books.txt",ios::app);
        
    if(!file){
        cout<<"Error occured!!";
        interface1();
        return;
    }
        
    file<<bookcode<<","<<bookname<<","<<author<<endl;
    cout<<"Book added successfully!!"<<endl;

    file.close();
    interface1();
    }catch(const invalid_argument &e){
        cout<<"Invalid value.Oops you will have to re-fill the credentials!!";
        cin.clear();
        interface1();
    }
}

void delete_book(){
    int target_bookcode;
    string line;
    bool found=false;

    cin.clear();
    cout<<"Enter the book code of the book to be deleted: ";
    cin>>target_bookcode;

    if(!cin){
        cout<<"Incorrect book code!!"<<endl;
        interface1();
        return;
    }

    ifstream file("books.txt");
    ofstream tempfile("tempbook.txt");

    if(!file){
        cout<<"Error occured!!";
        interface1();
        return;
    }

    while(getline(file,line)){
        stringstream ss(line);//hum ek string ko alag-alag parts me todne ke liye use kar rahe hain,
        //jaise hum ek sentence ko words me todte hain.
        string bookcode_str;
        getline(ss, bookcode_str, ',');  // Get the book code (before the first comma)
        //getline(ss, variable, delimiter)

        int bookcode = stoi(bookcode_str);

        if(target_bookcode==bookcode){
            found=true;
            continue;
            }
            tempfile << line << "\n";
       }

    cout<<found<<endl;
        
    tempfile.close();
    file.close();

    if (found) {
        remove("books.txt");             
        rename("tempbook.txt","books.txt"); 
        cout << "Book with code " << target_bookcode << " deleted successfully!!\n";
        interface1();
        } else {
        remove("tempbook.txt"); 
        cout << "Book with code " << target_bookcode << " not found!!\n";
        interface1();
    }
}

//User Functions

void user_login(){
    string student_username,user_password;
    long long int user_phone;
    string target_user_phone;
    string target_user_password;
    bool isUserPhone=false;
    
    try{
        cout<<"STUDENT LOGIN."<<endl;
        cout<<"Enter your login phone number: ";
        cin>>target_user_phone;

        if (target_user_phone.length() != 10) {
            throw invalid_argument("Phone number must be exactly 10 digits.");
        }

        long long int phone = stoll(target_user_phone);
        cin.ignore();

        ifstream file("student.txt");

        if(!file){
            cout<<"No account found!!";
            main_menu();
            return;
        }

        while(file>>student_username>>user_phone>>user_password){
            if(phone==user_phone){
                cout<<"Enter password: ";
                cin>>target_user_password;
                if(target_user_password==user_password){
                    isUserPhone=true;
                }
            }else{
                isUserPhone;
            }
        }

        file.close();

        if(isUserPhone){
        interface2();
        }else{
        cout<<"Account not found!!"<<endl;
        main_menu();
        }
    }catch(const invalid_argument &e){
        cout<<"Invalid value.Oops you will have to re-fill the credentials!!"<<endl;
        cin.clear();
        main_menu();
    }
}

void create_useracc(){
    string student_username,user_password;
    string user_phone;
    
    try{
        fstream file;
        file.open("student.txt", ios::app);

        if(!file){
            cout<<"No account found!!";
            main_menu();
            return;
        }

        cout<<"Enter username(Note: Do not use space while selecting username): ";
        cin>>student_username;
        cin.ignore();

        cout<<"Enter phone number: ";
        cin>>user_phone;

        if (user_phone.length() != 10) {
            throw invalid_argument("Phone number must be exactly 10 digits.");
        }

        long long int phone1 = stoll(user_phone);

        cout<<"Set a password: ";
        cin>>user_password;

        file<<student_username<<" "<<user_phone<<" "<<user_password<<endl;    

        file.close();

        cout<<"Account created successfully!!"<<endl;

        main_menu();
    }catch(const invalid_argument &e){
        cout<<"Invalid value. Oops, you will have to re-fill the credentials!!"<<endl;
        cin.clear();
        cin.ignore();  // Clear the input buffer
        main_menu();
    }
}

void search_books(){
    string target_bookname;
    string line;
    bool found = false;
    string book_code, book_name, author;

    cout << "Enter the book name: ";
    cin.ignore();
    getline(cin,target_bookname);

    fstream file("books.txt");

    if (!file) {
        cout << "Something went wrong!" << endl;
        interface2();
        return;
    }

    while (getline(file, line)) {
        stringstream ss(line);  // Split the line using stringstream

        getline(ss, book_code, ',');  // Extract book code
        getline(ss, book_name, ',');  // Extract book name
        getline(ss, author, ',');     // Extract author (not used in comparison)

        if (target_bookname == book_name) {
            found = true;
            cout << "Book \"" << book_name << "\" is available. It has code " << book_code << " and author " << author << "." << endl;
            break;  // No need to check further once the book is found
        }
    }

    if (!found) {
       cout << "Book \"" << target_bookname << "\" not found." << endl;
       interface2();
    }

    file.close();
}

void my_books(){
    string student_username;
    int bookcode;
    string target_username;

    cout<<"Enter your username: ";
    cin>>target_username;

    fstream file;
    
    string line;

    file.open("issued_books.txt",ios::in);

    if(!file){
        cout<<"Something went wrong!!";
        interface2();
        return;
    }

    while(file>>bookcode>>student_username){
        if(target_username==student_username){
            cout<<student_username<<" is issued the book with code: "<<bookcode;
            interface2();
        }else{
            cout<<"No book issued!!"<<endl;
            interface2();
        }
    }
}

void user_books(){
    fstream file;

    string line;

    file.open("books.txt",ios::in);

    if(!file){
        cout<<"No books found!!";
        interface2();
        return;
    }

    while(getline(file,line)){
        cout<<line<<endl;
    }

    file.close();

    interface2();
}

void take_book(){
    string student_username;
    int bookcode;
    int target_bookcode;

    cout<<"Enter the code(Book code ranges from(101 to 160): ";
    cin>>target_bookcode;

    if(!cin || cin.fail() || target_bookcode < 101 || target_bookcode > 160){
        cin.clear();
        cout<<"You have entered invalid book code!!"<<endl;
        interface2();
        return;
    }

    ifstream file("issued_books.txt");
    bool found = false;

    if(!file){
        cout<<"Something went wrong!!";
        interface2();
        return;
    }
        
    while(file>>bookcode>>student_username){
       if(target_bookcode==bookcode){
        cout<<"Book not available!! Try after few days!!"<<endl;
        found=true;
        break;
       }
    }

    file.close();

    if (found) {
        interface2();
        return;  // Exit if book is already issued
    }

    ofstream ofile;

    ofile.open("issued_books.txt", ios::app);

    if (!ofile) {
        cout << "Error!!" << endl;
        interface2();
        return;
    }

    cout<<"Enter your username: ";
    cin>>student_username;

    ofile<<target_bookcode<<" "<<student_username<<endl;

    cout << "Book issued successfully!" << endl;

    ofile.close();

    interface2();
}

void return_book(){
    string student_username;
    int target_bookcode;
    int bookcode;

    cout<<"Enter the code of book you want to return: ";
    cin>>target_bookcode;

    if(!cin){
        cout<<"Invalid input!!"<<endl;
        interface2();
        return;
    }

    ifstream file("issued_books.txt");
    ofstream tempfile("garbage.txt",ios::app);

    string line;
    bool found=false;
        
    if(!file){
        cout<<"No account found!!";
        interface2();
        return;
    }

    if(!tempfile){
        cout<<"Something went wrong1!!";
        interface2();
        return;
    }

    while(file>>bookcode>>student_username){
        if(target_bookcode!=bookcode){
        tempfile<<bookcode<<" "<<student_username;
       }else{
        found=true;
       }
    }

    file.close();
    tempfile.close();
        
    remove("issued_books.txt");
    rename("garbage.txt","issued_books.txt");

    if(found){
        cout<<"Book returned successfully!!"<<endl;
        interface2();
        }else{
        cout<<"Something went wrong2!!"<<endl;
        interface2();
    }
}

void delete_user_acc(){
    long long int target_user_phone;

    cout<<"Enter the phone number you want to delete: ";
    cin>>target_user_phone;
         
    ifstream file("student.txt");
    ofstream tempFile("example.txt");

    if(!file){
        cout<<"Something went wrong!!";
        interface2();
        return;
    }

    string student_username,user_password;
    long long int user_phone;
    bool found=false;

    while(file>>student_username>>user_phone>>user_password){
        if(target_user_phone!=user_phone){
            tempFile<<student_username<<" "<<user_phone<<" "<<user_password<<endl;
        }else{
            found=true;
        }
    }

    file.close();
    tempFile.close();
        
    remove("student.txt");
    rename("example.txt","student.txt");

    if(found){
        cout<<"Account deleted successfully!!"<<endl;
        main_menu();
        return;
    }else{
        cout<<"Account not found!!"<<endl;
        interface2();
        return;
    }
}

// void interface1(){
//     int choice;
//     cout<<"\nSelect any one of the (1,2,3,4,5,6,7,8): ";
//     cout<<"\n1.Create account.\n2.Delete account.\n3.View student account.\n4.View books.\n5.View Issued books.\n6.Add new boooks.\n7.Delete books.\n8.Return to main menu.\n";
//     cout<<"Enter your choice here: ";
//     cin>>choice;

//     if(choice==1){
//         create_acc();
//     }else if(choice==2){
//         delete_acc();
//     }else if(choice==3){
//         view_student_accounts();
//     }else if(choice==4){
//         view_books();
//     }else if(choice==5){
//         issued_books();
//     }else if(choice==6){
//         add_new_book();
//     }else if(choice==7){
//         delete_book();
//     }else if(choice==8){
//         main_menu();
//     }else{
//         cout<<"Invalid value entered!!"<<endl;
//         interface1();
//     }
// }

// void interface2(){
//     int choice1;
//     cout<<"Select the any of the options given below(1,2,3,4,5,6,7,8): "<<endl;
//     cout<<"1.Delete account.\n2.Search books.\n3.View books.\n4.View my Issued books.\n5.Borrow books.\n6.Return book.\n7.Return to main menu."<<endl;
//     cout<<"Enter your choice here: ";
//     cin>>choice1;

//     if(choice1==1){
//         delete_user_acc();
//     }else if(choice1==2){
//         search_books();
//     }else if(choice1==3){
//         user_books();
//     }else if(choice1==4){
//         my_books();
//     }else if(choice1==5){
//         take_book();
//     }else if(choice1==6){
//         return_book();
//     }else if(choice1==7){
//         main_menu();
//     }else{
//         cout<<"Invalid value entered!!"<<endl;
//         interface2();
//     }
// }

// void main_menu(){
//     int option;
//     cout<<"Select the option(1,2,3) from the ones given below:"<<endl;
//     cout<<"1. Librarian \n2. Student \n3. Exit "<<endl;
//     cout<<"Enter your choice here: ";
//     cin>>option;

//     if(option==1){
//         admin_login();
//         return;
//     }else if(option==2){
//         int select;
//         cout<<"Select the number to proceed further: \n1.Create new account.\n2.Login"<<endl;
//         cin>>select;
//             if(select==1){
//                 create_useracc();
//             }else if(select==2){
//                 user_login();
//             }else{
//                 cout<<"Invalid value!!"<<endl;
//                 main_menu();
//             }
//         return;
//     }else if(option==3){
//         return;
//     }else{
//         cout<<"Enter valid option!!"<<endl;
//         main_menu();
//     }
// }

// ==============================================
// Function: interface1
// Purpose: Handles the menu options for the librarian
// ==============================================
void interface1() {
    int choice;  // Variable to store the user's menu selection
    cout << "\n=========================================\n";
    cout << "Select any one of the (1, 2, 3, 4, 5, 6, 7, 8): \n";
    cout << "\n1. Create account.\n2. Delete account.\n3. View student account.\n4. View books.\n5. View Issued books.\n6. Add new books.\n7. Delete books.\n8. Return to main menu.\n";
    cout << "=========================================\n";
    cout << "Enter your choice here: ";
    cin >> choice;

    // Process the menu choice for the librarian
    if(choice == 1){
        create_acc();
    } else if(choice == 2){
        delete_acc();
    } else if(choice == 3){
        view_student_accounts();
    } else if(choice == 4){
        view_books();
    } else if(choice == 5){
        issued_books();
    } else if(choice == 6){
        add_new_book();
    } else if(choice == 7){
        delete_book();
    } else if(choice == 8){
        main_menu();
    } else {
        cout << "Invalid value entered!!" << endl;
        interface1();  // Recursively call to retry
    }
}

// ==============================================
// Function: interface2
// Purpose: Handles the menu options for the student
// ==============================================
void interface2() {
    int choice1;  // Variable to store the student's menu selection
    cout << "\n=========================================\n";
    cout << "Select any of the options given below (1, 2, 3, 4, 5, 6, 7, 8): \n";
    cout << "=========================================\n";
    cout << "1. Delete account.\n2. Search books.\n3. View books.\n4. View my Issued books.\n5. Borrow books.\n6. Return book.\n7. Return to main menu.\n";
    cout << "=========================================\n";
    cout << "Enter your choice here: ";
    cin >> choice1;

    // Process the menu choice for the student
    if(choice1 == 1){
        delete_user_acc();
    } else if(choice1 == 2){
        search_books();
    } else if(choice1 == 3){
        user_books();
    } else if(choice1 == 4){
        my_books();
    } else if(choice1 == 5){
        take_book();
    } else if(choice1 == 6){
        return_book();
    } else if(choice1 == 7){
        main_menu();
    } else {
        cout << "Invalid value entered!!" << endl;
        interface2();  // Recursively call to retry
    }
}

// ==============================================
// Function: main_menu
// Purpose: Displays the main menu and processes user choices
// ==============================================
void main_menu() {
    int option;  // Variable to store the user's main menu selection
    cout << "\n=========================================\n";
    cout << "Select the option (1, 2, 3) from the ones given below:\n";
    cout << "=========================================\n";
    cout << "1. Librarian \n2. Student \n3. Exit\n";
    cout << "=========================================\n";
    cout << "Enter your choice here: ";
    cin >> option;

    // Process the main menu choice
    if(option == 1){
        admin_login();
        return;
    } else if(option == 2){
        int select;
        cout << "Select the number to proceed further: \n1. Create new account.\n2. Login" << endl;
        cout<<"Enter your choice here: ";
        cin >> select;
        if(select == 1){
            create_useracc();
        } else if(select == 2){
            user_login();
        } else {
            cout << "Invalid value!!" << endl;
            main_menu();  // Recursively call to retry
        }
        return;
    } else if(option == 3){
        return;
    } else {
        cout << "Enter valid option!!" << endl;
        main_menu();  // Recursively call to retry
    }
}

int main(){
    cout << "\n=====================================\n";
    cout << "         WELCOME TO LIBRARY SYSTEM       " << endl;
    cout << "=====================================\n";
    main_menu();
    return 0;
}