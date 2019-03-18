# Installation guide

RacingWorld is divided into two large parts:
 *   ServerSide(Java) - it is only represents two servers(game and for authorization) for Linux or Windows. They come already
 assembled, but if you want to build them manually, you can use the script <i>Scripts/BuildServerSide.sh</i> or
 <i>Scripts/BuildServerSide.bat</i> depending on your OS.
 *   ClientSide(C/C++) - it is the game, written only for Windows, using the <i>Visual Studio 2017</i> compiler.

## Building of the RacingWorld

### What do you need to build client side

Firs of all you need install on your computer necessary programs:

*   <a href="https://cmake.org/download/">CMake</a>
*   <a href="https://visualstudio.microsoft.com/en/?rr=https%3A%2F%2Fyandex.ru%2F">Visual Studio 2017</a>

### How to build client side

Clone a copy of the main RacingWorld git repository by running:

    git clone https://github.com/<your-username>/RacingWorld.git

Run script for building of the client side:

    cd Scripts
    BuildClientSide.bat

If you want build client side manually, the use the following:

    cd ClientSide
    mkdir Build
    cd Build
    cmake -G "Visual Studio 15 2017 ..
    // Launch generated project in Visual Studio 2017

## Launch of the RacingWorld

Before you start the game, you must start the game server. You can use the
script <i>Scripts/RunGameServer.sh</i> or <i>Scripts/RunGameServer.bat</i> depending on your OS.
After it can you run game and try to play in our game.

> At the moment there is no need to start the authorization server to start the game.

---

If you have any questions, please contact: vladimirbalun@yandex.ru
