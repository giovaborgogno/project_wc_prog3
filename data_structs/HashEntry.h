#ifndef U05_HASH_HASHMAP_HASHENTRY_H_
#define U05_HASH_HASHMAP_HASHENTRY_H_

template <class K> class HashEntry {
private:
    K key;

public:
    int value;
    HashEntry(){};
    HashEntry(K key, int value) {
        this->key = key;
        this->value = value;
    }
    K getKey() { return key; }
    void setKey(K key) { this->key = key; }
    int getValue() { return value; }
    void setValue(int value) { this->value = value; }
    void incrementValue(){
        value = value+1;
    }
};

#endif // U05_HASH_HASHMAP_HASHENTRY_H_