#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>


template <typename T>

class Tree {
private:
    void push(T key, int parentIndex) {
        int currentIndex = parentIndex + 1;
        bool greater = key > tree[parentIndex]->key;
        Node* current;

        if (this->contains(key)) {
            return;
        }
        else {
            while (currentIndex < tree.size()) {
                current = tree[currentIndex];
                if (parentIndex == current->parentIndex) {
                    if (greater) {
                        greater = false;
                    }
                    else {
                        if (current->mark != 0) {
                            current->mark = 0;
                            current->key = key;
                            return;
                        }
                        greater = key > current->key;
                        parentIndex = currentIndex;
                    }
                }
                ++currentIndex;
            }

            if (greater) {
                tree.push_back(new Node(-2, parentIndex, 2));
            }
            tree.push_back(new Node(key, parentIndex, 0));
        }
    }

    void intersection(int current, Tree* other) {
        if (current >= tree.size() || tree[current]->mark != 0) {
            return;
        }

        if (findLeftChild(current) != current) {
            intersection(findLeftChild(current), other);
        }
        if (findRightChild(current) != current) {
            intersection(findRightChild(current), other);
        }

        if (!other->contains(tree[current]->key)) {
            deleteNode(current);
        }
    }

    T deleteNode(int current) {
        T tempkey;
        bool warp = false;
        if (findRightChild(current) != current && tree[findRightChild(current)]->mark == 0) {
            tempkey = deleteNode(findLeft(findRightChild(current)));
            warp = true;
        }
        else if (findLeftChild(current) != current && tree[findLeftChild(current)]->mark == 0) {
            tempkey = deleteNode(findLeftChild(current));
            warp = true;
        }
        if (!warp) {
            tree[current]->mark = 1;
            return tree[current]->key;
        }
        T buff = tree[current]->key;
        tree[current]->key = tempkey;
        return buff;
    }

    void print(int index, int level = 0) {
        if (index != findRightChild(index)) {
            print(findRightChild(index), level + 1);
        }
        for (int i = 0; i < level * 4; ++i) {
            std::cout << ' ';
        }
        std::cout << tree[index]->key << '\n';
        if (index != findLeftChild(index)) {
            print(findLeftChild(index), level + 1);
        }
    }

public:
    class Node {
    public:
        T key;
        int parentIndex;
        int mark;
        Node(T key, int parentIndex, int mark) : key(key), parentIndex(parentIndex), mark(mark) {};

    };

    std::vector<Node*> tree = std::vector<Node*>();

    Tree() {};

    ~Tree() {
        for (int i = 0; i < tree.size(); ++i) {
            if (tree[i]) {
                delete tree[i];
            }
        }
    }

    void push(T key) {
        if (tree.size() == 0) {
            tree.push_back(new Node(key, -1, 0));
        }
        else {
            push(key, 0);
        }
    }

    int findLeftChild(int parentIndex) {
        int index = parentIndex + 1;
        while (index < tree.size() && tree[index]->parentIndex != parentIndex) {
            ++index;
        }
        if (index == tree.size() || tree[index]->mark != 0) {

            return parentIndex;
        }
        return index;
    }

    int findRightChild(int parentIndex) {
        int index = parentIndex + 1;
        int childNum = 1;

        while (index < tree.size()) {
            if (tree[index]->parentIndex == parentIndex && --childNum == -1) {
                break;
            }
            ++index;
        }

        if (index == tree.size() || tree[index]->mark != 0) {
            return parentIndex;
        }
        return index;
    }

    int findLeft(int parentIndex) {
        int index = parentIndex + 1;

        while (index < tree.size() && tree[index]->parentIndex != parentIndex) {
            ++index;
        }
        if (index == tree.size() || tree[index]->mark != 0) {

            return parentIndex;
        }
        return findLeft(index);
    }

    int findRight(int parentIndex) {

        int index = parentIndex + 1;
        int childNum = 1;

        while (index < tree.size()) {
            if (tree[index]->parentIndex == parentIndex && --childNum == -1) {
                break;
            }
            ++index;
        }

        if (index == tree.size() || tree[index]->mark != 0) {
            return parentIndex;
        }
        return findRight(index);
    }

    // Метод для выполнения операции A = A ⋂ B
    void intersection(Tree* other) {
        intersection(0, other);
    }

    void print() {
        print(0);
    }

