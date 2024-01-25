#!/bin/bash

echo "Compiling and starting backend..."

# replace following variables with appropriate values for your system:
BACKEND_DIR="./backend/src"  # Path to the backend source code directory
BACKEND_OUTPUT="arb_backend"  # Name of the compiled backend executable
INCLUDE_PATH="YOUR PATH"  # Include path for libraries
LIBRARY_PATH="YOUR PATH"  # Library path for libraries
LIBRARIES="-lcurl -lboost_system -lssl -lcrypto -lcpprest -ljsoncpp"  # Libraries to link

cd "$BACKEND_DIR"

g++ -std=c++17 -o "$BACKEND_OUTPUT" main.cpp ApiClient.cpp ArbitrageDetector.cpp $LIBRARIES -I$INCLUDE_PATH -L$LIBRARY_PATH

if [ $? -eq 0 ]; then
  echo "Backend compilation successful. Starting backend..."
  ./"$BACKEND_OUTPUT" &
else
  echo "Backend compilation failed."
  exit 1
fi

echo "Starting React app..."
cd ../../react
npm start