#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

class Book
{
public:
    string title, author, isbn;
    int year;

    Book() {}
    Book(string t, string a, string i, int y) : title(t), author(a), isbn(i), year(y) {}

    string toString() const
    {
        return title + "," + author + "," + isbn + "," + to_string(year);
    }

    static Book fromString(const string &data)
    {
        stringstream ss(data);
        string title, author, isbn, year;
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, isbn, ',');
        getline(ss, year);
        return Book(title, author, isbn, stoi(year));
    }

    void display() const
    {
        cout << "Title: " << title << "\nAuthor: " << author
             << "\nISBN: " << isbn << "\nYear: " << year << endl;
    }
};

class Library
{
private:
    map<string, Book> books;
    const string filename = "library.txt";

public:
    Library()
    {
        loadFromFile();
    }
    ~Library()
    {
        saveToFile();
    }

    void addBook()
    {
        string title, author, isbn;
        int year;
        cout << "Enter title: ";
        getline(cin, title);
        cout << "Enter author: ";
        getline(cin, author);
        cout << "Enter ISBN: ";
        getline(cin, isbn);
        cout << "Enter year: ";
        cin >> year;
        cin.ignore();

        if (books.find(isbn) != books.end())
        {
            cout << "Book with this ISBN already exists!\n";
            return;
        }

        books[isbn] = Book(title, author, isbn, year);
        cout << "Book added successfully!\n";
    }

    void viewBooks()
    {
        if (books.empty())
        {
            cout << "No books in the library.\n";
            return;
        }
        for (const auto &pair : books)
        {
            cout << "----------------------\n";
            pair.second.display();
        }
    }

    void searchBook()
    {
        string isbn;
        cout << "Enter ISBN to search: ";
        getline(cin, isbn);
        if (books.find(isbn) != books.end())
        {
            cout << "Book found:\n";
            books[isbn].display();
        }
        else
        {
            cout << "Book not found.\n";
        }
    }

    void updateBook()
    {
        string isbn;
        cout << "Enter ISBN of the book to update: ";
        getline(cin, isbn);
        auto it = books.find(isbn);
        if (it == books.end())
        {
            cout << "Book not found.\n";
            return;
        }
        string title, author;
        int year;
        cout << "Enter new title: ";
        getline(cin, title);
        cout << "Enter new author: ";
        getline(cin, author);
        cout << "Enter new year: ";
        cin >> year;
        cin.ignore();
        it->second = Book(title, author, isbn, year);
        cout << "Book updated successfully!\n";
    }

    void deleteBook()
    {
        string isbn;
        cout << "Enter ISBN of the book to delete: ";
        getline(cin, isbn);
        if (books.erase(isbn))
        {
            cout << "Book deleted successfully!\n";
        }
        else
        {
            cout << "Book not found.\n";
        }
    }

    void saveToFile()
    {
        ofstream out(filename);
        for (const auto &pair : books)
        {
            out << pair.second.toString() << endl;
        }
    }

    void loadFromFile()
    {
        ifstream in(filename);
        string line;
        while (getline(in, line))
        {
            if (!line.empty())
            {
                Book b = Book::fromString(line);
                books[b.isbn] = b;
            }
        }
    }
};

void showMenu()
{
    cout << "\n--- Library Management System ---\n";
    cout << "1. Add Book\n";
    cout << "2. View Books\n";
    cout << "3. Search Book\n";
    cout << "4. Update Book\n";
    cout << "5. Delete Book\n";
    cout << "6. Exit\n";
    cout << "Choose an option: ";
}

int main()
{
    Library lib;
    int choice;
    while (true)
    {
        showMenu();
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer
        switch (choice)
        {
        case 1:
            lib.addBook();
            break;
        case 2:
            lib.viewBooks();
            break;
        case 3:
            lib.searchBook();
            break;
        case 4:
            lib.updateBook();
            break;
        case 5:
            lib.deleteBook();
            break;
        case 6:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
