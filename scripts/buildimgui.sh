cd extern/imgui-sfml
rm -rf build && mkdir build && cd build

INSTALL_PREFIX="$(pwd)/../../SFML/build/install"
IMGUI_PATH="$(pwd)/../../imgui"

echo "Using SFML_DIR = ${INSTALL_PREFIX}/lib/cmake/SFML"
echo "Using IMGUI_DIR = ${IMGUI_PATH}"

cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=ON \
  -DIMGUI_DIR="${IMGUI_PATH}" \
  -DSFML_DIR="${INSTALL_PREFIX}/lib/cmake/SFML"

cmake --build . --config Release
