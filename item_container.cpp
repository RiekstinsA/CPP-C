#include <iostream>
#include <memory>
#include <utility>
using namespace std;

template<typename T>
class Item {
    unique_ptr<T[]> elements;
    size_t count;

public:
    explicit Item(size_t n) : count(n), elements(make_unique<T[]>(n)) {
        cout << "Created an item with " << count << " slots.\n";
    }

    Item(Item&& other) noexcept : elements(move(other.elements)), count(other.count) {
        other.count = 0;
        cout << "Item has been moved to new owner!\n";
    }

    Item& operator=(Item&& other) noexcept {
        if (this != &other) {
            elements = move(other.elements);
            count = other.count;
            other.count = 0;
            cout << "Item has been move assigned!\n";
        }
        return *this;
    }

    T& operator[](size_t i) { 
        return elements[i]; 
    }
    
    const T& operator[](size_t i) const {
         return elements[i]; 
        }

    size_t size() const { 
        return count; 
    }
};

int main() {
    Item<int> myItem(10);

    for (size_t i = 0; i < myItem.size(); ++i)
        myItem[i] = i * 10;

    Item<int> anotherItem = move(myItem);
    cout << "The element 5 is: " << anotherItem[4] << "\n";

    return 0;
}
