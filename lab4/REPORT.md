# Lab 4 — Group A

| | |
|---|---|
| Repository | https://github.com/Dazzling-Darshan/SnakeByte |
| Base tag | `lab4-base` at commit `17bc256` (`17bc256926a95aa647314649331fe78d4b52c41b`) |
| Pull request | https://github.com/Dazzling-Darshan/SnakeByte/pulls |

---

## 1. Five rules — [5]

Written before opening the source. Behaviour, with an observable outcome.

| # | Rule |
|---|---|
| 1 | Eating a normal food item increases the score by 10 and causes the snake to grow by 1 segment on subsequent movement. |
| 2 | Eating a poison food item decreases the score by 30 (minimum score capped at 0) and shrinks the snake body by up to 3 segments. |
| 3 | The snake cannot reverse directly 180 degrees into the opposite direction (e.g. attempting to switch to `LEFT` while traveling `RIGHT` is ignored). |
| 4 | Moving the snake's head into any outer boundary wall ends the game (`gameOver` becomes `true`). |
| 5 | Moving the snake's head into any cell occupied by its own body ends the game (`gameOver` becomes `true`) unless a shield power-up is active. |

---

## 2. What you could test, and what stopped you — [10]

No source changes in this part. Every `file:line` below is a line in `lab4-base`.

| # | Rule | Test written? | Blocking dependency (`file:line` + what it is) |
|---|---|---|---|
| 1 | Eating normal food increases score by 10 and length by 1 | No | `implementation.cpp:393` — `rand()` called inside `Game::spawnFood()` generates random non-deterministic coordinates; `game.h:58` — `score` is a private member variable with no getter accessor. |
| 2 | Eating poison food decreases score by 30 and shrinks snake by 3 | No | `implementation.cpp:455` — `rand()` called inside `Game::spawnPoisonFood()`; `implementation.cpp:927` — `foodEaten % 4 == 0` gating requirement prevents spawning poison food without eating non-deterministic food first. |
| 3 | Reversing direction directly 180 degrees is prohibited | Yes | None. Testable directly on `Snake` class via public methods `Snake::changeDirection()` and `Snake::move()` in `lab4-base`. |
| 4 | Moving into a boundary wall ends the game | Yes | None. Testable by instantiating `Game game;` and calling `game.update()` across 31 ticks to reach boundary `x >= 40`, observing `game.isGameOver() == true`. |
| 5 | Self-collision without shield ends the game | No | `implementation.cpp:963` — `InputHandler::isKeyPressed()` inside `Game::handleInput()` reads hardware keyboard with no input injection; `implementation.cpp:393` — `rand()` in `spawnFood()` prevents growing snake to length >= 4 required for self-collision. |

> **Rules testable without modifying the source: 2 / 5**

---

## 3. Coverage, and what it missed — [6]

| | |
|---|---|
| Line coverage | 28.16% (base suite) / 32.52% (with seam test) |
| Branch coverage | 21.80% (base suite) / 24.25% (with seam test) |
| Command used | `g++ --coverage -O0 -g implementation.cpp tests.cpp -o tests.exe; .\tests.exe; gcov -b tests-implementation.gcno` |

**One rule that is executed by the suite but not verified by it:**

| | |
|---|---|
| Rule | Rule 5: Self-collision check without shield ends the game. |
| Line that runs | `implementation.cpp:898` (`if (!snake.hasShield()) { for (size_t i = 1; i < snake.getBody().size(); i++) { ... } }`) |
| The assertion that is missing | The wall-collision test loop executes lines 898–900 on every tick of `game.update()`, but the test only asserts `game.isGameOver()` at the final boundary crash and never asserts whether self-collision logic correctly refrained from triggering game over prematurely. |

---

## 4. The seam — [10]

| | |
|---|---|
| Rule made testable | Eating normal food increases the score by 10 and increases snake length by 1 |
| Commit 1 (seam) | `3cc1e86` (`3cc1e867e148211c76953f4326fa66294decf774`) |
| Commit 2 (test) | `HEAD` (Commit 2 on branch `lab4`) |
| Seam kind | object |
| Enabling point | `Game::Game(IRandom* customRng = nullptr)` constructor parameter. The decision of whether to use production pseudorandom generation (`DefaultRandom`) or a deterministic test double (`StubRandom`) now lives at the call site where `Game` is instantiated. |
| What production code gave up | Production code gave up tight coupling to the global C standard library `rand()` function, strict encapsulation of `score` by adding an observer `getScore() const`, and pure stack allocation for `rng` (incurring a pointer indirection and virtual dispatch). This cost nothing to the player because the default constructor path seamlessly instantiates `DefaultRandom` delegating directly to `rand()`, preserving identical gameplay, visuals, and frame timings. |

---

## 5. The double — [4]

| | |
|---|---|
| What you passed through the seam | stub |
| The method under test | `Game::update()` (and `Game::spawnFood()`) |

Two sentences: The collaborator (`IRandom`) was asked a question (`getRandom(min, max)`) to provide deterministic coordinate values for food placement, rather than being told to perform an action. Because a stub supplies indirect inputs via return values to the system under test—which are then verified through the observable state of `Game::getScore()` rather than by verifying that a specific command occurred on the collaborator—it is classified as a stub.

---

## 6. Two smells in your own tests — [5]

| | Smell | `file:line` | One-line fix |
|---|---|---|---|
| 1 | Resource optimism | `tests.cpp:24` | Supply mock graphics/storage abstractions or instantiate tests within an isolated temporary sandbox directory containing required fixture files. |
| 2 | Assertion roulette | `tests.cpp:32` | Add failure diagnostic messages to assertions: `assert(game.getScore() == 10 && "Expected score to increase by 10 after eating food");`. |

Fixing them is optional. Finding them is not.
