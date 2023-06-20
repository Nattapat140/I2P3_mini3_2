#include <iostream>
#include <fstream>
#include <cstdlib>
#include<vector>
#include<climits>
#include<cmath>
#include "../config.hpp"
#include "../state/state.hpp"
#include "../policy/alpha.hpp"


State* root;

/**
 * @brief Read the board from the file
 * 
 * @param fin 
 */
void read_board(std::ifstream& fin) {
  Board board;
  int player;
  fin >> player;

  for (int pl=0; pl<2; pl++) {
    for (int i=0; i<BOARD_H; i++) {
      for (int j=0; j<BOARD_W; j++) {
        int c; fin >> c;
        // std::cout << c << " ";
        board.board[pl][i][j] = c;
      }
      // std::cout << std::endl;
    }
  }
  root = new State(board, player);
  root->get_legal_actions();
}


/**
 * @brief choose a move and then write it into output file
 * 
 * @param fout 
 */
void write_valid_spot(std::ofstream& fout) {
  // Keep updating the output until getting killed.
  if(!root->legal_actions.size()){
    root->get_legal_actions();
  }
  int max_val = -1e9; //make it lowest val 
  int curr_val = 0;
  Move move;
  for(auto& curr : root->legal_actions){
    //call alpha func to get the max value
    curr_val = AlphaBeta::alphabeta(root->next_state(curr), 5,-1e9,1e9, false);
    //then compare the value
    if(curr_val > max_val){
      move = curr; //choose the best move
      max_val = curr_val; //set the next max val
    }
    //bug if it's the same place then it will be invalid move so we need to check it first 
    //if it equal then we choose the first guy in legal_actions
    //it's actually dont have to be the first guy but I dont know what to choose in the case where there is no avaible move to choose.
    //prevent move 0,0 to 0,0 like A6->A6
    if(move.first == move.second){
      move = root->legal_actions[0];
    }
    fout << move.first.first << " " << move.first.second << " "\
         << move.second.first << " " << move.second.second << std::endl;
    
    // Remember to flush the output to ensure the last action is written to file.
    fout.flush();
  }
}


/**
 * @brief Main function for player
 * 
 * @param argv 
 * @return int 
 */
int main(int, char** argv) {
  srand(RANDOM_SEED);
  std::ifstream fin(argv[1]);
  std::ofstream fout(argv[2]);

  read_board(fin);
  write_valid_spot(fout);

  fin.close();
  fout.close();
  return 0;
}
