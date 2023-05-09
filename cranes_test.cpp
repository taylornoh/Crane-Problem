///////////////////////////////////////////////////////////////////////////////
// cranes_test.cpp
//
// Unit tests for crane_algs.hpp
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <random>

#include "rubrictest.hpp"

//#include "cranes_types.hpp"
#include "cranes_algs.hpp"

int main() {

  Rubric rubric;

  const cranes::step_direction E = cranes::STEP_DIRECTION_EAST,
                               S = cranes::STEP_DIRECTION_SOUTH;

  cranes::grid empty2(2, 2), empty4(4, 4);
  cranes::path empty2_solution(empty2), empty4_solution(empty4);

  cranes::grid horizontal(4, 4);
  horizontal.set(0, 3, cranes::CELL_CRANE);
  cranes::path horizontal_solution(horizontal, {E, E, E});

  cranes::grid vertical(4, 4);
  vertical.set(3, 0, cranes::CELL_CRANE);
  cranes::path vertical_solution(vertical, {S, S, S});

  cranes::grid all_cranes(4, 4);
  for (cranes::coordinate r = 0; r < 4; ++r) {
    for (cranes::coordinate c = 0; c < 4; ++c) {
      if (!(r == 0 && c == 0)) {
        all_cranes.set(r, c, cranes::CELL_CRANE);
      }
    }
  }

  cranes::grid maze(4, 4);
  /*    ..XX
        X..X
        XX..
        XXXC   */
  maze.set(0, 2, cranes::CELL_BUILDING);
  maze.set(0, 3, cranes::CELL_BUILDING);
  maze.set(1, 0, cranes::CELL_BUILDING);
  maze.set(1, 3, cranes::CELL_BUILDING);
  maze.set(2, 0, cranes::CELL_BUILDING);
  maze.set(2, 1, cranes::CELL_BUILDING);
  maze.set(3, 0, cranes::CELL_BUILDING);
  maze.set(3, 1, cranes::CELL_BUILDING);
  maze.set(3, 2, cranes::CELL_BUILDING);
  maze.set(3, 3, cranes::CELL_CRANE);

  cranes::path maze_solution(maze, {E, S, E, S, E, S});


  rubric.criterion("exhaustive optimization - simple cases", 4,
		   [&]() {
         TEST_EQUAL("empty2", empty2_solution, crane_unloading_exhaustive(empty2));
         TEST_EQUAL("empty4", empty4_solution, crane_unloading_exhaustive(empty4));
         TEST_EQUAL("horizontal", horizontal_solution, crane_unloading_exhaustive(horizontal));
         TEST_EQUAL("vertical", vertical_solution, crane_unloading_exhaustive(vertical));
         auto output = crane_unloading_exhaustive(all_cranes);
         TEST_EQUAL("all_cranes path length", 7, output.steps().size());
         TEST_EQUAL("all_cranes total cranes", 6, output.total_cranes());
		   });

  rubric.criterion("exhaustive optimization - maze", 1,
		   [&]() {
         TEST_EQUAL("correct", maze_solution, crane_unloading_exhaustive(maze));
		   });

  rubric.criterion("dynamic programming - simple cases", 4,
		   [&]() {
         TEST_EQUAL("empty2", empty2_solution, crane_unloading_dyn_prog(empty2));
         TEST_EQUAL("empty4", empty4_solution, crane_unloading_dyn_prog(empty4));
         TEST_EQUAL("horizontal", horizontal_solution, crane_unloading_dyn_prog(horizontal));
         TEST_EQUAL("vertical", vertical_solution, crane_unloading_dyn_prog(vertical));
         auto output = crane_unloading_dyn_prog(all_cranes);
         TEST_EQUAL("all_cranes path length", 7, output.steps().size());
         TEST_EQUAL("all_cranes total cranes", 6, output.total_cranes());
		   });

  rubric.criterion("dynamic programming - maze", 1,
		   [&]() {
         TEST_EQUAL("correct", maze_solution, crane_unloading_dyn_prog(maze));
		   });

  rubric.criterion("stress test", 2,
		   [&]() {
         const cranes::coordinate ROWS = 5,
                                  MAX_COLUMNS = 15;
         const unsigned SEED = 20181130;

         std::mt19937 gen(SEED);

         for (cranes::coordinate columns = 1; columns <= MAX_COLUMNS; ++columns) {
           auto area = ROWS * columns,
                cranes = area / 5,
                buildings = area / 10;
           cranes::grid setting = cranes::grid::random(ROWS, columns, cranes, buildings, gen);
           TEST_EQUAL("random grid with " + std::to_string(columns) + " columns",
                      cranes::crane_unloading_exhaustive(setting).total_cranes(),
                      cranes::crane_unloading_dyn_prog(setting).total_cranes());
         }
		   });

  return rubric.run();
}