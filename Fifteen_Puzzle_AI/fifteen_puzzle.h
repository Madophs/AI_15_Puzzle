#ifndef FIFTEEN_PUZZLE_H
#define FIFTEEN_PUZZLE_H

#endif // FIFTEEN_PUZZLE_H

#include <bits/stdc++.h>

using namespace std;

const int ROWS = 4, COLS = 4, LAST_VALUE = 15, MAX_STEPS = 55, INF = (int)1e9;
const string directions = "RLUD";
int crow[] = { 0, 0,-1, 1};
int ccol[] = { 1,-1, 0, 0};
int limit, newLimit;
vector<int> puzzle(ROWS*COLS);
unordered_map<unsigned long long, int> state;
unordered_map<int,int> solution;
string generatedSolution = "";

bool solved(){
    for(int i = 0; i < puzzle.size(); i++)
        if(puzzle[i] != i) return false;
    return true;
}

int sumAllManhattanDistances(){
    int sum = 0, row, col;
    for(int i = 0; i < puzzle.size(); i++){
        if(puzzle[i] == LAST_VALUE) continue;
        row = puzzle[i] / 4, col = puzzle[i] % 4;
        sum += abs(row - (i / 4)) + abs(col - (i % 4));
    }
    return sum;
}

int manhattanDistance(int row, int col, int newRow, int newCol){
    int tgtRow = puzzle[newRow*4+newCol] / 4, tgtCol = puzzle[newRow*4+newCol] % 4;
    return -(abs(newRow - tgtRow) + abs(newCol - tgtCol)) + (abs(row - tgtRow) + abs(col - tgtCol));

}

bool validLocation(int row, int col){
    return row > -1 && row < 4 && col > -1 && col < 4;
}

bool dfs(int g, int h){
    if(g + h > limit){
        newLimit = min(newLimit, g + h);
        return false;
    }
    if(solved()) return true;
    unsigned long long currentState = 0;
    for(int i = 0; i < puzzle.size(); i++){
        currentState <<= 4;
        currentState += puzzle[i];
    }
    if(state.count(currentState) && state.find(currentState)->second <= g)
        return false;
    state[currentState] = g;
    int row, col, newRow, newCol;
    for(int i = 0; i < puzzle.size(); i++){
        if(puzzle[i] == LAST_VALUE){
            row = i / 4;
            col = i % 4;
            break;
        }
    }
    for(int i = 0; i < 4 ; i++){
        newRow  = row + crow[i], newCol = col + ccol[i];
        if(validLocation(newRow, newCol)){
            int hDelta = manhattanDistance(row, col, newRow, newCol);
            swap(puzzle[row * 4 + col], puzzle[newRow * 4 + newCol]);
            solution[g+1] = i;
            if(dfs(g+1, h + hDelta))
                return true;
            swap(puzzle[row * 4 + col], puzzle[newRow * 4 + newCol]);
        }
    }
    return false;
}

int idaStar(){
    limit = sumAllManhattanDistances();
    while(true){
        newLimit = INF;
        solution.clear();
        state.clear();
        if(dfs(0, sumAllManhattanDistances())){
            return limit;
        }else{
            if(newLimit == INF) return -1;
            limit = newLimit;
            if(limit > MAX_STEPS) return -1;
        }
    }
    return -1;
}

void instructions(int index){
    if(index-1 < 0) return;
    instructions(index-1);
    generatedSolution.push_back(directions[solution.find(index)->second]);
}

string generateSolution(vector<vector<int>> grid){
    generatedSolution = "";
    int emptyCell = 0, ans;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            puzzle[i*4+j] = grid[i][j]-1;
            if(puzzle[i*4+j] == LAST_VALUE){;
                emptyCell = i*4+j;
            }
        }
    }
    ans = idaStar();
    instructions(ans);
    return generatedSolution;
}
