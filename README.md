# Classic Space Invaders

A recreation of the classic arcade game "Space Invaders" built with C++ and the `raylib` library.

---

## Getting Started

Follow these steps to get the game up and running in your local development environment.

### Prerequisites

You'll need to have the following installed on your system:

- **Visual Studio Code**: The code editor for running the project.
- **A C++ Compiler**: `g++` or `clang++` must be installed and configured.
- **The raylib library**: This project uses `raylib` for graphics and audio. The `Makefile` is configured to find `raylib` at `C:/raylib/raylib`, but you may need to adjust the path in the `Makefile` and `tasks.json` to match your installation.

### 1\. Clone the Repository

First, clone this repository to your local machine using Git.

```bash
git clone https://github.com/your-username/your-repository-name.git
cd your-repository-name
```

### 2\. Open in VS Code

Open the project folder in Visual Studio Code.

```bash
code .
```

### 3\. Run the Game

The project is configured to build and run directly from the VS Code **Run and Debug** menu.

1.  Open the **Run and Debug** view in VS Code by clicking the debug icon on the sidebar or pressing `Ctrl+Shift+D`.
2.  In the dropdown menu at the top, select the **"Run"** configuration. This configuration will compile the game in release mode and run the executable.
3.  Click the green **"Start Debugging"** button or press `F5`.

The `Makefile` will automatically compile the project, and the game window will launch.

---

## How It Works

- The `launch.json` file contains two configurations: "Debug" and "Run." These configurations tell VS Code how to build and execute the game.
- The `tasks.json` file defines the build commands, specifically **"build debug"** and **"build release,"** which use the project's `Makefile` to compile the source code.
- The `Makefile` handles the platform-specific compilation, including linking with the `raylib` library. It's set up to build a single `game.exe` executable.
