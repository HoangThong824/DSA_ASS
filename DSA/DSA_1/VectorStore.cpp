#include "VectorStore.h"

// ----------------- ArrayList Implementation -----------------
template <class T>
void ArrayList<T>:: ensureCapacity(int cap){
    /* the dynamic array has sufficient capacity to store at least cap elements.
     If cap exceeds the current capacity, the capacity is increased by a factor of 1.5,
      a new memory block is allocated, and all existing elements are copied into it.*/
    if(cap > capacity){
        this->capacity*=1.5;
    }
    
    T* newData = new T[capacity];
    for(int i=0; i<count; i++){
        newData[i] = this->data[i];
    }
    this->data = newData;
}
template <class T>
ArrayList<T>::ArrayList(int initCapacity = 10) {
    /*: Initializes an empty dynamic array list with an initial capacity of initCapacity.*/
    this->capacity = initCapacity;
    this->count = 0;
    this->data = new T[capacity];
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& other) {
    /* Constructs a new list by copying all elements from the list other.*/
    this->capacity = other.capacity;
    this->count = other.count;
    this->data = new T[capacity];
    for (int i = 0; i< count; i++){
        data[i] = other.data[i];
    }
}   

template <class T>
ArrayList<T>::~ArrayList() {
    /*Releases all memory allocated for the list to avoid memory leaks*/
    delete[] data;
}
template <class T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other){
    /*Assigns all elements from other to the current list.*/
        if (this != &other) {
        delete[] data;
        this->capacity = other.capacity;
        this->count = other.count;
        this->data = new T[capacity];
        for (int i = 0; i < count; i++) {
            this->data[i] = other.data[i];
        }
    }
    return *this;
}
template <class T>
void ArrayList<T>:: add(T e){
    /* Appends element e to the end of the array*/
    ensureCapacity(count+1);
    data[count++] = e;
}

template <class T>
void ArrayList<T>::add(int index, T e) {
    /*Inserts element e at position index, shifting subsequent elements one position to the right.*/
    if (index < 0 || index > count) {
        throw std::out_of_range("Index is invalid!");
    }
    ensureCapacity(count + 1);
    for (int i = count; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = e;
    count++;
}
template <class T>
T ArrayList<T>::removeAt(int index) {
    /* Removes and returns the element at position index, shifting subsequent
    elements one position to the left.
    */
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is invalid!");
    }
    T removed = data[index];
    for (int i = index; i < count - 1; i++) {
        data[i] = data[i + 1];
    }
    count--;
    return removed;
}

template <class T>
bool ArrayList<T>::empty() const {
    return count == 0;
}

template <class T>
int ArrayList<T>::size() const{
    return count;
}

template <class T>
void ArrayList<T>::clear() {
    delete[] data;
    capacity = 10;
    count = 0;
    data = new T[capacity];
}

template <class T>
const T& ArrayList<T>::get(int index) const {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    return data[index];
}

template <class T>
void ArrayList<T>::set(int index, T e) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    data[index] = e;
}

template <class T>
int ArrayList<T>::indexOf(T item) const{
    for (int i = 0; i < count; i++) {
        if (data[i] == item) return i;
    }
    return -1;
}

template <class T>
bool ArrayList<T>::contains(T item) const{
    return indexOf(item) != -1;
}

template <class T>
string ArrayList<T>::toString(string (*item2str)(T&)) const {
    ostringstream oss;
    oss << "[";

    for (int i = 0; i < count; i++) {
        if (item2str) {
            oss << item2str(data[i]);
        } else {
            oss << to_string(data[i]);
        }
        if (i < count - 1) oss << ", ";
    }
    oss << "]";
    return oss.str();
}

template <class T>
ArrayList<T>::Iterator ArrayList<T>::begin(){
    return Iterator(this, 0);
}

template <class T>
ArrayList<T>::Iterator ArrayList<T>::end(){
    return Iterator(this, count);
}
// ----------------- Iterator of ArrayList Implementation -----------------
template <class T>
ArrayList<T>::Iterator::Iterator(ArrayList<T>* pList, int index) {
    /*  -Initializes an iterator pointing to the array pList at the given index.
    Students must verify the validity of index with respect to the list pList.
        - Throws out_of_range("Index is invalid!") if index is outside the
    valid range.
    */
    if (pList != nullptr && (index < 0 || index > pList->count)) {
        throw std::out_of_range("Index is invalid!");
    }
    this->pList = pList;
    this->cursor = index;

}

