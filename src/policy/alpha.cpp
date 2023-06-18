#include <cstdlib>
#include<vector>
#include<climits>
#include<cmath>
#include "../state/state.hpp"
#include "./alpha.hpp"


/**
 * @brief minimax get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int AlphaBeta::alphabeta(State *state, int max_depth,int alpha, int beta, bool is_player_minimizer){
  if (max_depth == 0) {
    return state->evaluate();
  }
  // Is the current player the minimizer?
  if (is_player_minimizer) {
    int value = -1e9;
    for (auto& move : state->legal_actions) {
      State* new_state = state->next_state(move);
      int evaluation = alphabeta(new_state, max_depth - 1,alpha, beta, false);
      value = std::max(value, evaluation);
      alpha = std::max(alpha, value);
      if(alpha >= beta){
        break;
      }
    }
    return value;
  }
  // Or the maximizer?
  else{
    int value = 1e9;
    for (auto& move : state->legal_actions) {
      State* new_state = state->next_state(move);
      int evaluation = alphabeta(new_state, max_depth - 1,alpha,beta, true);
      value = std::min(value, evaluation);
      beta = std::min(beta, value);
      if(beta <= alpha){
        break;
      }
    }
    return value;
  }
}