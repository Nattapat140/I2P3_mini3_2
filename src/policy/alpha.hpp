#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class AlphaBeta{
public:
  static int alphabeta(State *state, int max_depth, int alpha, int beta, bool is_player_minimizer);
};