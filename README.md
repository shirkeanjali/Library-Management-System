# Library Management System

## Overview
This is a simple Library Management System implemented in C++ that allows librarians and students to manage books efficiently.
The system supports functionalities such as book issuance, return, account management, and book search.

## Features
### Librarian Functions:
- Create student accounts
- Delete student accounts
- View student details
- View all books
- View issued books
- Add new books
- Delete books

### Student Functions:
- Create an account
- Delete their own account
- Search for books
- View available books
- View their issued books
- Borrow books
- Return books

## File Usage
The system uses the following files to store data:
- `books.txt` - Stores book details (book code, name, author)
- `issued_books.txt` - Stores issued book records (book code, student username)
- `student.txt` - Stores student details (username, phone number, password)

## How to Use
1. Run the program.
2. Select user type: Librarian or Student.
3. Librarians can log in and manage books and accounts.(Default admin phone number: 0000000000 and password: 1234)
4. Students can log in, search for books, borrow, and return them.
5. Follow the on-screen prompts to perform desired actions.

## Compilation and Execution
To compile and run the program:
```bash
 g++ library_system.cpp -o library_system
 ./library_system
```

## Notes
- The system uses file-based storage (no database required).
- Users must enter correct book codes and credentials for transactions.
- Error messages guide users in case of incorrect inputs.
