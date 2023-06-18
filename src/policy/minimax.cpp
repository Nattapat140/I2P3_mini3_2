#include <cstdlib>
#include<vector>
#include<climits>
#include<cmath>
#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

/*Move Minimax::get_move(State *state, int depth, bool maximizingPlayer){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  //return actions[(rand()+depth)%actions.size()];
  int k = depth;
  for(int i=0;i<depth;i++){
    k = rand()/k;
  }
  return actions[k%actions.size()];
}*/
//State* move;
int Minimax::minimax(State *state, int max_depth, bool is_player_minimizer) {
  if (max_depth == 0) {
    return state->evaluate();
  }

  // Is the current player the minimizer?
  if (is_player_minimizer) {
    int value = INT_MIN;
    /*if(!state->legal_actions.size()){
      state->get_legal_actions();
    }*/
    for (auto& move : state->legal_actions) {
      State* new_state = state->next_state(move);
      int evaluation = minimax(new_state, max_depth - 1, false);
      value = std::max(value, evaluation);
    }
    return value;
  }
  // Or the maximizer?
  else{
    int value = INT_MAX;
    /*if(!state->legal_actions.size()){
      state->get_legal_actions();
    }*/
    for (auto& move : state->legal_actions) {
      State* new_state = state->next_state(move);
      int evaluation = minimax(new_state, max_depth - 1, true);
      value = std::min(value, evaluation);
    }
    return value;
  }
}