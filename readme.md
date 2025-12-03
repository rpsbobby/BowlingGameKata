# 🎳 Bowling Game Engine – Modern C++20, TDD, and Full Test Suite

![Build](https://github.com/rpsbobby/BowlingGameKata/actions/workflows/ci.yml/badge.svg)
![Clang-Format](https://img.shields.io/badge/format-clangformat-success)

---


A complete and fully-tested **Bowling scoring engine** implemented in idiomatic **C++20** using a strict **Test-Driven
Development** workflow.

This project goes beyond the classic kata: it models bowling as a small domain with **Frames**, **Bonuses**, and a *
*FrameCounter** that enforces all game rules with strong types and explicit error handling.

> **Highlights**
>
> * 70+ GoogleTest tests (including parameterized and fuzz tests)
> * Strong domain model with strict validation
> * Deterministic scoring with full rules enforcement
> * Modern C++20 patterns (value semantics, RAII, clean APIs)
> * CMake + GoogleTest project structure

---

## 🚀 Features

### ✔ Complete Bowling Rule Engine

Implements all official scoring rules:

* 10 frames per game
* Strike → next **two** rolls as bonus
* Spare → next **one** roll as bonus
* 10th frame may include 1–2 bonus rolls
* Impossible states are rejected

### ✔ Strong Domain Model

| Class          | Responsibility                                                      |
|----------------|---------------------------------------------------------------------|
| `Frame`        | Represents a single frame, validates rolls, identifies strike/spare |
| `Bonus`        | Enforces valid bonus rules for final frame                          |
| `FrameCounter` | Core engine: scoring, bonus handling, game completeness             |

### ✔ Explicit Error Types

* `InvalidRollError`
* `InvalidBonusError`
* `TooManyFramesError`
* `IncompleteGameError`

No silent failures — invalid states are impossible.

### ✔ Comprehensive Test Suite

Includes:

* Unit tests for each component
* Parameterized tests
* Completeness logic tests
* Bonus rules tests
* Full scoring tests
* **Fuzz tests** generating random valid/invalid games

---

## 📁 Project Structure

```
project_root/
│── CMakeLists.txt
│── src/
│    ├── Frame.hpp / Frame.cpp
│    ├── bonus.hpp / bonus.cpp
│    ├── frame_counter.hpp / frame_counter.cpp
│    ├── errors.hpp
│
│── test/
│    ├── test_frame.cpp
│    ├── test_frame_invalid.cpp
│    ├── test_frame_spare.cpp
│    ├── test_bonus_ctor.cpp
│    ├── test_bonus.cpp
│    ├── test_frame_counter.cpp
│    ├── test_frame_counter_bonus.cpp
│    ├── test_frame_counter_completeness.cpp
│    ├── test_frame_counter_completeness_bonus.cpp
│    ├── test_frame_counter_scoring.cpp
│    ├── test_frame_counter_scoring_freestanding.cpp
│    └── test_fuzz_random_games.cpp
```

---

## 🛠️ Building

```
mkdir build && cd build
cmake ..
make -j
```

## ▶️ Running Tests

```
ctest --verbose
```

or:

```
./bowling_tests
```

---

## 🧠 Key Design Decisions

### 1️⃣ No Invalid State Can Exist

Constructors validate input immediately — the domain model forbids impossible bowling states.

### 2️⃣ Value Semantics

`Frame` and `Bonus` are immutable, self-contained, easy to reason about.

### 3️⃣ Transparent Scoring

Scoring is deterministic:

```
rolls = flatten all rolls
for each frame:
    score += strike/spare/open logic
```

### 4️⃣ Explicit Completeness Rules

`get_score()` throws if the game is not complete.

### 5️⃣ Clean, Maintainable Code

No mutation during scoring, no hidden dependencies.

---

## 🧪 Example Fuzz Test

```
TEST(FuzzGames, random_valid_sequences_must_not_throw) {
    for (int i = 0; i < 5000; ++i) {
        FrameCounter fc;
        auto frames = random_valid_game();
        for (auto& f : frames.base_frames)
            ASSERT_NO_THROW(fc.add_frame(f));

        if (frames.bonus)
            ASSERT_NO_THROW(fc.add_bonus(*frames.bonus));

        ASSERT_NO_THROW(fc.get_score());
    }
}
```

---

## 📈 What This Project Demonstrates

Perfect for portfolio reviewers:

### 💎 Modern C++20 Design

* Value semantics
* Strong invariants
* Clean separation of responsibilities

### 🧪 Professional Testing Practices

* Parameterized tests
* Boundary testing
* Exception testing
* Fuzzing

### ⚙️ Tooling Mastery

* Modern CMake
* GoogleTest integration
* Organized project layout

---

## 🎯 Future Enhancements

* CLI scoring tool
* JSON input/output
* Scoreboard rendering
* Integration tests for full game simulations

---

## 📜 License

MIT

---

If you want, I can also prepare:

* UML diagrams
* A GitHub banner
* A CI workflow (GitHub Actions)
* Badges (C++20 / tests / CMake)

Just tell me: **“add diagrams”**, **“add CI”**, or **“add badges”**!
