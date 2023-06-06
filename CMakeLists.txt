cmake_minimum_required(VERSION 3.22)
project(sudoku)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        sudoku
        src/main.cpp
        src/core.cpp
)

# Tests

enable_testing()

add_test(
        NAME generate_final_board_small
        COMMAND $<TARGET_FILE:sudoku> -c 10
)

add_test(
        NAME generate_final_board
        COMMAND $<TARGET_FILE:sudoku> -c 1000
)

add_test(
        NAME generate_game_small
        COMMAND $<TARGET_FILE:sudoku> -n 10
)

add_test(
        NAME generate_game
        COMMAND $<TARGET_FILE:sudoku> -n 1000
)

add_test(
        NAME generate_game_normal
        COMMAND $<TARGET_FILE:sudoku> -n 1000 -m 2
)

add_test(
        NAME generate_game_hard
        COMMAND $<TARGET_FILE:sudoku> -n 1000 -m 3
)

add_test(
        NAME generate_game_with_range
        COMMAND $<TARGET_FILE:sudoku> -n 1000 -r 30~40
)

add_test(
        NAME generate_game_unique
        COMMAND $<TARGET_FILE:sudoku> -n 1000 -u
)

add_test(
        NAME generate_game_arg_combine
        COMMAND $<TARGET_FILE:sudoku> -n 1000 -m 2 -r 30~40 -u
)

add_test(
        NAME solve_game
        COMMAND $<TARGET_FILE:sudoku> -s ${CMAKE_CURRENT_SOURCE_DIR}/test/to_solve.txt
)

add_test(
        NAME show_test
        COMMAND $<TARGET_FILE:sudoku> -h
)

add_test(
        NAME invalid_solver_input_character
        COMMAND $<TARGET_FILE:sudoku> -s ${CMAKE_CURRENT_SOURCE_DIR}/test/invalid_character.txt
)

add_test(
        NAME invalid_solver_input_length
        COMMAND $<TARGET_FILE:sudoku> -s ${CMAKE_CURRENT_SOURCE_DIR}/test/invalid_length.txt
)

add_test(
        NAME solver_input_not_exist
        COMMAND $<TARGET_FILE:sudoku> -s ${CMAKE_CURRENT_SOURCE_DIR}/test/not_exist.txt
)

add_test(
        NAME invalid_opcode
        COMMAND $<TARGET_FILE:sudoku> -x
)

add_test(
        NAME invalid_range_1
        COMMAND $<TARGET_FILE:sudoku> -c 1000001
)

add_test(
        NAME invalid_range_2
        COMMAND $<TARGET_FILE:sudoku> -n 10001
)

add_test(
        NAME invalid_range_3
        COMMAND $<TARGET_FILE:sudoku> -n 10000 -m 4
)

add_test(
        NAME invalid_range_4
        COMMAND $<TARGET_FILE:sudoku> -n 10000 -m 3 -r 30-40
)

add_test(
        NAME invalid_range_5
        COMMAND $<TARGET_FILE:sudoku> -n 10000 -m 3 -r 40~60
)

add_test(
        NAME invalid_combine
        COMMAND $<TARGET_FILE:sudoku> -m 2 -r 30~40 -u
)

set_tests_properties(
        invalid_solver_input_character
        invalid_solver_input_length
        solver_input_not_exist
        invalid_opcode
        invalid_range_1
        invalid_range_2
        invalid_range_3
        invalid_range_4
        invalid_range_5
        invalid_combine
        PROPERTIES WILL_FAIL TRUE
)
