#!/bin/bash

# Function to kill existing processes
kill_existing_processes() {
    echo "Checking for existing processes..."
    
    # Kill any process running on port 8080 (backend)
    BACKEND_PID=$(lsof -ti:8080)
    if [ ! -z "$BACKEND_PID" ]; then
        echo "Killing existing backend process..."
        kill -9 $BACKEND_PID
    fi
    
    # Kill any process running on port 3000 (frontend)
    FRONTEND_PID=$(lsof -ti:3000)
    if [ ! -z "$FRONTEND_PID" ]; then
        echo "Killing existing frontend process..."
        kill -9 $FRONTEND_PID
    fi
}

# Kill existing processes
kill_existing_processes

echo "Compiling and starting backend..."

# using system paths for macOS with homebrew
BACKEND_DIR="./backend/src"
BACKEND_OUTPUT="arb_backend"
INCLUDE_PATH="/opt/homebrew/include"
LIBRARY_PATH="/opt/homebrew/lib"
LIBRARIES="-lcurl -lboost_system -lssl -lcrypto -lcpprest -ljsoncpp"

# Navigate to backend directory and compile
cd "$BACKEND_DIR"

g++ -std=c++17 -o "$BACKEND_OUTPUT" main.cpp ApiClient.cpp ArbitrageDetector.cpp $LIBRARIES -I$INCLUDE_PATH -L$LIBRARY_PATH

if [ $? -eq 0 ]; then
    echo "Backend compilation successful. Starting backend..."
    ./"$BACKEND_OUTPUT" &
    BACKEND_PID=$!
    echo "Backend started with PID: $BACKEND_PID"
else
    echo "Backend compilation failed."
    exit 1
fi

# Navigate back to project root
cd ../../

echo "Starting frontend..."
cd React

# Check if node_modules exists, if not run npm install
if [ ! -d "node_modules" ]; then
    echo "Installing frontend dependencies..."
    npm install
fi

# Start the frontend
echo "Starting React development server..."
npm start &
FRONTEND_PID=$!
echo "Frontend started with PID: $FRONTEND_PID"

# Wait for both processes
wait $BACKEND_PID $FRONTEND_PID