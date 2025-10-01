#include "VectorStore.h"
void test_001() {
    ArrayList<int> arr;
    arr.add(10);
    arr.add(20);
    arr.add(30);
    cout << "test_001: " << arr.toString() << endl;
}

void test_002() {
    ArrayList<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.set(1, 99);
    cout << "test_002: " << arr.toString() << endl;
}

void test_003() {
    ArrayList<int> arr;
    arr.add(5);
    arr.add(6);
    arr.add(7);
    arr.add(1, 99); // chèn vào giữa
    cout << "test_003: " << arr.toString() << endl;
}

void test_004() {
    ArrayList<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.removeAt(1);
    cout << "test_004: " << arr.toString() << endl;
}

void test_005() {
    SinglyLinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    cout << "test_005: " << list.toString() << endl;
}

void test_006() {
    SinglyLinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(1, 99);
    cout << "test_006: " << list.toString() << endl;
}

void test_007() {
    SinglyLinkedList<int> list;
    list.add(10);
    list.add(20);
    list.add(30);
    list.removeAt(1);
    cout << "test_007: " << list.toString() << endl;
}
// Hàm embedding giả lập
SinglyLinkedList<float>* simpleEmbed(const string& text) {
    auto* vec = new SinglyLinkedList<float>();
    for (char c : text) vec->add((float)(c % 5));
    return vec;
}

void test_008() {
    VectorStore store(5, simpleEmbed);
    store.addText("hello");
    store.addText("world");
    cout << "test_008: size = " << store.size() << endl;
}

void test_009() {
    VectorStore store(5, simpleEmbed);
    store.addText("hello");
    store.addText("world");
    cout << "test_009: " << store.getRawText(0) 
         << ", " << store.getRawText(1) << endl;
}

void test_010() {
    VectorStore store(5, simpleEmbed);
    store.addText("abc");
    store.addText("abd");
    auto* q = simpleEmbed("abe");
    int idx = store.findNearest(*q, "cosine");
    cout << "test_010: nearest to 'abe' = " << store.getRawText(idx) << endl;
    delete q;
}

int main() {
    // Student can use this main function to do some basic testing
     test_001();
    test_002();
    test_003();
    test_004();

    test_005();
    test_006();
    test_007();

    test_008();
    test_009();
    test_010();

    return 0;
}