<h1 align="center"><img src="https://github.com/Livl-Corporation/livl-pacman/assets/62793491/57617b44-13eb-4680-a742-07753d40e0ce" width="224px"/><br/>  
  Livl Pacman
</h1>  
<p align="center">Livl Pac-Man is a free, open source Pacman clone written in C using SDL2 and SDL_mixer.</p>  

# Table of Contents

- [📦 Prerequisites](#-prerequisites)
    - [⚙️ Installation of SDL2 and SDL2 mixer](#-installation-of-sdl2-and-sdl2-mixer)
        - [**Linux** / **WSL**](#linux--wsl)
        - [**MacOS**](#macos)
- [🚀 Usage](#-usage)
- [🎮 How to Play](#-how-to-play)
    - [📝 Pac-Man Rules](#-pac-man-rules)
    - [⚠️ Potential sound latency issues](#-potential-sound-latency-issues)
- [🧍🏽Project team](#project-team)
- [📝 License](#-license)

# 🕹️ Gameplay

> [!NOTE]
> Here is a video from our Pacman game made from scratch ! The game was fully implemented, with different levels, music, AI for the ghost and everything !

[![Gameplay video](https://youtube.com/shorts/2im7196q84Y)](https://youtube.com/shorts/2im7196q84Y)


# 📦 Prerequisites
- `CMake`
- C compiler (gcc, clang, etc.)
- `SDL2` and `SDL2_mixer`

## ⚙️ Installation of SDL and SDL Mixer

Please find the SDL2 repository [here](https://github.com/libsdl-org/SDL) and the SDL2_mixer repository [here](https://github.com/libsdl-org/SDL_mixer).
You can also have a look to the official [SDL2 documentation](https://wiki.libsdl.org/Installation).

### **Linux** / **WSL**

- Using [apt](https://doc.ubuntu-fr.org/apt)

```bash
sudo apt-get update
sudo apt-get install -y libsdl2-dev
sudo apt-get install -y libsdl2-mixer-dev
```

### **MacOS**

- Using [homebrew](https://brew.sh/index_fr)

```bash
brew install sdl2 sdl_mixer 
```

> 💭 If you use Cocoa framework on macOS, please uncomment the line 276 to 278 in [FindSDL2.cmake](modules/FindSDL2.cmake) file to use it.


# 🚀 Usage

Run the following commands in your terminal to be able to compile and run the game :

```bash
git clone git@github.com:Livl-Corporation/livl-pacman.git
cd livl-pacman
mkdir build
cd build
cmake ..
make
./Pacman
```

# 🎮 How to Play

- ⬆️ Move Up
- ⬇️ Move Down
- ⬅️ Move Left
- ➡️ Move Right
- `P` Pause

## 📝 Pac-Man Rules

- Eat all the dots to win
- Avoid the ghosts
- Eat the big dots to eat the ghosts
- Eat the fruits to get more points
- Eat the ghosts to get more points
- You have 3 lives
- When you eat all the dots, you go to the next round

### ⚠️ Potential sound latency issues

> If you’re running this game on Windows Subsystem for Linux (WSL), you may experience some latency issues with the sounds.
This is due to the fact that WSL is an emulation layer for running Linux applications on Windows, and as such, it may not provide the same level of performance as running natively on Linux or Windows.
If you’re experiencing latency issues, you might want to restart the game one few more times, or try running the game natively on Linux or Windows to see if that improves the latency.

# **🧍🏽Project team**

<table align="center">
    <tr>
        <th><img src="https://avatars.githubusercontent.com/u/19238963?v=4?v=4?size=115" width="115"><br><strong>@FranckG28</strong></th>
        <th><img src="https://avatars.githubusercontent.com/u/62793491?v=4?size=115" width="115"><br><strong>@jvondermarck</strong></th>
    </tr>
    <tr align="center">
        <td><b>Franck Gutmann</b></td>
        <td><b>Julien Von Der Marck</b></td>
    </tr>
</table>

# 📝 License

> This project is licensed under the MIT License - see the [LICENSE.md](LICENSE) file for details. © 2023 Livl Corporation.
