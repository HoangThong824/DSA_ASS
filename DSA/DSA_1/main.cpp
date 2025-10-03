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

SinglyLinkedList<float>* dummyEmbedding(const string& text) {
    auto* vec = new SinglyLinkedList<float>();
    for (char c : text) {
        vec->add(static_cast<float>(c % 5));
    }
    return vec;
}

void test_011() {
    ArrayList<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.removeAt(1);   // Xóa phần tử có index = 1 (giá trị 2)
    cout << "test_011: " << arr.toString() << endl;
}
// Expected: [1, 3]

void test_012() {
    ArrayList<int> arr;
    arr.add(10);
    arr.add(20);
    arr.add(30);
    cout << "test_012: contains(20) = " << (arr.contains(20) ? "true" : "false") << endl;
}
// Expected: contains(20) = true

void test_013() {
    ArrayList<int> arr;
    cout << "test_013: empty() = " << (arr.empty() ? "true" : "false") << endl;
}
// Expected: empty() = true

void test_014() {
    SinglyLinkedList<int> sll;
    sll.add(5);
    sll.add(10);
    cout << "test_014: size = " << sll.size() << endl;
}
// Expected: size = 2

void test_015() {
    SinglyLinkedList<int> sll;
    sll.add(1);
    sll.add(2);
    sll.add(3);
    cout << "test_015: indexOf(3) = " << sll.indexOf(3) << endl;
}
// Expected: indexOf(3) = 2

void test_016() {
    VectorStore store(5, dummyEmbedding);
    store.addText("abc");
    store.addText("xyz");
    cout << "test_016: size = " << store.size() << endl;
}
// Expected: size = 2

void test_017() {
    VectorStore store(5, dummyEmbedding);
    store.addText("aaa");
    store.addText("bbb");
    cout << "test_017: getRawText(0) = " << store.getRawText(0) 
         << ", getRawText(1) = " << store.getRawText(1) << endl;
}
// Expected: getRawText(0) = aaa, getRawText(1) = bbb

void test_018() {
    VectorStore store(5, dummyEmbedding);
    store.addText("cat");
    store.addText("dog");
    store.clear();
    cout << "test_018: empty() after clear = " << (store.empty() ? "true" : "false") << endl;
}
// Expected: empty() after clear = true

void test_019() {
    VectorStore store(5, dummyEmbedding);
    store.addText("apple");
    store.addText("banana");
    int idx = store.findNearest(*dummyEmbedding("apple"));
    cout << "test_019: nearest to 'apple' is id = " << idx+1 << endl;
}
// Expected: nearest to 'apple' is id = 1   (vì "apple" so chính nó)

void test_020() {
    VectorStore store(5, dummyEmbedding);
    store.addText("one");
    store.addText("two");
    store.addText("three");
    int* top2 = store.topKNearest(*dummyEmbedding("two"), 2);
    cout << "test_020: top2 nearest indices = [" << top2[0] << ", " << top2[1] << "]" << endl;
    delete[] top2;
}
// Expected: top2 nearest indices = [1, 2]   (hoặc hoán đổi, tùy embedding)
// ================== TEST CASES 021 -> 030 ==================

void test_021() {
    VectorStore store(5, dummyEmbedding);
    store.addText("one");
    store.addText("two");
    store.addText("three");
    cout << "test_021: size = " << store.size() << endl;
}

void test_022() {
    VectorStore store(5, dummyEmbedding);
    store.addText("ab");
    auto& vec = store.getVector(0);
    cout << "test_022: vector length = " << vec.size() << endl;
}

void test_023() {
    VectorStore store(5, dummyEmbedding);
    store.addText("alpha");
    store.addText("beta");
    store.addText("gamma");
    cout << "test_023: rawText(1) = " << store.getRawText(1) << endl;
}

void test_024() {
    VectorStore store(5, dummyEmbedding);
    store.addText("first");
    store.addText("second");
    cout << "test_024: id(0) = " << store.getId(0)
         << ", id(1) = " << store.getId(1) << endl;
}

void test_025() {
    VectorStore store(5, dummyEmbedding);
    store.addText("red");
    store.addText("green");
    store.addText("blue");
    store.removeAt(1);
    cout << "test_025: size = " << store.size()
         << ", rawText(1) = " << store.getRawText(1) << endl;
}

void test_026() {
    VectorStore store(5, dummyEmbedding);
    store.addText("old");
    store.updateText(0, "new");
    cout << "test_026: rawText(0) = " << store.getRawText(0) << endl;
}

void test_027() {
    VectorStore store(5, dummyEmbedding);
    cout << "test_027: empty = " << (store.empty() ? "true" : "false") << endl;
}

void test_028() {
    VectorStore store(5, dummyEmbedding);
    store.addText("hello");
    store.addText("world");
    store.clear();
    cout << "test_028: size = " << store.size() << endl;
}

void test_029() {
    VectorStore store(5, dummyEmbedding);
    store.addText("abc");
    store.addText("xyz");
    SinglyLinkedList<float>* query = dummyEmbedding("abc");
    int idx = store.findNearest(*query, "cosine");
    cout << "test_029: nearest index = " << idx
         << ", rawText = " << store.getRawText(idx) << endl;
    delete query;
}

void test_030() {
    VectorStore store(5, dummyEmbedding);
    store.addText("abc");
    store.addText("xyz");
    store.addText("cat");

    SinglyLinkedList<float>* query = dummyEmbedding("xyz");
    int* top2 = store.topKNearest(*query, 2, "cosine");
    cout << "test_030: top2 = [" << top2[0] << ", " << top2[1] << "]" << endl;
    delete[] top2;
    delete query;
}

// ================== MAIN =================


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

    test_011();
    test_012();
    test_013();

    test_014();
    test_015();
    test_016();

    test_017();
    test_018();
    test_019();
    test_020();

    test_021();
    test_022();
    test_023();
    test_024();
    test_025();
    test_026();
    test_027();
    test_028();
    test_029();
    test_030();
    return 0;
}