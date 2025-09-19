# VGP230 Final Game

Welcome to **VGP230FinalGame** – a project developed as the final assignment for the VGP230 course! This game was built using [raylib](https://www.raylib.com/), a simple and easy-to-use C/C++ library to enjoy videogames programming.

## 🕹️ Game Overview

This project is a demonstration of concepts and skills learned throughout VGP230, including graphics, input handling, collision detection, and basic gameplay programming. Challenge yourself to achieve a high score and explore the code to see how classic gameplay mechanics are implemented from scratch!

## ✨ Features

- Built with **raylib** in C/C++
- Custom graphics and animations
- Responsive player controls
- Score tracking and win/lose conditions
- Sound effects and background music
- Clean, readable code with comments

## 🛠️ Built With

- **raylib** (recommended version: 4.x)
- **C** (or C++ if applicable)
- [GCC](https://gcc.gnu.org/), [Clang](https://clang.llvm.org/), or [MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/) (for compiling)
- [CMake](https://cmake.org/) (optional, for build automation)

## 🚀 Getting Started

### Prerequisites

- [raylib](https://www.raylib.com/) installed on your system
- C compiler (GCC, Clang, or MSVC)
- Git (to clone the repository)

### Installation

1. **Clone this repository**
    ```bash
    git clone https://github.com/DankMcTavish/VGP230FinalGame.git
    cd VGP230FinalGame
    ```
2. **Build the game**
    - If using a Makefile:
        ```bash
        make
        ```
    - If using CMake:
        ```bash
        mkdir build
        cd build
        cmake ..
        make
        ```
    - Or compile directly (example for main.c):
        ```bash
        gcc main.c -o VGP230FinalGame -lraylib -lm -lpthread -ldl -lrt -lX11
        ```

3. **Run the game**
    ```bash
    ./VGP230FinalGame
    ```

## 🎮 How to Play

- **Arrow keys / WASD** – Move the player
- **Spacebar / Z / X** – Action (jump, shoot, etc. depending on gameplay)
- **Esc** – Quit the game

*(Update controls as per your specific gameplay!)*

## 📸 Screenshots

*(Add screenshots of your game here!)*

## 📦 Credits & Assets

- Programming: [DankMcTavish](https://github.com/DankMcTavish)
- Art & Audio: [List your sources or note if you created them yourself]
- Libraries: [raylib](https://www.raylib.com/)
- Special thanks to [instructors, classmates, contributors, etc.]

## 📝 License

This project is for educational purposes. See [LICENSE](LICENSE) for more information.

## 🤝 Contributing

Pull requests are welcome! For major changes, please open an issue to discuss what you would like to change.

---

Made with ❤️ for VGP230 by [DankMcTavish](https://github.com/DankMcTavish)
