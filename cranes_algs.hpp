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

// 1. Generate all possible combinations of 1s and 0s (no recursion, just use two loops) (one function only)
// 2. Use bit shift to see what position you have 1s and 0s
// 3. Use add_step helper functions according to your ones and zeros (convert bit strings to 1s and 0s)
// 4. Pass candidate to is valid function
// 5. best = calculate the shortest lengths and max cranes (vectors of steps)

path crane_unloading_exhaustive(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  // Compute maximum path length, and check that it is legal.
  const size_t max_steps = setting.rows() + setting.columns() - 2;
  assert(max_steps < 64);

  // TODO: implement the exhaustive search algorithm, then delete this
  // comment.
  path best(setting);
  for (size_t bits = 0; bits < pow(2, max_steps); bits++) {
      path p(setting);

      std::vector<step_direction> candidate;
      for(size_t k = 0; k < max_steps; k++) {
        int bit = (bits >> k) & 1;
        if(bit == 1) {
          candidate.push_back(STEP_DIRECTION_SOUTH);
        } else {
          candidate.push_back(STEP_DIRECTION_EAST);
        }
      }
      for(step_direction s: candidate) {
        if(!p.is_step_valid(s))
          break;
        p.add_step(s);

        if(p.total_cranes() > best.total_cranes()) {
          best = p;
        }
      }

    }
  return best;
}

// Solve the crane unloading problem for the given grid, using a dynamic
// programming algorithm.
// The grid must be non-empty.

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

	  // TODO: implement the dynamic programming algorithm, then delete this comment.

   // assert(best->has_value());
   // std::cout << "total cranes" << (**best).total_cranes() << std::endl;
      }
    }

   return best;
	}

}