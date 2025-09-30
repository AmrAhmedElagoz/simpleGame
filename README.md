# simpleGame

A lightweight project using SFML and ImGui-SFML.


## Installation

1. Clone the repository:
```bash
   git clone https://github.com/AmrAhmedElagoz/simpleGame
```
2. Initialize submodules:
```bash
   git submodule update --init --recursive
```
3. Set the versions:
```bash
   ./scripts/set_version.sh
```

## Building

### **Option 1**: Build with dependencies (SFML + ImGui-SFML)
Build everything, including external dependencies:
```bash
   ./scripts/buildme.sh externals
```

### **Option 2**: Recommended – Build once and reuse dependencies
Build SFML and ImGui-SFML only once:

```bash
   ./scripts/buildsfml.sh
   ./scripts/buildimgui.sh
```

Then build only the project source files in src/:

```bash
   ./scripts/buildme.sh
```

## Project Structure

```bash
simpleGame/
├── assets/ 
├── build/ 
├── docs/ 
├── src/ 
│ └── main.cpp
├── include/ 
├── extern/ 
│ ├── SFML
│ ├── imgui
│ └── imgui-sfml
├── scripts/ 
│ ├── buildimgui.sh
│ ├── buildme.sh
│ ├── buildsfml.sh
│ └── set_versions.sh
├── .gitignore
├── .gitmodules
├── CMakeLists.txt
└── README.md
```