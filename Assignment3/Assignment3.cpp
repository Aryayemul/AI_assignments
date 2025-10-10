#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

//Knowledge base
map<string,vector<string>> father;
map<string,vector<string>> mother;

//facts
void addFather(string f,string c){
    father[f].push_back(c);
}
void addMother(string m, string c){
    mother[m].push_back(c);
}

//Rules
//Parent
vector<string> getChildren(string p){
    vector<string> result;
    for(string c : father[p]) result.push_back(c);
    for(string c : mother[p]) result.push_back(c);
    return result;
}

//get siblings
vector<string> getSiblings(string name){
    vector<string> result;

    //check in father
    for(auto&entry:father){
        vector<string> children = entry.second;//extract children of father[idx]
        bool found = false;

        //find through loop the child whose siblings to be found
        for(string c : children){
            if(c==name) found=true;   
        }

        //if found add the silbings
        if(found){
            for (string c: children) {
            if(c!=name){
                result.push_back(c);
            }
            }
        }
    }

    //check in mother
    for(auto &entry:mother){
        vector<string>children = entry.second;
        bool found = false;
        for(string c : children){
            if(c == name){
                found = true;
            }
        }
        if(found){
            for(string c:children){
                if(c!=name) result.push_back(c);
            }
        }
    }
}

//get grandchildren
vector<string> getGrandchildren(string gp){
    
    vector<string> result;
    for(string child : father[gp]){
        vector<string> gkids = getChildren(child);
        result.insert(result.end(),gkids.begin(),gkids.end());
    }

    for(string child : mother[gp]){
        vector<string> gkids = getChildren(child);
        result.insert(result.end(),gkids.begin(),gkids.end());
    }

    return result;

    // vector<string>result;
    // vector<string> children;
    // vector<string> grandchildren;
    // //get all children (i.e. parents of grandchildren)
    // for(string c : father[gp]) children.push_back(c);
    // for(string c:mother[gp]) children.push_back(c);

    // //for each child find their children
    // for(string child:children){
    //    vector<string> grandchildren = getChildren(child);
    //    for(string gc : grandchildren) grandchildren.push_back(gc);
    // }
  

    // return grandchildren;


}

// Main
int main() {
    // Add facts
    addFather("John", "Alice");
    addFather("John", "Bob");
    addMother("Mary", "Alice");
    addMother("Mary", "Bob");

    addFather("Bob", "Charlie");
    addMother("Sara", "Charlie");

    addFather("Bob", "Daisy");
    addMother("Sara", "Daisy");

    // Query examples
    cout << "Children of John: ";
    for (string c : getChildren("John")) cout << c << " ";
    cout << endl;

    cout << "Siblings of Alice: ";
    for (string s : getSiblings("Alice")) cout << s << " ";
    cout << endl;

    cout << "Grandchildren of John: ";
    for (string gc : getGrandchildren("John")) cout << gc << " ";
    cout << endl;

    cout << "Grandchildren of Mary: ";
    for (string gc : getGrandchildren("Mary")) cout << gc << " ";
    cout << endl;

    return 0;
}