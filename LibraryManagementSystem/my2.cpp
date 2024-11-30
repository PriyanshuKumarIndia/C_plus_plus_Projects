#include <bits/stdc++.h>
using namespace std;

// Class representing a Book
class Book
{
public:
    string title;
    string author;
    bool isAvailable;

    Book(string t, string a) : title(t), author(a), isAvailable(true) {}

    void display()
    {
        cout << "Title: " << title << ", Author: " << author
             << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

// Class representing a User
class User
{
public:
    string username;
    string password;

    User(string u, string p) : username(u), password(p) {}

    void display()
    {
        cout << "Username: " << username << endl;
    }
};

// Class representing the Library Management System
class LibrarySystem
{
private:
    vector<Book> books;
    vector<User> users;

public:
    LibrarySystem()
    {
        loadBooks();
        loadUsers();
    }

    ~LibrarySystem()
    {
        saveBooks();
        saveUsers();
    }

    void loadBooks()
    {
        ifstream inFile("books.txt");
        if (!inFile)
            return;

        string title, author, availability;
        while (getline(inFile, title) && getline(inFile, author) && getline(inFile, availability))
        {
            Book book(title, author);
            book.isAvailable = (availability == "1");
            books.push_back(book);
        }
        inFile.close();
    }

    void saveBooks()
    {
        ofstream outFile("books.txt");
        for (const auto &book : books)
        {
            outFile << book.title << endl;
            outFile << book.author << endl;
            outFile << (book.isAvailable ? "1" : "0") << endl;
        }
        outFile.close();
    }

    void loadUsers()
    {
        ifstream inFile("users.txt");
        if (!inFile)
            return;

        string username, password;
        while (getline(inFile, username) && getline(inFile, password))
        {
            users.push_back(User(username, password));
        }
        inFile.close();
    }

    void saveUsers()
    {
        ofstream outFile("users.txt");
        for (const auto &user : users)
        {
            outFile << user.username << endl;
            outFile << user.password << endl;
        }
        outFile.close();
    }

    void addUser()
    {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        users.push_back(User(username, password));
        saveUsers(); // Save users to file immediately after adding a new user
        cout << "User registered successfully!" << endl;
    }

    bool loginUser(string &loggedInUser)
    {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (const auto &user : users)
        {
            if (user.username == username && user.password == password)
            {
                loggedInUser = username;
                return true;
            }
        }
        return false;
    }

    void addBook()
    {
        string title, author;
        cout << "Enter book title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter book author: ";
        getline(cin, author);

        books.push_back(Book(title, author));
        saveBooks();
        cout << "Book added successfully!" << endl;
    }

    void displayBooks()
    {
        for (auto &book : books)
        {
            book.display();
        }
    }

    void borrowBook()
    {
        string title;
        cout << "Enter book title to borrow: ";
        cin.ignore();
        getline(cin, title);

        for (auto &book : books)
        {
            if (book.title == title && book.isAvailable)
            {
                book.isAvailable = false;
                saveBooks(); // Save books to file after borrowing
                cout << "You have borrowed the book: " << title << endl;
                return;
            }
        }
        cout << "Book not available!" << endl;
    }

    void returnBook()
    {
        string title;
        cout << "Enter book title to return: ";
        cin.ignore();
        getline(cin, title);

        for (auto &book : books)
        {
            if (book.title == title && !book.isAvailable)
            {
                book.isAvailable = true;
                saveBooks(); // Save books to file after returning
                cout << "You have returned the book: " << title << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }
};

// Main function
int main()
{
    LibrarySystem library;
    string loggedInUser;
    int choice;

    while (true)
    {
        cout << "\n1. Register\n2. Login\n3. Add Book\n4. Display Books\n5. Borrow Book\n6. Return Book\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            library.addUser();
            break;
        case 2:
            if (library.loginUser(loggedInUser))
            {
                cout << "Login successful! Welcome, " << loggedInUser << endl;
            }
            else
            {
                cout << "Invalid username or password!" << endl;
            }
            break;
        case 3:
            if (!loggedInUser.empty())
            {
                library.addBook();
            }
            else
            {
                cout << "Please login first!" << endl;
            }
            break;
        case 4:
            library.displayBooks();
            break;
        case 5:
            if (!loggedInUser.empty())
            {
                library.borrowBook();
            }
            else
            {
                cout << "Please login first!" << endl;
            }
            break;
        case 6:
            if (!loggedInUser.empty())
            {
                library.returnBook();
            }
            else
            {
                cout << "Please login first!" << endl;
            }
            break;
        case 7:
            return 0;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
    return 0;
}
