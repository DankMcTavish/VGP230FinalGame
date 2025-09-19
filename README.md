# VGP230 Final Game

Welcome to **VGP230FinalGame** – a project developed as the final assignment for the VGP230 course! This game was built using [raylib](https://www.raylib.com/), a simple and easy-to-use C/C++ library to enjoy videogames programming.

## 🕹️ Game Overview

This project is a demonstration of concepts and skills learned throughout VGP230, including graphics, input handling, collision detection, and basic gameplay programming. Challenge yourself to achieve a high score and explore the code to see how classic gameplay mechanics are implemented from scratch!

## ✨ Features

- Built with **raylib** in C/C++
- Responsive player controls
- Score tracking and win/lose conditions
- Clean, readable code

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

- **Left/Right arrow keys or A/D** – Move the player
- **Spacebar** – Action (jump, shoot, etc. depending on gameplay)
- **Esc** – Quit the game
- **R** - Restart the game

## 📸 Screenshots
![GamePlay2](https://github.com/user-attachments/assets/55a346c2-569b-4fbb-ab83-fe20078952f2)


## 📦 Credits & Assets


- Programming: [DankMcTavish](https://github.com/DankMcTavish)
- Libraries: [raylib](https://www.raylib.com/)
- Special thanks to [Amir - Teacher]

## 📝 License

This project is for educational purposes. See [LICENSE](LICENSE) for more information.

## 🤝 Contributing

Pull requests are welcome! For major changes, please open an issue to discuss what you would like to change.

## Next steps

The next things that can be worked on and added
1. Collision logic. Stop player from coming up from below the platforms
2. Textures
3. High score system
4. Menu. View high scores, change difficulty and screen size
5. Adjust platform creation location logic
6. Adjust camera

---

Made with ❤️ for VGP230 by [DankMcTavish](https://github.com/DankMcTavish)



![GameOver2](https://github.com/user-attachments/assets/312d8221-2bfb-4299-b973-37d31574272e)
