# Super Mario Refactoring Plan

## Background & Motivation
The current Super Mario clone, built upon the "PTSD" 2D engine, attempts to mimic a "Windows Forms" approach using Object-Oriented Programming (OOP). However, this has resulted in:
1. **Deep Inheritance Anti-pattern**: `Mario` -> `Character` -> `Object` -> `Util::GameObject`. This causes rigid structures and bloated classes (e.g., `Mario` managing its own state, rendering paths, and physics).
2. **Performance Bottlenecks**: `FormManager` uses type-specific vectors (`TextObjectPtrVec`, `ButtonPtrVec`, etc.) and performs linear searches (`std::find_if`) wrapped in massive `if constexpr` blocks.
3. **Hardcoded Resources**: Hundreds of image paths are hardcoded in static maps inside classes.
4. **Outdated Concurrency**: `main.cpp` uses raw `std::thread` with manual joining and relies on global variables for window dimensions.

## Scope & Impact
This refactoring will be comprehensive, modernizing the codebase to idiomatic modern C++ (C++17/20) while preserving the current C++ version. The changes will significantly impact the `Object` hierarchy, `FormManager`, and resource loading logic. The original behavior and PTSD engine integration will remain intact.

## Proposed Solution

### 1. ECS / Component-Based Architecture (組合優於繼承)
- **Entity**: Refactor `Object` to act as a container for components rather than heavily relying on virtual polymorphism.
- **Components**: Introduce modular components such as `PhysicsComponent` (gravity, collision logic), `RenderComponent` (managing `Util::Image`), `StateComponent` (handling Mario's Invincible/Fiery/Super states), and `InputComponent`.
- **Decoupling**: Remove the necessity for interfaces like `ICollisionable` and `IMovable`, determining behavior by the presence of specific components.

### 2. Centralized AssetManager
- **Asset Caching**: Create an `AssetManager` class to load, store, and share `std::shared_ptr<Util::Image>` and audio files.
- **Configuration**: Extract all hardcoded string paths into a `Constants.hpp` or external configuration, drastically cleaning up the `Mario.hpp` header.

### 3. FormManager Modernization
- **Typo Fix**: Rename `FormManager` to `FormManager`.
- **O(1) Lookups**: Replace the fragmented type-specific vectors inside `FormAndObject` with a unified `std::unordered_map<size_t, std::shared_ptr<Object>>` to look up objects instantly by their ID.
- **Modern C++ Algorithms**: Replace manual `std::for_each` and lambdas with clean C++20 `std::ranges::views` for filtering and updating objects.

### 4. main.cpp & Global State Cleanup
- **Concurrency**: Replace `std::thread` with `std::jthread` to handle automatic joining during image resizing operations.
- **Encapsulation**: Remove global variables (`WINDOW_WIDTH`, `WINDOW_HEIGHT`) by encapsulating them into an `EngineConfig` or `GameContext` singleton.

## Phased Implementation Plan

### Phase 1: Setup & Asset Management
1. Fix naming conventions (e.g., `FormManager` -> `FormManager`).
2. Create `Constants.hpp` for file paths and magic numbers.
3. Implement `AssetManager`.
4. Refactor `main.cpp` to use `std::jthread` and eliminate global state.

### Phase 2: FormManager Optimization
1. Refactor `FormAndObject` to use `std::unordered_map<size_t, std::shared_ptr<Object>>`.
2. Rewrite `GetFormObject` to remove `if constexpr` linear search templates.
3. Update `UpdateForm` to utilize C++20 `std::ranges`.

### Phase 3: Component System Introduction
1. Define the `Component` base class and standard components (`TransformComponent`, `RenderComponent`, `PhysicsComponent`).
2. Refactor the `Object` base class to attach and retrieve components.

### Phase 4: Character & Mario Refactoring
1. Break down `Mario.hpp` and `Character.hpp`.
2. Migrate Mario's giant state map to a `StateMachineComponent` mapping state to animations loaded via `AssetManager`.
3. Shift collision and movement logic into `PhysicsComponent`.
4. Per user request: The agent will output this exact refactoring plan to the root directory `D:\program\C++\Super_Mario\refactoring_plan.md`.

## Verification & Testing
- Validate that the PTSD engine still renders correctly.
- Verify Mario's physics (jump height, acceleration, collision with blocks) remain identical to the original behavior.
- Ensure the `ImageResizer` step executes without memory leaks or race conditions.
