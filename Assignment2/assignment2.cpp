#include<iostream>
#include<map>
#include<set>
#include<string>

using namespace std;

//Possible colors
vector<string>colors = {'Red','Green','Blue'};

//Graph: adjacency ist for each region
map<string,vector<string>> neighbors;

bool isConsistent(const string&region,const string& color,const map<string,string>&assignment){
   vector<string>neighborList = neighbors[region];
   for(size_t i =0; i < neighborList.size();++i){
    string neighbor = neighborList[i];
    if(assignment.find(neighbor)!=assignment.end() && assignment.at(neighbor) == color){
        return false;
    }
   }
   return true;
}

bool forwardCheck(const string&region, const string&color, map<string,set<string>>&domains,  const map<string,string>& assignment){

    vector<string> neighborList = neighbors[region];//get all the neighbor regions

    //Iterate through each neighbor of the curr region
    for(size_t i = 0; i<neighborList.size(); ++i){
        string neighbor  = neighborList[i];
        if(assignment.find(neighbor) == assignment.end()){ //only consider unassigned neighbors
            if(domains[neighbor].count(color)){
                domains[neighbor].erase(color); //remove the assigned color from neighbor's domain if present.
            }
            if(domains[neighbor].empty()){ 
                return false; //if the neighbor has no legal colors left then curr assignment = dead-end(triggers backtrack)
            }
        }
    }
    return true; //If every unassigned neighbor still has at least one color, forward checking succeeded.
}

bool backtrack(map<string,string>& assignment,map<string,set<string> & domains, const vector<string>& varOrder,int index){
    
    if(index == varOrder.size()) return true; // Base-case(sol found)

    string region = varOrder[index]; //pick curr region
    set<string> domainColors = domains[region]; //get possible colors for this reion

    //loop over all possible colors in domain
    for(set<string>::iterator it = domainColors.begin(); it != domainColors.end(); ++it){
        string color = *it;

        if(isConsistent(region,color,assignment)){//if satisfiying the condition

            //Save domains to restore after backtracking
            map<string, set<string>> savedDomains = domains;

            assignment[region] = color;

            if(forwardCheck(region,color,domains,assignment)){//Prue the domains by removin color from unassigned neighbors and if possible move next(recursive)
                if(backtrack(assignment,domains,varOrder,index+1)){
                    return true;
                }
            }
            //Backtrack
            assignment.erase(region);
            domains = savedDomains;
        }
    }
    return false;


}

int main(){
    // Define neighbors
    neighbors["WA"] = vector<string>{"NT", "SA"};
    neighbors["NT"] = vector<string>{"WA", "SA", "Q"};
    neighbors["SA"] = vector<string>{"WA", "NT", "Q", "NSW", "V"};
    neighbors["Q"] = vector<string>{"NT", "SA", "NSW"};
    neighbors["NSW"] = vector<string>{"SA", "Q", "V"};
    neighbors["V"] = vector<string>{"SA", "NSW"};
    neighbors["T"] = vector<string>{};

    //Variable assignment order
    vector<string> varOrder = {"WA", "NT", "SA", "Q", "NSW", "V", "T"};

    //Initialize domains
    map<string, set<string>> domains;
    for(size_t i = 0; i <varOrder.size(); ++i){
        set<string> domainSet(colors.begin(), colors.end());
        domains[varOrder[i]] = domainSet;
    }

    //Assignment result
    map<string, string> assignment;

    if(backtrack(assignment,domains,varOrder, 0)){
        cout<<"Final Assignment:\n";
        map<string,string>::iterator it;
        for(it = assignment.begin(); it!=assignment.end(); ++it){
            cout<<it->first <<" = "<<it->second<<endl;

        }else{
            cout<<"No valid assignment found.\n"
        }

        return 0;
    }

}