#include <bits/stdc++.h>
using namespace std;

class User;

bool loggedIn = false;
User *loggedUser = NULL;

class Book
{
public:
    string Id;
    string title;
    string issuedTo;
    bool available;
    static int BId;

    Book(string title, string issued = "None", bool available = true)
    {
        Id = to_string(BId);
        this->title = title;
        BId++;
        issuedTo = issued;
        this->available = available;
    }

    void display()
    {
        cout << "Title: " << title << "\nBookId: " << Id << "\nIssuedTo: " << issuedTo << "\nAvailable: " << (available ? "Yes" : "No") << endl;
    }
};
int Book::BId = 100000;

class User
{
public:
    string Id;
    string username;
    string password;
    string bookIssued;
    static int UId;

    User(string username, string password)
    {
        Id = to_string(UId);
        UId++;
        this->username = username;
        this->password = password;
        bookIssued = "";
    }

    void display()
    {
        cout << "Username: " << username << "\nUserId: " << Id << "\nPassword: **Secret hae sorry**"
             << endl;
        cout << "Books issued: ";
        if (bookIssued.length() == 0)
            cout << "No books issued" << endl;
        else
        {
            for (int i = 0; i < bookIssued.length(); i++)
            {
                char ch = bookIssued[i];
                if (ch == ',')
                    cout << endl;
                else
                    cout << ch;
            }
            cout << endl;
        }
    }
};
int User::UId = 0;

class Library
{
public:
    vector<Book> books;
    vector<User> users;

    Library()
    {
        loadBooks();
        loadUsers();
    }

    ~Library()
    {
        saveBooks();
        saveUsers();
    }

    void loadBooks()
    {
        ifstream BOOK("books.txt");
        string title, Id, issuedTo, available;
        while (getline(BOOK, Id) && getline(BOOK, title) && getline(BOOK, issuedTo) && getline(BOOK, available))
        {
            Book new_book(title);
            new_book.available = available == "Yes";
            new_book.issuedTo = issuedTo;
            new_book.Id = Id;
            new_book.BId--;
            books.push_back(new_book);
        }
        BOOK.close();
    }

    void loadUsers()
    {
        ifstream USER("users.txt");
        string Id, username, password, bookissued;
        while (getline(USER, Id) && getline(USER, username) && getline(USER, password) && getline(USER, bookissued))
        {
            User new_user(username, password);
            new_user.Id = Id;
            new_user.bookIssued = bookissued;
            new_user.UId--;            // Adjust to ensure unique user ID
            users.push_back(new_user); // Add the user to the vector
        }
        USER.close();
    }

    void saveBooks()
    {
        ofstream out("books.txt");

        for (auto &book : books)
        {
            out << book.Id << endl;
            out << book.title << endl;
            out << book.issuedTo << endl;
            out << (book.available ? "Yes" : "No") << endl;
        }
        out.close();
    }

    void saveUsers()
    {
        ofstream out("users.txt");

        for (auto &user : users)
        {
            out << user.Id << endl;
            out << user.username << endl;
            out << user.password << endl;
            out << user.bookIssued << endl;
        }
        out.close();
    }

    void addUser()
    {
        string username, password;
        cout << "Enter your username: ";
        cin.ignore();
        getline(cin, username);
        cout << "Enter your password: ";
        cin.ignore();
        getline(cin, password);

        User new_user(username, password);
        users.push_back(new_user);
        cout << "User registered successfully!\nNow you can log in from the login option :)" << endl;
    }

    bool loginUser()
    {
        string username, password;
        cout << "Enter your username: ";
        cin.ignore();
        getline(cin, username);
        cout << "Enter your password: ";
        cin.ignore();
        getline(cin, password);

        for (auto &user : users)
        {
            if (user.username == username && user.password == password)
            {
                loggedIn = true;
                loggedUser = &user;
                return true;
            }
        }
        return false;
    }

    void logoutUser()
    {
        string username = loggedUser->username;
        loggedUser = NULL;
        loggedIn = false;
        cout << "You have been successfully logged out! " << username << endl;
    }

    void addBook()
    {
        string title;
        cin.ignore();
        cout << "Enter the title: ";
        getline(cin, title);

        Book new_book(title);
        books.push_back(new_book);
        cout << "Book added successfully! Below are the details:" << endl;
        new_book.display();
    }

    void displayBooks()
    {
        if (books.size() == 0)
        {
            cout << "No books available! :(" << endl;
            return;
        }
        for (auto &book : books)
        {
            book.display();
        }
    }

    void borrowBook()
    {
        string title;
        cout << "Enter the title: ";
        cin.ignore();
        getline(cin, title);

        for (auto &book : books)
        {
            if (book.title == title && book.available)
            {
                book.available = false;
                book.issuedTo = loggedUser->Id;
                loggedUser->bookIssued += (title + " ");
                cout << "Book borrowed by:" << endl;
                loggedUser->display();
                cout << endl;
                cout << "Book issued is:" << endl;
                book.display();
                cout << endl;
                return;
            }
        }
        cout << "Book not available!" << endl;
    }

    void returnBook()
    {
        string title;
        cout << "Enter the title of the book: ";
        cin.ignore();
        getline(cin, title);

        for (auto &book : books)
        {
            if (book.title == title)
            {
                book.available = true;
                int pos = loggedUser->bookIssued.find(title);
                if (pos != string::npos)
                {
                    loggedUser->bookIssued.erase(pos, title.length() + 1);
                }
                cout << "Book returned by user:" << endl;
                loggedUser->display();
                cout << "Book returned was:" << endl;
                book.display();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }
};

int main()
{
    Library l1;
    int choice;

    while (true)
    {
        if (!loggedIn)
        {
            cout << "1. Register\n2. Login\n3. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            if (choice == 1)
            {
                l1.addUser();
            }
            else if (choice == 2)
            {
                if (l1.loginUser())
                {
                    cout << "Welcome " << loggedUser->username << " good to see you!\nHappy reading :)" << endl;
                }
                else
                {
                    cout << "Invalid username or password!\nTry again..." << endl;
                }
            }
            else if (choice == 3)
                return 0;
            else
            {
                cout << "Invalid choice!\nAre you dumb or what?" << endl;
            }
        }
        else
        {
            cout << "1. Display Books\n2. Borrow book\n3. Add books\n4. Return book\n5. Your account\n6. Logout\n7. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                l1.displayBooks();
                break;
            case 2:
                l1.borrowBook();
                break;
            case 3:
                l1.addBook();
                break;
            case 4:
                l1.returnBook();
                break;
            case 5:
                loggedUser->display();
                break;
            case 6:
                l1.logoutUser();
                break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice!\nAre you dumb or what?" << endl;
            }
        }
    }

    return 0;
}