    bool contains(T key) {
        int parentIndex = 0;
        if (tree[0]->key == key) {
            return true;
        }
        int currentIndex = key > tree[parentIndex]->key ? findRightChild(parentIndex) : findLeftChild(parentIndex);
        while (currentIndex != parentIndex) {
            if (key == tree[currentIndex]->key) {
                return true;
            }
            parentIndex = currentIndex;
            currentIndex = key > tree[parentIndex]->key ? findRightChild(parentIndex) : findLeftChild(parentIndex);
        }

        if (key == tree[currentIndex]->key) {
            return true;
        }
        return false;
    }


    class symetryIterator {
    private:
        int currentIndex;
        Tree* set;

    public:
        typedef int difference_type;
        typedef T value_type;
        typedef std::forward_iterator_tag iterator_category;
        typedef T& reference;
        typedef void pointer;
        Node* current;
        std::stack<Node*> stack_minus;
        T operator*() { return current->key; }
        T operator!=(symetryIterator other) { return currentIndex != other.currentIndex; }
        bool operator==(T key) { return current->key == key; }

        symetryIterator(int startIndex, Tree<T>* set) {
            this->set = set;
            this->currentIndex = startIndex;
            this->current = startIndex != -1 ? this->set->tree[currentIndex] : nullptr;
        };

        void findNextNode() {
            if (set->findRightChild(currentIndex) != currentIndex) {
                currentIndex = set->findLeft(set->findRightChild(currentIndex));
                current = set->tree[currentIndex];

                return;
            }
            if (current->parentIndex == -1 || current->key > set->tree[current->parentIndex]->key) {
                while (current->parentIndex != -1 && current->key > set->tree[current->parentIndex]->key) {
                    currentIndex = current->parentIndex;
                    current = set->tree[currentIndex];
                }
                if (current->parentIndex == -1) {
                    currentIndex = -1;
                    return;
                }
            }
            currentIndex = current->parentIndex;
            current = set->tree[current->parentIndex];
        }

        void findPrevNode() {
            if (currentIndex == -1) {
                return;
            }
            if (set->findLeftChild(currentIndex) != currentIndex) {
                int index = set->findLeftChild(currentIndex);

                currentIndex = set->findRight(index);
                current = set->tree[currentIndex];

                return;
            }
            if (current->key < set->tree[current->parentIndex]->key) {
                while (current->parentIndex != -1 && current->key < set->tree[current->parentIndex]->key) {
                    currentIndex = current->parentIndex;
                    current = set->tree[currentIndex];
                }
                if (current->parentIndex == -1) {
                    currentIndex = -1;
                    return;
                }
            }
            currentIndex = current->parentIndex;
            current = set->tree[current->parentIndex];
        }

        symetryIterator& operator++() {
            findNextNode();
            return *this;
        }
        symetryIterator& operator++(int) {
            findNextNode();
            return *this;
        }
        symetryIterator& operator --()
        {
            findPrevNode();
            return *this;
        }

        symetryIterator& operator --(int)
        {
            findPrevNode();
            return *this;
        }
    };

    symetryIterator begin() {
        return symetryIterator(findLeft(0), this);
    }

    symetryIterator end() {
        return symetryIterator(-1, this);
    }
    symetryIterator rbegin()
    {
        return symetryIterator(findRight(0), this);
    }

    symetryIterator rend()
    {
        return symetryIterator(-1, this);
    }


    class reverseIterator {
    private:
        Tree* set;

    public:
        typedef int difference_type;
        typedef T value_type;
        typedef std::forward_iterator_tag iterator_category;
        typedef T& reference;
        typedef void pointer;
        int currentIndex;
        Node* current;
        T operator*() { return current->key; }
        T operator!=(reverseIterator other) { return currentIndex != other.currentIndex; }
        bool operator==(T key) { return current->key == key; }

        reverseIterator(int startIndex, Tree<T>* set) {
            this->set = set;
            this->currentIndex = startIndex;
            this->current = startIndex != -1 ? this->set->tree[currentIndex] : nullptr;
        };

        void findNextNode() {
            if (current->parentIndex == -1) {
                currentIndex = -1;
                return;
            }
            if (set->tree[current->parentIndex]->key < current->key) {
                currentIndex = current->parentIndex;
                current = set->tree[currentIndex];
                return;
            }

            currentIndex = current->parentIndex;
            current = set->tree[currentIndex];

            if (set->findRightChild(currentIndex) == currentIndex) {
                return;
            }

            while (set->findRightChild(currentIndex) != currentIndex) {
                int index = set->findRightChild(currentIndex);
                currentIndex = set->findLeft(index);
                current = set->tree[currentIndex];
            }
        }