template<class T> 
ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator=(const ArrayList<T>::Iterator &other){
    /* Assigns the state from the iterator other to the current iterator.*/
    this->pList = other.pList;
    this->cursor = other.cursor;
    return *this;
}

template<class T>
T &ArrayList<T>::Iterator::operator*(){
    /*  -Returns a reference to the element at the position cursor in pList.
    Dereferencing at end() is invalid.
        -Throws out_of_range("Iterator is out of range!") if cursor is invalid.
    */
    if (pList == nullptr || cursor < 0 || cursor >= pList->count) {
        throw std::out_of_range("Iterator is out of range!");
    }
    return pList->data[cursor];
}

template<class T> 
bool ArrayList<T>::Iterator::operator!=(const ArrayList<T>::Iterator &other) const{
    /*Compares two iterators for inequality. They are considered different if
    their pList differ or their cursor indices differ.
    */
   return this->pList != other.pList || this->cursor != other.cursor;
}

template<class T> 
ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator++(){
    /*  Advances the iterator to the next element (prefix, ++it).
        Throws out_of_range("Iterator cannot advance past end!") if cursor is already at count.
    */
    if (cursor >= pList->count) {
        throw std::out_of_range("Iterator cannot advance past end!");
    }
    ++cursor;
    return *this;
}

template<class T> 
ArrayList<T>::Iterator ArrayList<T>::Iterator::operator++(int){
    /*
        -Advances the iterator to the next element (postfix, it++) and returns a
    copy of the old state.
        -Throws out_of_range("Iterator cannot advance past end!") if cursor is already at count.
    */
   if (cursor >= pList->count) {
        throw std::out_of_range("Iterator cannot advance past end!");
    }
    Iterator temp = *this;
    cursor++;
    return temp;
}
template<class T> 
ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator--(){
    /*
        -Moves the iterator to the previous element (prefix, --it). If the iterator
    is currently at end(), this operation moves it to the last element.
        -Throws out_of_range("Iterator cannot move before begin!") if already at the first element
    */
    if (cursor == 0) {
        throw std::out_of_range("Iterator cannot move before begin!");
    }
    --cursor;
    return *this;
}

template<class T>
 ArrayList<T>::Iterator ArrayList<T>::Iterator::operator--(int){
    /*
        -Moves the iterator to the previous element (postfix, it--) and returns a copy of the old state.
        -Throws out_of_range("Iterator cannot move before begin!") if already at the first element.
    */
    if (cursor == 0) {
        throw std::out_of_range("Iterator cannot move before begin!");
    }
    Iterator temp = *this;
    --cursor;
    return temp;
 }
// TODO: implement other methods of ArrayList::Iterator



// ----------------- SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    // TODO
    head = nullptr;
    tail = nullptr;
    count = 0;
}   

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    // TODO
    clear();
}   

template<class T> 
void SinglyLinkedList<T>::add(T e){
     /* Insert an element into the end of the list. */
    Node* newNode = new Node(e);
    if (tail == NULL || head == NULL){
        this->tail = newNode;
        this->head = newNode;
        this->head->next = tail;
        this->tail->next = NULL;
        this->count++;
        return;
        }
    this->tail->next = newNode;
    this->tail = newNode;
    ++(this->count);
    return;
}


template<class T>
void SinglyLinkedList<T>::add(int index, T e){
     /* Insert an element into the list at given index. */ 

    if (index < 0 || index > count)
            throw out_of_range("Index is invalid!");
            
    if (index == this->count && this->count != 0) {
		add(e);
		return;
	}
	Node* newNode = new Node(e, NULL);
	if (this->count == 0) {
		this->head = this->tail = newNode;
	}
	else if (index == 0) {
		newNode->next = this->head;
		this->head = newNode;
	}
	else {
		Node* temp = this->head;
		for (int i = 0; i < index - 1; i++) temp = temp->next;
		newNode->next = temp->next;
		temp->next = newNode;
	}
	++this->count;
}

