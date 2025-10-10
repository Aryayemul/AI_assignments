#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<queue>
#include<algorithm>
using namespace std;

//check is solvable
bool isSolvable(vector<int> state){
    int inversion = 0;
    int n = state.size();
    for(int i=0;i<n;i++){
        for(int j = i+1 ; j<n;j++){
            if(state[i] != 0 && state[j] != 0 && state[i] > state[j]){
                inversion++;
            }
        }
    }
    return (inversion % 2 == 0);
}


//get all possible directions and generate them
vector<vector<int>> getMoves(vector<int>state,vector<vector<int>>&visited){
    int empTileIdx = find(state.begin(),state.end(),0) - state.begin();
    
    //check possible moves
    vector<string>moves;
    if(empTileIdx > 2){
        //not in first row i.e. idx != 0,1 or 2
        moves.push_back("UP");
    }
    if(empTileIdx <6){
        //not in last row i.e. idx != 6,7,8
        moves.push_back("DOWN");
    }
    if(empTileIdx % 3 != 0 ){
        //not in first col i.e. idx != 0,3,6 
        moves.push_back("LEFT");
    }
    if((empTileIdx+1)%3 != 0 ){
        //not in last col i.e. idx != 2,5,8
        moves.push_back("RIGHT");
    }
   
    //generate states for possiblemoves:
    vector<vector<int>> possibleState;
    for(auto move : moves){
        vector<int> newState = state;
        if(move == "UP"){
            swap(newState[empTileIdx], newState[empTileIdx -3]);
        }else if(move == "DOWN"){
            swap(newState[empTileIdx],newState[empTileIdx + 3]);
        }else if(move == "LEFT"){
            swap(newState[empTileIdx],newState[empTileIdx -1]);
        }else if(move == "RIGHT"){
            swap(newState[empTileIdx],newState[empTileIdx +1]);
        }

        //check if not visited
        if(find(visited.begin(),visited.end(),newState) == visited.end()){
            possibleState.push_back(newState);
        }
    }
    return possibleState;

}

//BFS Logic 
vector<vector<int>> solveByBFS(vector<int> start){
    vector<int> target = {1,2,3,4,5,6,7,8,0};
    queue<vector<int>> q;
    vector<vector<int>> visited;

    q.push(start);

    while(!q.empty()){
        vector<int> state = q.front();
        q.pop();
        visited.push_back(state);

        if(state == target){
            return visited;
        }

        vector<vector<int>> nextMoves = getMoves(state,visited);
        for(auto move : nextMoves){
            if(find(visited.begin(),visited.end(),move) == visited.end()){
                q.push(move);
            }
        }
    }
    return {};
}


//dfs logic
vector<int> dfsSolve(const vector<int>& start, const vector<int>& target) {
    stack<vector<int>> st;
    st.push(start);

    vector<vector<int>> visited; // now passed to getMoves

    while (!st.empty()) {
        vector<int> current = st.top();
        st.pop();

        visited.push_back(current);

        if (current == target) {
            return current; // solution found
        }

        // neighbors already filtered for visited
        vector<vector<int>> neighbors = getMoves(current, visited);
        for (auto& next : neighbors) {
            st.push(next);
        }
    }
    return {}; // no solution
}
int main(){
    vector<int> state1 = {8,1,2,0,4,3,7,6,5};
    vector<int> state2 = {1,8,2,0,4,3,7,6,5};
    if(isSolvable(state1)){
        cout<<"Solvable\n";
        auto result = solveByBFS(state1);
        cout<<"Number of visited states:"<<result.size()<<endl;
        cout<<"Final state: ";
        for(int x : result.back()) cout<<x<<" ";
        cout<<endl;
    }else{
        cout<<"No solution\n";
    }

    if(isSolvable(state2)){
        cout<<"Solvable\n";
        auto result = solveByBFS(state2);
        cout<<"Number of visited states:"<<result.size()<<endl;
        cout<<"Final state: ";
        for(int x : result.back()) cout<<x<<" ";
        cout<<endl;
    }else{
        cout<<"No solution\n";
    }
}
