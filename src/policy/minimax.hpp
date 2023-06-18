#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Minimax{
public:
  //static Move get_move(State *state, int depth, bool maximizingPlayer);
  static int minimax(State *state, int max_depth, bool is_player_minimizer);
};