template<class T> 
T SinglyLinkedList<T>::removeAt(int index){
    if (count == 0) throw std::out_of_range("Index is out of range");
    if (index > count-1) throw std::out_of_range("Index is out of range");

    Node* h = this->head;
    Node* prev = this->head;
    T temp;
    if (index == 0){
        temp = h->data;
        this->head = h->next;
        delete h;
        --(this->count);
        return temp;
    }

    if (index == count-1){
        while (h->next->next != NULL) h = h->next;
        temp = this->tail->data;
        delete this->tail;
        this->tail = h;
        this->tail->next = NULL;
    }
    else{
        for(int i = 0; i < index-1; i++)    prev = prev->next;
        h = prev->next;
        temp = h->data;
        prev->next = h->next;
        delete h;
        h = NULL;
    }
    --(this->count);
    return temp;
throw std::out_of_range("Index is out of range");
/* Remove element at index and return removed value */
}

template<class T>
bool SinglyLinkedList<T>::removeItem(T item){
    int index = indexOf(item);
    if (index != -1) {
        this->removeAt(index);
        return true;
    }
    return false;
}

template<class T>
 bool SinglyLinkedList<T>::empty() const{
    if (count == 0) return true;
    return false;
}

template<class T>
 int SinglyLinkedList<T>::size() const{
return (this->count);
}

template<class T>
 void SinglyLinkedList<T>::clear(){
    while (!empty()) {
        removeAt(0);
    }
}

template<class T>
 T &SinglyLinkedList<T>::get(int index){
    if (index < 0 || index > this->count){
        throw std::out_of_range("The index is out of range!");
    } 
    if(this->empty())   throw("List is empty");
    else{
        Node* temp = this->head;
        for (int i = 0; i < index; i++) temp = temp->next;
        return temp->data;
    }
}

template<class T>
 int SinglyLinkedList<T>::indexOf(T item) const{
     if (!this->empty()) {
        int index = 0;
        Node* temp = this->head;
        for (int i = 0; i < this->count; i++) {
            if (temp->data == item) {
                index = i;
                break;
            }
            else 
                temp = temp->next;
        }
        if (temp != NULL) return index;
    }
    return -1;
}

template<class T>
bool SinglyLinkedList<T>::contains(T item) const{
     return (this->indexOf(item) != -1);
}

template<class T>
 string SinglyLinkedList<T>::toString(string (*item2str)(T &) = 0) const{
    string result = "";
        Node* p = head;
        while (p != nullptr) {
            if (item2str != nullptr)
                result += "[" + item2str(p->data) + "]";
            else {
                result += "[" + to_string(p->data) + "]";
            }
            if (p->next != nullptr) result += "->";
            p = p->next;
        }
        return result;
}

template<class T>
const SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::begin() const{
    return Iterator(head);
}

template<class T>
const SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end() const{
    return Iterator(nullptr); 
}



// TODO: implement other methods of SinglyLinkedList



// ----------------- Iterator of SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::Iterator::Iterator(Node* node) {
    // TODO
    this->current = node;
}   
template<class T>
SinglyLinkedList<T>::Iterator
&SinglyLinkedList<T>::Iterator::operator=(const SinglyLinkedList<T>::Iterator &other){
    this->pList = other.pList;
	this->current = other.current;
	this->index = other.index;
	return *this;
 }

template<class T> T &SinglyLinkedList<T>::Iterator::operator*(){
    if (current == nullptr) {
            throw out_of_range("Iterator is out of range!");
        }
        return current->data;
}

template<class T>
bool SinglyLinkedList<T>::Iterator::operator!=(const SinglyLinkedList<T>::Iterator &other) const{
    return this->current != other.current;
}
template<class T> 
SinglyLinkedList<T>::Iterator &SinglyLinkedList<T>::Iterator::operator++(){
     if (current == nullptr) {
            throw out_of_range("Iterator cannot advance past end!");
        }
        current = current->next;
        return *this;
}
template<class T> 
SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::Iterator::operator++(int){
    if (current == nullptr) {
            throw out_of_range("Iterator cannot advance past end!");
        }
        Iterator temp = *this; 
        current = current->next; 
        return temp; 
}





// TODO: implement other methods of SinglyLinkedList::Iterator



// ----------------- VectorStore Implementation -----------------

