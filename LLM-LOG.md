# LLM-LOG.md

## 1. Setup

| | |
|---|---|
| Model(s) | Claude Sonnet 5 |
| Tool / harness | Claude Code |
| IDE / editor | VS Code |
| Did you paste this assignment document into it? | y — pasted only the Part A requirements list, not Parts B–E |

## 2. The session

> List every prompt you sent, numbered and in order. For each one, include only
> the relevant part of the reply (the code it produced), not the whole essay.

### Prompt 1
```
You are a software engineer and very good at prompt engineering, I want you to go through the following changes needs to be made on existing project:
Implement exactly this, and nothing more:

A second snake, controlled by W A S D. Player 1 keeps whatever controls the game already uses.
Both snakes eat the same fruit. Whoever reaches it first grows.
Each player has their own score, both visible during play.
The game ends when either snake hits a wall, itself, or the other snake. Announce which player lost.
Do not do anything else. No new menus, no colours, no renaming, no tidying up code you dislike, no reformatting. Every extra edit makes your measurement incomparable to the other 41 groups, and the comparison is the assignment.

If you think the code needs restructuring before a second snake is possible, that is a finding — write it in Part D. Do not act on it.

Give me a prompt which tells the coding agent to make the mentioned changes.
```
**Relevant reply / code produced:**
```
Prompt to give your coding agent

Paste this into Claude Code / Cursor / Copilot agent mode, run from inside the SnakeByte folder on the feat/multiplayer branch:

You are editing a C++ console Snake game (main.cpp, game.h, input_handler.h,
screen.h, implementation.cpp). Implement EXACTLY this, and nothing more:

1. Add a second snake controlled by W/A/S/D. Player 1 keeps whatever controls
   the game already uses (arrow keys).
2. Both snakes eat the same fruit. Whichever snake reaches it first grows;
   the other snake is unaffected until the next fruit spawns.
3. Each player has their own score, and both scores are visible on screen
   during play at the same time.
4. The game ends when EITHER snake hits a wall, itself, OR the other snake.
   When the game ends, announce clearly which player lost (Player 1 or
   Player 2), or if both collided simultaneously, say so.

STRICT SCOPE RULES — follow these exactly:
- Do NOT add new menus, colors, renaming, or unrelated refactors.
- Do NOT reformat files, change indentation style, or "clean up" code you
  think is messy, even if it looks bad.
- Do NOT touch the special food, poison food, obstacle, or shield systems
  unless a function there literally cannot work with two snakes without a
  one-line change (e.g. it hardcodes references to a single global snake).
  If you think the codebase needs deeper restructuring to support two
  snakes properly, STOP and tell me instead of doing it — don't act on it.
- Preserve existing whitespace/line endings in any function you don't
  actually change. I need `git diff --stat` to reflect only real changes.

Before you start, read main.cpp, game.h, input_handler.h, screen.h, and
implementation.cpp in full so you understand where snake position, input,
rendering, and collision logic live.

After implementing:
1. Build it (g++ -std=c++17 main.cpp implementation.cpp -o snake_game) and
   fix any compile errors introduced by your change only.
2. Run `git diff --stat -w` and tell me if any file shows a suspiciously
   large number of changed lines relative to what you touched — that
   signals unwanted reformatting.
3. List, by name, every function you modified, and for each one say whether
   it is snake-movement-related or whether it's something incidental
   (rendering, scoring, input, file I/O) that you were forced into because
   it assumed a single snake.
4. Tell me explicitly: was "there is exactly one snake" written down in one
   single place in this codebase, or was that assumption scattered across
   multiple functions? Give specifics.

Do not commit or push anything yourself — I will review and commit manually.

After it finishes, review its diff yourself before committing — the assignment explicitly penalizes noisy diffs, and only you can judge whether the agent quietly reformatted something.
```

### Prompt 2 (if applicable)
```
You are editing a C++ console Snake game (main.cpp, game.h, input_handler.h,
screen.h, implementation.cpp). Implement EXACTLY this, and nothing more:

1. Add a second snake controlled by W/A/S/D. Player 1 keeps whatever controls
   the game already uses (arrow keys).
2. Both snakes eat the same fruit. Whichever snake reaches it first grows;
   the other snake is unaffected until the next fruit spawns.
3. Each player has their own score, and both scores are visible on screen
   during play at the same time.
4. The game ends when EITHER snake hits a wall, itself, OR the other snake.
   When the game ends, announce clearly which player lost (Player 1 or
   Player 2), or if both collided simultaneously, say so.

STRICT SCOPE RULES — follow these exactly:
- Do NOT add new menus, colors, renaming, or unrelated refactors.
- Do NOT reformat files, change indentation style, or "clean up" code you
  think is messy, even if it looks bad.
- Do NOT touch the special food, poison food, obstacle, or shield systems
  unless a function there literally cannot work with two snakes without a
  one-line change (e.g. it hardcodes references to a single global snake).
  If you think the codebase needs deeper restructuring to support two
  snakes properly, STOP and tell me instead of doing it — don't act on it.
- Preserve existing whitespace/line endings in any function you don't
  actually change. I need `git diff --stat` to reflect only real changes.

Before you start, read main.cpp, game.h, input_handler.h, screen.h, and
implementation.cpp in full so you understand where snake position, input,
rendering, and collision logic live.

After implementing:
1. Build it (g++ -std=c++17 main.cpp implementation.cpp -o snake_game) and
   fix any compile errors introduced by your change only.
2. Run `git diff --stat -w` and tell me if any file shows a suspiciously
   large number of changed lines relative to what you touched — that
   signals unwanted reformatting.
3. List, by name, every function you modified, and for each one say whether
   it is snake-movement-related or whether it's something incidental
   (rendering, scoring, input, file I/O) that you were forced into because
   it assumed a single snake.
4. Tell me explicitly: was "there is exactly one snake" written down in one
   single place in this codebase, or was that assumption scattered across
   multiple functions? Give specifics.

Do not commit or push anything yourself — I will review and commit manually.
```

## 3. Which attempt finally worked, and what was wrong with earlier ones

<e.g. "Prompt 1 compiled but both snakes shared one score variable due to a
static instead of per-instance member. Prompt 2 fixed this by...">

## 4. Total number of prompts to get working code

**N = 2**

## 5. What code was given to the model

- [ ] Whole file