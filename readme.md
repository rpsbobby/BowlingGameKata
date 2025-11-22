# 🎳 Bowling Game TDD Kata (C++)

This repository implements the classic **Bowling Game TDD Kata** in modern **C++** using a strict test-driven workflow.
The goal is to practice incremental design, clean abstractions, and disciplined testing.

---

## 📌 Overview

The kata implements a scoring engine for a standard 10-frame bowling game:

* A game consists of **20 rolls** (or fewer with strikes).
* A spare adds the next roll as a bonus.
* A strike adds the next **two** rolls as a bonus.
* The 10th frame may contain extra rolls.

The challenge is **not the algorithm**, but the discipline of:

* Writing only the minimal code needed to pass each test.
* Adding complexity *only* when a new failing test requires it.
* Keeping code small and expressive.

---

## 🧪 Testing Setup (Catch2)

This project uses **Catch2** for unit testing.

### Example test

```cpp
TEST_CASE("Gutter game scores 0") {
    Game g;
    for (int i = 0; i < 20; ++i) g.roll(0);
    REQUIRE(g.score() == 0);
}
```

---

## 📁 Project Structure

```
/ (root)
│── CMakeLists.txt
│── src/
│    └── Game.hpp
│    └── Game.cpp
│── tests/
│    └── test_game.cpp
│── build/ (ignored)
```

---

## 🛠️ Building

```bash
mkdir build && cd build
cmake ..
make
```

---

## ▶️ Running Tests

```bash
./tests/test_game
```

---

## 💡 TDD Steps (Recommended)

Follow these in strict order:

### 1. Gutter Game

```
roll(0) × 20 → score = 0
```

### 2. All Ones

```
roll(1) × 20 → score = 20
```

### 3. Single Spare

```
5,5,3 → bonus = 3
```

### 4. Single Strike

```
10, 3, 4 → bonus = 3+4
```

### 5. Perfect Game

```
12 × 10 → score = 300
```

Each step adds **one test**, run → watch fail → implement smallest fix.

---

## 🎯 Goals

* Learn disciplined incremental design.
* Practice clean, minimal C++.
* Reinforce STL usage, value semantics, and RAII.
* Keep Game class focused and tiny.

---

## 🙌 Notes

This kata is intentionally simple.
Treat it like sharpening a knife — you get better at everything else by practicing precision here.