VectorStore::VectorStore(int dimension = 512, EmbedFn embeddingFunction = nullptr) {
    // TODO
    this-> dimension = dimension;
    this-> count = 0;
    this-> embeddingFunction = embeddingFunction;
}

VectorStore::~VectorStore() {
    // TODO
    clear();
}
int VectorStore::size() const{
    return this->count;
}
bool VectorStore::empty() const{
    return (this->count == 0);
}
void VectorStore::clear(){
     for (int i = 0; i < count; i++) {
        delete records.get(i)->vector;
        delete records.get(i);
    }
    records.clear();
    count = 0;
}

SinglyLinkedList<float> *VectorStore::preprocessing(std::__cxx11::string rawText){
    SinglyLinkedList<float>* vector = embeddingFunction(rawText);
    int length = vector->size();

    while (length > dimension) { 
        vector->removeAt(length - 1);
        length--;
    }
    while (length < dimension) { 
        vector->add(0.0);
        length++;
    }
    return vector;
}
void VectorStore::addText(std::__cxx11::string rawText){
    VectorRecord* rec = new VectorRecord(count + 1, rawText, preprocessing(rawText));
    records.add(rec);
    count++;
}
SinglyLinkedList<float> &VectorStore::getVector(int index){
     if (index < 0 || index >= count) throw out_of_range("Invalid index!");
    return *(records.get(index)->vector);
}
std::__cxx11::string VectorStore::getRawText(int index) const{
    if (index < 0 || index >= count) throw out_of_range("Invalid index!");
    return records.get(index)->rawText;
}
int VectorStore::getId(int index) const{
     if (index < 0 || index >= count) throw out_of_range("Invalid index!");
    return records.get(index)->id;
}
bool VectorStore::removeAt(int index){
     if (index < 0 || index >= count) throw out_of_range("Invalid index!");
    delete records.get(index)->vector;
    delete records.get(index);
    records.removeAt(index);
    count--;
    return true;
}
bool VectorStore::updateText(int index, std::__cxx11::string newRawText){
    if (index < 0 || index >= count) throw out_of_range("Invalid index!");
    VectorRecord* rec = records.get(index);
    delete rec->vector;
    rec->rawText = newRawText;
    rec->rawLength = newRawText.size();
    rec->vector = preprocessing(newRawText);
    return true;
}
void VectorStore::setEmbeddingFunction(VectorStore::EmbedFn newEmbeddingFunction){
     this->embeddingFunction = newEmbeddingFunction;
}
void VectorStore::forEach(void (*action)(SinglyLinkedList<float> &, int, std::__cxx11::string &)){
     for (int i = 0; i < count; i++) {
        action(*(records.get(i)->vector), records.get(i)->id, records.get(i)->rawText);
    }
}
double VectorStore::cosineSimilarity(const SinglyLinkedList<float> &v1, const SinglyLinkedList<float> &v2) const{
    double v1v2 = 0, v1Squared = 0, v2Squared = 0;

    auto it1 = v1.begin();
    auto it2 = v2.begin();
    while (it1 != v1.end() && it2 != v2.end()) {
        v1v2   += (*it1) * (*it2);
        v1Squared += (*it1) * (*it1);
        v2Squared += (*it2) * (*it2);
        ++it1; ++it2;
    }
    if (v1Squared == 0 || v1Squared == 0) return 0;
    return v1v2 / (sqrt(v1Squared) * sqrt(v2Squared));
}
double VectorStore::l1Distance(const SinglyLinkedList<float> &v1, const SinglyLinkedList<float> &v2) const{
    auto it1 = v1.begin();
    auto it2 = v2.begin();
    double sum;
    while (it1 != v1.end() && it2 != v2.end()) {
        sum += fabs((*it1) - (*it2));
        ++it1; ++it2;
    }
    return sum;
}
double VectorStore::l2Distance(const SinglyLinkedList<float> &v1, const SinglyLinkedList<float> &v2) const{
     double sum = 0;
    auto it1 = v1.begin();
    auto it2 = v2.begin();
    while (it1 != v1.end() && it2 != v2.end()) {
        double diff = (*it1) - (*it2);
        sum += diff * diff;
        ++it1; ++it2;
    }
    return sqrt(sum);
}
int VectorStore::findNearest(const SinglyLinkedList<float> &query, const std::__cxx11::string &metric = "cosine") const{
   int bestIdx = -1;
    double bestValue;

    if (metric == "cosine") {
        bestValue = -1e9;   // tìm max similarity
    } else {
        bestValue = 1e18;   // tìm min distance
    }

    for (int i = 0; i < count; i++) {
        double metricValue;
        if (metric == "cosine") {
            metricValue = cosineSimilarity(query, *(records.get(i)->vector));
            if (metricValue > bestValue) {
                bestValue = metricValue;
                bestIdx = i;
            }
        }
        else if (metric == "euclidean") {
            metricValue = l2Distance(query, *(records.get(i)->vector));
            if (metricValue < bestValue) {
                bestValue = metricValue;
                bestIdx = i;
            }
        }
        else if (metric == "manhattan") {
            metricValue = l1Distance(query, *(records.get(i)->vector));
            if (metricValue < bestValue) {
                bestValue = metricValue;
                bestIdx = i;
            }
        }
        else {
            //throw metric_error();
        }
    }
    return bestIdx;
}


