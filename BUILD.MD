sudo apt install libgtest-dev

python3 -m venv conan
source conan/bin/activate
pip install conan

conan profile detect
mkdir build && cd build
conan install .. -of=. --build missing 

cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .

ctest --rerun-failed --output-on-failure
./BlockHandler block_device.dat --create
./BlockHandler block_device.dat
