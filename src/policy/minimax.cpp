#include <cstdlib>
#include<vector>
#include<climits>
#include<cmath>
#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief minimax get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

//sudo code from ppt
int Minimax::minimax(State *state, int max_depth, bool is_player_minimizer) {
  if (max_depth == 0) {
    return state->evaluate();
  }

  // Is the current player the minimizer?
  if (is_player_minimizer) {
    int value = -1e9;
    for (auto& move : state->legal_actions) {
      State* new_state = state->next_state(move);
      int tmpVal = minimax(new_state, max_depth - 1, false);
      value = std::max(value, tmpVal);
    }
    return value;
  }
  // Or the maximizer?
  else{
    int value = 1e9;
    for (auto& move : state->legal_actions) {
      State* new_state = state->next_state(move);
      int tmpVal = minimax(new_state, max_depth - 1, true);
      value = std::min(value, tmpVal);
    }
    return value;
  }
}