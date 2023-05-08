///////////////////////////////////////////////////////////////////////////////
// cranes_algs.hpp
//
// Algorithms that solve the crane unloading problem.
//
// All of the TODO sections for this project reside in this file.
//
// This file builds on crane_types.hpp, so you should familiarize yourself
// with that file before working on this file.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cassert>
#include <math.h>

#include "cranes_types.hpp"

namespace cranes {

// Solve the crane unloading problem for the given grid, using an exhaustive
// optimization algorithm.
//
// This algorithm is expected to run in exponential time, so the grid's
// width+height must be small enough to fit in a 64-bit int; this is enforced
// with an assertion.
//
// The grid must be non-empty.
path crane_unloading_exhaustive(const grid& setting) {
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  const size_t max_steps = setting.rows() + setting.columns() - 2;
  assert(max_steps < 64);

  path best(setting);
  for (size_t steps = 0; steps <= max_steps; steps++) {
    for (size_t i = 0; i <= steps; i++) {
      size_t j = steps - i;
      if (i >= setting.rows() || j >= setting.columns()) {
        continue;
      }
      if (setting.get(i, j) == CELL_BUILDING) {
        continue;
      }
      for (size_t k = 0; k <= steps; k++) {
        size_t l = steps - k;
        if (k >= setting.rows() || l >= setting.columns()) {
          continue;
        }
        if (setting.get(k, l) == CELL_BUILDING) {
          continue;
        }
        path candidate(setting);

        candidate = best;
        if (i == 0 && j == 0) {
          if(candidate.is_step_valid(STEP_DIRECTION_START)) {
            candidate.add_step(STEP_DIRECTION_START);
          }
        } else if (i == k && j < l) {
        if(candidate.is_step_valid(STEP_DIRECTION_SOUTH)) {
            candidate.add_step(STEP_DIRECTION_SOUTH);
          }
        } else if(i < k && j == l) {
        if(candidate.is_step_valid(STEP_DIRECTION_EAST)) {
            candidate.add_step(STEP_DIRECTION_EAST);
          }
        }
        if (candidate.total_cranes() < best.total_cranes()) {
          best = candidate;
        }
      }
    }
  }
  return best;
}

// Solve the crane unloading problem for the given grid, using a dynamic
// programming algorithm.
//
// The grid must be non-empty.
//path crane_unloading_dyn_prog(const grid& setting) {
path crane_unloading_dyn_prog(const grid& setting) {

  path best(setting);

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);


  using cell_type = std::optional<path>;

  std::vector<std::vector<cell_type> > A(setting.rows(),
                                        std::vector<cell_type>(setting.columns()));

  A[0][0] = path(setting);
  assert(A[0][0].has_value());

  for (coordinate r = 0; r < setting.rows(); ++r) {
    for (coordinate c = 0; c < setting.columns(); ++c) {

      if (setting.get(r, c) == CELL_BUILDING){
        A[r][c].reset();
        continue;
        }

    cell_type from_above = std::nullopt;
    cell_type from_left = std::nullopt;

	    // TODO: implement the dynamic programming algorithm, then delete this
  // comment.

   // assert(best->has_value());
//  //   std::cout << "total cranes" << (**best).total_cranes() << std::endl;

	}
}
return best;
}
}