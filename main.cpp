#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base Class
class Book {
private:
    int id;
    string title;
    bool available;

protected:
    string author;

public:
    // Constructor
    Book(int i, string t, string a)
        : id(i), title(t), author(a), available(true) {}

    // Destructor
    virtual ~Book() {
        cout << "Book destroyed.\n";
    }

    int getId() const {
        return id;
    }

    string getTitle() const {
        return title;
    }

    // Function Overloading
    void borrowBook() {
        if (available) {
            available = false;
            cout << "Book borrowed successfully.\n";
        }
        else {
            cout << "Book is not available.\n";
        }
    }

    void borrowBook(string studentName) {
        if (available) {
            available = false;
            cout << "Book borrowed by "
                 << studentName << ".\n";
        }
        else {
            cout << "Book is not available.\n";
        }
    }

    void returnBook() {
        available = true;
        cout << "Book returned successfully.\n";
    }

    // Virtual Function
    virtual void display() const {
        cout << "ID: " << id << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;

        cout << "Status: "
             << (available ? "Available" : "Borrowed")
             << endl;
    }
};


// Inheritance
class EBook : public Book {
private:
    double sizeMB;

public:
    EBook(int i, string t, string a, double s)
        : Book(i, t, a), sizeMB(s) {}

    // Destructor
    ~EBook() override {
        cout << "EBook destroyed.\n";
    }

    // Polymorphism
    void display() const override {
        cout << "\n--- E-Book ---\n";

        Book::display();

        cout << "Size: "
             << sizeMB << " MB\n";
    }
};


// Library Class
class Library {
private:
    vector<Book*> books;

public:

    // Destructor
    ~Library() {
        for (Book* b : books)
            delete b;
    }

    void addBook(Book* b) {
        books.push_back(b);
    }

    Book* findBook(int id) {
        for (Book* b : books)
            if (b->getId() == id)
                return b;

        return nullptr;
    }

    void showBooks() const {

        if (books.empty()) {
            cout << "No books.\n";
            return;
        }

        for (Book* b : books) {

            b->display();

            cout << "------------------\n";
        }
    }
};


int main() {

    Library library;

    int choice;

    do {

        cout << "\n===== LIBRARY SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. Add E-Book\n";
        cout << "3. Show Books\n";
        cout << "4. Borrow Book\n";
        cout << "5. Return Book\n";
        cout << "0. Exit\n";

        cout << "Choose: ";
        cin >> choice;


        if (choice == 1 || choice == 2) {

            int id;
            string title, author;

            cout << "ID: ";
            cin >> id;

            cin.ignore();

            cout << "Title: ";
            getline(cin, title);

            cout << "Author: ";
            getline(cin, author);


            if (choice == 1) {

                library.addBook(
                    new Book(id, title, author)
                );

            }
            else {

                double size;

                cout << "Size (MB): ";
                cin >> size;

                library.addBook(
                    new EBook(
                        id,
                        title,
                        author,
                        size
                    )
                );
            }

            cout << "Added successfully.\n";
        }


        else if (choice == 3) {

            library.showBooks();
        }


        else if (choice == 4 ||
                 choice == 5) {

            int id;

            cout << "Book ID: ";
            cin >> id;

            Book* b =
                library.findBook(id);


            if (b == nullptr) {

                cout << "Book not found.\n";
            }

            else if (choice == 4) {

                b->borrowBook("Student");
            }

            else {

                b->returnBook();
            }
        }


        else if (choice != 0) {

            cout << "Invalid choice.\n";
        }


    } while (choice != 0);


    cout << "Program ended.\n";

    return 0;
}
