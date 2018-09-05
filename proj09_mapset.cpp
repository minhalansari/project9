//project proj09
//11 functions for class MapSet
//find_key returns an iterator to the given key 
////initializer_list is a constructor for class map set and adds all elements in the list to the vector v_
//size returns the size of vector v_
//get returns the pair associated with the given string
//update updates existing keys in mapset
//remove removes the pair associated with the given key
//add adds a pair into the vector v_ in sorted order
//compare compares two map sets and returns a number based off the first different element
//mapset_union returns a new mapset that contains the contents of both mapsets 
//mapset_intersection returns a new mapset that contains keys that are common between both mapsets
//friend operator writes mapset on ostream and returns it


#include "proj09_mapset.h"
#include<vector>
using std::vector; 
#include<iostream>
using std::cout; using std::endl; using std::boolalpha;using std::ostream;
#include<algorithm>
using std::copy; using std::lower_bound;
#include<utility>
using std::pair; using std::make_pair;




ostream& operator<<(ostream& out, MapSet& ms){
    for (int i=0; i<ms.v_.size(); i++){
        out << (i==0 ? "" : ", ") << ms.ary[i].first << ":" << ms.ary_[i].second;
    }
    return out;
}

vector< pair <string, long> >::iterator MapSet::find_key(string s){
    //find iterator of string value 
    auto it = std::lower_bound(v_.begin(), v_.end(), s,[](std::pair<string ,long> const & x, string d){ return x.first < d; }); 
    
}

bool MapSet::add(pair<string,long> p){
    int check = 0;
    for(auto i = 0; i < v_.size(); i++){ 
        if(v_[i].first == p.first){ //check if string already in v_
            check = 100;
            return false;
        }
    }
    if(check != 100){ //use find_key to get iterator and insert into v_ 
        auto itr = find_key(p.first);
        v_.insert(itr, p);
        return true;
    }
    
}

MapSet::MapSet(initializer_list< pair<string ,long > > vlist){
    
    std::initializer_list< pair<string, long> >::iterator it; //iterator through initializer_list and add values to v_
    for ( it=vlist.begin(); it!=vlist.end(); ++it){
        add(*it);
    }
}

size_t MapSet::size(){
    return v_.size(); //return size of v
}
pair<string,long> MapSet::get(string s ){
    int check = 0;
    pair<string, long> default_pair = make_pair("" , 0); //default pair
    for(auto i = 0; i < v_.size(); i++){ //go through elements in vector
        if(v_[i].first == s){
            check = 100; //return pair if string found
            return v_[i];
        }
    }
    if(check != 100){ //if string not found return default pair
        return default_pair;
    }
}

bool MapSet::remove (string s){
    int check = 0;
    for(auto i = 0; i< v_.size(); i++){ //go through elements in v_
        if(v_[i].first == s){ //if string is found 
            auto itr = find_key(s); //get iterator
            v_.erase(itr); //use iterator to remove pair
            return true;
        }
    }
    if(check != 100){ //string not found
        return false;
    }
}

bool MapSet::update(string s ,long l){
    int check = 0;
    pair <string, long> new_pair = make_pair(s, l); //create new pair to add
    for(auto i = 0; i< v_.size(); i++ ){
        if(v_[i].first == s){ //if string found
            remove(s); //remove pair
            add(new_pair); //add new pair in its place
            check = 100;
            return true;
            
        }
    }
    if(check != 100){ //return false if string not found
        return false;
    }
}
MapSet MapSet::mapset_union (MapSet& ms){
    MapSet new_mapset; //initialize new MapSet
    
    for(auto i = 0; i< v_.size(); i++){ //go through elements in v_
        new_mapset.add(v_[i]); //add to new MapSet
    }
    for(auto i2 = 0; i2 < ms.v_.size(); i2++){ //go through other mapset
        string s = ms.v_[i2].first; //get key of other mapset
        int check = 0;
        for(auto i3 = 0; i3 < v_.size(); i3++){
            if(v_[i3].first ==s){ //check if key matches first vector
                check = 100;
            }
        }
        if(check != 100){
            new_mapset.add(ms.v_[i2]); //if it doesnt then add new pair
        }
    }
    return new_mapset;
    
}

MapSet MapSet::mapset_intersection(MapSet& ms){
    MapSet new_mapset2; //initialize new MapSet
    for(auto i = 0; i<v_.size(); i++){  //go through elements in vector
        string calling_key = v_[i].first; //get key
        for(auto i2 = 0; i2< ms.v_.size(); i2++ ){
            string other_key = ms.v_[i2].first;
            if(calling_key == other_key){ //if keys are the same then add to the new mapset
                new_mapset2.add(v_[i]);
            }
        }
    }
    return new_mapset2;
}

int MapSet::compare(MapSet& ms){
    size_t main_size = v_.size(); //size of calling MapSet
    size_t ms_size = ms.v_.size(); //size of parameter mapset
    int one = 1;
    int neg_one = -1;
    int zero = 0;
    //check which one is smaller
    size_t smaller_size = main_size; 
    if (main_size > ms_size){
        smaller_size = ms_size;
    }
    if(ms_size > main_size){
        smaller_size = main_size;
    }
    for(auto i = 0; i< smaller_size; i++){ //compare keys in each
        string calling_key = v_[i].first;
        string other_key = ms.v_[i].first;
        if(calling_key > other_key){
            return one;
        }
        if(other_key > calling_key){
            return neg_one;
        }

    }
    //if keys all the same compare sizes
    if(main_size > ms_size){
        return one;
    }
    if(ms_size > main_size){
        return neg_one;
    }
    if(main_size == ms_size){
        return zero;
    }
    
}


