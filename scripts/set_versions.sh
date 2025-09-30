set -euo pipefail

BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

SFML_DIR="$BASE_DIR/extern/SFML"
IMGUI_DIR="$BASE_DIR/extern/imgui"
IMGUI_SFML_DIR="$BASE_DIR/extern/imgui-sfml"

echo "Switching versions..."

# SFML
if [ -d "$SFML_DIR" ]; then
    echo "Checking out SFML v3.0.0..."
    cd "$SFML_DIR"
    git checkout 3.0.0
else
    echo "Directory $SFML_DIR not found!"
fi

# ImGui
if [ -d "$IMGUI_DIR" ]; then
    echo "Checking out ImGui v1.91.1..."
    cd "$IMGUI_DIR"
    git checkout v1.91.1
else
    echo "Directory $IMGUI_DIR not found!"
fi

# ImGui-SFML
if [ -d "$IMGUI_SFML_DIR" ]; then
    echo "Checking out ImGui-SFML v3.0..."
    cd "$IMGUI_SFML_DIR"
    git checkout v3.0
else
    echo "Directory $IMGUI_SFML_DIR not found!"
fi

echo "Done!"
