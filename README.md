🌀 Sonic-Style 2D Platformer

A fast-paced 2D platformer inspired by Sonic the Hedgehog, developed using C++ and SFML 2.5.1. This project is a personal learning experience in game development, focusing on smooth character movement, momentum-based physics, and retro-style visuals.
🎮 Features

    Fast and smooth character movement

    Momentum-based physics (like running and jumping)

    Basic enemy interaction and collision detection

    Tile-based level system

    Ring collection system
    

🧰 Built With

    C++17

    SFML 2.5.1 – Simple and Fast Multimedia Library for handling graphics, audio, and input

    Tiled Map Editor – For designing tile-based levels

    Custom physics, animation, and input logic

🚀 Getting Started
Prerequisites

Make sure you have the following installed:

    C++ Compiler (e.g., g++, MSVC)

    SFML 2.5.1 (correctly installed and linked)

    CMake (optional, for easier builds)

    Tiled (if you want to edit or create levels)

Clone the Repository

git clone https://github.com/yourusername/sonic-sfml-game.git
cd sonic-sfml-game

Build and Run (Manual)

    Ensure SFML 2.5.1 is installed and set up correctly (environment variables or project settings).

    Compile with g++ (adjust paths as needed):

g++ -std=c++17 src/*.cpp -o SonicGame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./SonicGame

    Note: On Windows, make sure SFML DLLs are in the same folder as the compiled .exe.

Build with CMake (Recommended)

mkdir build
cd build
cmake ..
make
./SonicGame

📸 Screenshots

Coming soon...
❗ Known Issues

    Collision detection is still being refined

    Some animations may appear choppy


🤝 Contributing

Contributions, issues, and feature requests are welcome! Feel free to fork the repo and submit a pull request.
📜 License

This project is licensed under the MIT License — see the LICENSE file for details.
✨ Acknowledgments

    Thanks to the SFML community for documentation and support

    Sound and sprite assets are either custom-made or from open-source repositories (credited where due)

    Inspired by Sonic the Hedgehog classic games