void merge(double* scores, int* indices, int left, int mid, int right, bool cosineMetric) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    
    double* Ls = new double[n1];
    double* Rs = new double[n2];
    int* Li = new int[n1];
    int* Ri = new int[n2];

    for (int i = 0; i < n1; i++) {
        Ls[i] = scores[left + i];
        Li[i] = indices[left + i];
    }
    for (int j = 0; j < n2; j++) {
        Rs[j] = scores[mid + 1 + j];
        Ri[j] = indices[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        bool cond;
        if (cosineMetric) cond = (Ls[i] > Rs[j]);   // cosine: lớn hơn tốt hơn
        else cond = (Ls[i] < Rs[j]);                // distance: nhỏ hơn tốt hơn

        if (cond) {
            scores[k] = Ls[i];
            indices[k] = Li[i];
            i++;
        } else {
            scores[k] = Rs[j];
            indices[k] = Ri[j];
            j++;
        }
        k++;
    }

    // Copy
    while (i < n1) {
        scores[k] = Ls[i];
        indices[k] = Li[i];
        i++; k++;
    }
    while (j < n2) {
        scores[k] = Rs[j];
        indices[k] = Ri[j];
        j++; k++;
    }

    delete[] Ls; delete[] Rs;
    delete[] Li; delete[] Ri;
}

// MergeSort
void mergeSort(double* scores, int* indices, int left, int right, bool cosineMetric) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(scores, indices, left, mid, cosineMetric);
        mergeSort(scores, indices, mid + 1, right, cosineMetric);
        merge(scores, indices, left, mid, right, cosineMetric);
    }
}

int *VectorStore::topKNearest(const SinglyLinkedList<float> &query, int k, const std::__cxx11::string &metric = "cosine") const{
     if (metric != "cosine" && metric != "euclidean" && metric != "manhattan")
        //throw metric_error();
    if (k <= 0 || k > count) throw invalid_k_value();

    double* scores = new double[count];
    int* indices = new int[count];

    for (int i = 0; i < count; i++) {
        SinglyLinkedList<float>& v = *(records.get(i)->vector);
        if (metric == "cosine") scores[i] = cosineSimilarity(query, v);
        else if (metric == "euclidean") scores[i] = l2Distance(query, v);
        else scores[i] = l1Distance(query, v);

        indices[i] = i;
    }

    bool cosineMetric = (metric == "cosine");
    mergeSort(scores, indices, 0, count - 1, cosineMetric);

    int* result = new int[k];
    for (int i = 0; i < k; i++) {
        result[i] = indices[i];
    }

    delete[] scores;
    delete[] indices;

    return result;
}
// TODO: implement other methods of VectorStore


// Explicit template instantiation for char, string, int, double, float, and Point

template class ArrayList<char>;
template class ArrayList<string>;
template class ArrayList<int>;
template class ArrayList<double>;
template class ArrayList<float>;
template class ArrayList<Point>;

template class SinglyLinkedList<char>;
template class SinglyLinkedList<string>;
template class SinglyLinkedList<int>;
template class SinglyLinkedList<double>;
template class SinglyLinkedList<float>;
template class SinglyLinkedList<Point>;