        void findPrevNode() {
            if (set->findLeft(0) == currentIndex) {
                currentIndex = -1;
                return;
            }
            if (set->tree[set->findRightChild(currentIndex)]->key > set->tree[currentIndex]->key) {
                currentIndex = set->findRightChild(currentIndex);
                current = set->tree[currentIndex];
            }
            else {
                // Если у текущего узла нет правого сына, двигаемся вверх по дереву, пока не найдем первый узел, у которого текущий узел является правым сыном
                while (current->parentIndex != -1 && currentIndex == set->findRightChild(current->parentIndex)) {
                    currentIndex = current->parentIndex;
                    current = set->tree[currentIndex];
                }
                currentIndex = set->findLeftChild(currentIndex);
                current = set->tree[currentIndex];
            }
        }


        reverseIterator& operator++() {
            findNextNode();
            return *this;
        }

        reverseIterator& operator++(int) {
            findNextNode();
            return *this;
        }

        reverseIterator& operator --()
        {
            findPrevNode();
            return *this;
        }

        reverseIterator& operator --(int)
        {
            findPrevNode();
            return *this;
        }
    };

    reverseIterator begin_r() {
        int bottom = findLeft(0);
        while (bottom != findRightChild(bottom)) {
            bottom = findLeft(findRightChild(bottom));
        }
        return reverseIterator(bottom, this);
    }

    reverseIterator end_r() {
        return reverseIterator(-1, this);
    }

    reverseIterator rbegin_r() {
        return reverseIterator(0, this);
    }

    reverseIterator rend_r() {
        return reverseIterator(-1, this);
    }
};


int main()
{
    Tree<int> treeA;
    // Пример 1
    /*
    treeA.push(5);
    treeA.push(3);
    treeA.push(2);
    treeA.push(4);
    treeA.push(7);
    treeA.push(8);
    treeA.push(6);
    treeA.push(1);
    treeA.push(9);
    treeA.push(0);
    */
    // Пример 2
    treeA.push(3);
    treeA.push(2);
    treeA.push(1);
    treeA.push(4);
    treeA.push(7);
    treeA.push(8);
    std::cout << "Tree A" << "\n";
    treeA.print();
    std::cout << "\n";

    std::cout << "TreeA Iterator" << "\n";
    for (Tree<int>::symetryIterator i = treeA.begin(); i != treeA.end(); i++)
    {
        std::cout << *i << " ";
    }
    std::cout << "\n";


    Tree<int> treeB;
    // Пример 1
    /*
    treeB.push(5);
    treeB.push(2);
    treeB.push(1);
    treeB.push(3);
    treeB.push(4);
    treeB.push(7);
    treeB.push(11);
    treeB.push(0);
    */
    treeB.push(3);
    treeB.push(2);
    treeB.push(1);
    std::cout << "\n" << "Tree B" << "\n";
    treeB.print();
    std::cout << "\n";

    std::cout << "TreeB Iterator ++" << "\n";
    for (Tree<int>::reverseIterator i = treeB.begin_r(); i != treeB.end_r(); i++)
    {
        std::cout << *i << " ";
    }
    std::cout << "\n";

    std::cout << "TreeB Iterator --" << "\n";
    for (Tree<int>::reverseIterator i = treeB.rbegin_r(); i != treeB.rend_r(); i--)
    {
        std::cout << *i << " ";
    }
    std::cout << "\n";


    treeA.intersection(&treeB);


    std::cout << "\n" << "Tree A" << "\n";
    treeA.print();

    std::cout << "TreeA Iterator ++" << "\n";
    for (Tree<int>::symetryIterator i = treeA.begin(); i != treeA.end(); i++)
    {
        std::cout << *i << " ";
    }
    std::cout << "\n";

    std::cout << "TreeA Iterator --" << "\n";
    for (Tree<int>::symetryIterator i = treeA.rbegin(); i != treeA.rend(); --i)
    {
        std::cout << *i << " ";
    }
    std::cout << "\n";

    std::cout << "TreeA Iterator range" << "\n";
    for (auto i : treeA)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";

    std::cout << "count(treeA.Tree::begin(), treeA.Tree::end(), 2);" << "\n";
    std::cout << std::count(treeA.Tree::begin(), treeA.Tree::end(), 2);
}