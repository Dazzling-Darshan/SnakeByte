#include <iostream>
#include <vector>
#include <cassert>
#include "game.h"

// Stub random generator providing deterministic coordinates for tests
class StubRandom : public IRandom {
private:
    std::vector<int> predefinedValues;
    size_t index;

public:
    StubRandom(const std::vector<int>& values) : predefinedValues(values), index(0) {}

    int getRandom(int min, int max) override {
        if (index < predefinedValues.size()) {
            return predefinedValues[index++];
        }
        return min; // Fallback default
    }
};

// Test for Rule 1: Eating normal food increases score by 10 and length by 1
void test_rule1_eating_food_increases_score_and_length() {
    // Initial snake starts at (WIDTH / 4, HEIGHT / 2) = (10, 10) facing RIGHT.
    // The constructor calls spawnFood(), which calls getRandom for x and y.
    // We configure StubRandom to place the initial food at (11, 10), directly in front of the head.
    // Subsequent calls (e.g. respawning food after eating) place food safely at (25, 10).
    std::vector<int> coords = {11, 10, 25, 10, 30, 15};
    StubRandom stubRng(coords);

    Game game(&stubRng);

    assert(game.getScore() == 0);
    assert(game.getSnakeLength() == 1);

    // First update: snake moves from (10, 10) to (11, 10) and eats the food
    game.update();

    assert(game.getScore() == 10);

    // Second update: snake grows by 1 segment as setGrow(true, 1) resolves
    game.update();
    assert(game.getSnakeLength() == 2);

    std::cout << "[PASS] Rule 1: Eating food increases score by 10 and snake length by 1.\n";
}

// Test for Rule 3: Direct 180-degree reversal is prohibited
void test_rule3_direction_reversal_prevented() {
    Snake snake(10, 10);
    assert(snake.getHead().first == 10 && snake.getHead().second == 10);

    // Attempt to reverse 180 degrees directly into LEFT while traveling RIGHT
    snake.changeDirection(LEFT);
    snake.move();

    // Reversal should be ignored and snake moves forward to (11, 10)
    assert(snake.getHead().first == 11 && snake.getHead().second == 10);

    std::cout << "[PASS] Rule 3: Direction reversal prevented.\n";
}

// Test for Rule 4: Moving into outer wall causes Game Over
void test_rule4_wall_collision_causes_game_over() {
    Game game;
    assert(!game.isGameOver());

    // Head starts at x = 10 moving right. Moving 31 times reaches x = 41 >= WIDTH (40).
    for (int i = 0; i < 31; ++i) {
        if (!game.isGameOver()) {
            game.update();
        }
    }

    assert(game.isGameOver());
    std::cout << "[PASS] Rule 4: Boundary wall collision causes game over.\n";
}

int main() {
    std::cout << "Running SnakeByte Lab 4 Test Suite...\n";
    test_rule1_eating_food_increases_score_and_length();
    test_rule3_direction_reversal_prevented();
    test_rule4_wall_collision_causes_game_over();
    std::cout << "All tests passed successfully!\n";
    return 0;
}
