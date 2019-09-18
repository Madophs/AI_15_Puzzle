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
vector<int> solvedPuzzle;
unordered_map<unsigned long long, int> state;
unordered_map<int,int> solution;
string generatedSolution = "";
bool alreadySolved = false;

void initializePuzzleSolved(int puzzleId){
    if(puzzleId == 1){
        solvedPuzzle.assign({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
    }else if(puzzleId == 2){
        /*
         * 0, 1, 2, 3
         * 11,12,13,4
         * 10,15,14,5
         * 9,8, 7,6
         */
        solvedPuzzle.assign({0, 1, 2, 3, 11, 12, 13, 4, 10, 15, 14, 5, 9, 8, 7, 6});
    }else if(puzzleId == 3){
        /*
         * 0	4	8	12
         * 1	5	9	13
         * 2	6	10	14
         * 3	7	11	15
         */
        solvedPuzzle.assign({0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15});
    }else if(puzzleId == 4){
        /*
         * 6	5	4	15
         * 7	0	3	14
         * 8	1	2	13
         * 9	10	11	12
         */

        solvedPuzzle.assign({6, 5, 4, 15, 7, 0, 3, 14, 8, 1, 2, 13, 9, 10, 11, 12});
    }else if(puzzleId == 5){
        /*
         * 6	12	13	15
         * 5	7	11	14
         * 1	4	8	10
         * 0	2	3	9
         */
        solvedPuzzle.assign({6, 12, 13, 15, 5, 7, 11, 14, 1, 4, 8, 10, 0, 2, 3, 9});
    }
}

int getIndex(int val){
    int i = 0;
    for(; i < 16; ++i)
        if(solvedPuzzle[i] == val) break;
    return i;
}

bool solved(){
    for(int i = 0; i < puzzle.size(); i++)
        if(puzzle[i] != solvedPuzzle[i]) return false;
    return true;
}

int sumAllManhattanDistances(){
    int sum = 0, row, col;
    for(int i = 0; i < puzzle.size(); i++){
        if(puzzle[i] == LAST_VALUE) continue;
        row = getIndex(puzzle[i]) / 4, col = getIndex(puzzle[i]) % 4;
        sum += abs(row - (getIndex(solvedPuzzle[i]) / 4)) + abs(col - (getIndex(solvedPuzzle[i]) % 4));
    }
    return sum;
}

int manhattanDistance(int row, int col, int newRow, int newCol){
    int tgtRow = getIndex(puzzle[newRow*4+newCol]) / 4, tgtCol = getIndex(puzzle[newRow*4+newCol]) % 4;
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

string generateSolution(vector<vector<int>> grid, int puzzleId){
    generatedSolution = "";
    initializePuzzleSolved(puzzleId);
    int emptyCell = 0, ans;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            puzzle[i*4+j] = grid[i][j]-1;
            if(puzzle[i*4+j] == LAST_VALUE){;
                emptyCell = i*4+j;
            }
        }
    }
    if(solved()){
        alreadySolved = true;
        return "";
    }
    ans = idaStar();
    instructions(ans);
    return generatedSolution;
}
