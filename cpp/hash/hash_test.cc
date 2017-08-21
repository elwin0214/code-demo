#include <iostream>
#include <unordered_set>
#include <memory>

using namespace std;

struct Key{
  size_t value_;
  Key(size_t value):value_(value){

  }
};

struct HashKey{

  size_t operator()(const Key& key){
    return key.value_;
  } 

};

struct EqualKey{
  
  bool operator()(const Key& key1, const Key& key2){
    return key1.value_ == key2.value_;
  } 

};

int main(){
  unordered_set<Key, HashKey, EqualKey> set;
  typedef unordered_set<Key, HashKey, EqualKey> Set;
  Key k1(1);
  Key k2(2);
  Key k3(3);
  std::pair<Set::iterator,bool>  p = set.insert(k1);
  cout << p.second << endl;
  std::pair<Set::iterator,bool>  p2 = set.insert(k1);
  cout << p2.second << endl;


  


  return 0;
}