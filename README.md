# Arbitrage Opportunity Detector

## Overview

Triangular arbitrage is a strategy that takes advantage of exchange rate discrepancies between three currencies to generate a risk-free profit. This Arbitrage Opportunity Detector analyzes exchange rates to identify potential arbitrage opportunities across different currencies. It includes a backend implemented in C++ and a frontend built with React.

## Prerequisites

### macOS

```bash
# Install Homebrew if you haven't already
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install required packages
brew install boost cpprestsdk jsoncpp openssl curl
brew install node  # For React frontend
```

### Linux (Ubuntu/Debian)

```bash
# Install required packages
sudo apt-get update
sudo apt-get install -y \
    g++ \
    libboost-all-dev \
    libcpprest-dev \
    libjsoncpp-dev \
    libssl-dev \
    libcurl4-openssl-dev \
    curl

# Install Node.js and npm
curl -fsSL https://deb.nodesource.com/setup_20.x | sudo -E bash -
sudo apt-get install -y nodejs
```

### Windows

1. Install [MSYS2](https://www.msys2.org/) which provides a Unix-like environment
2. Open MSYS2 and run:

```bash
pacman -Syu
pacman -S \
    mingw-w64-x86_64-gcc \
    mingw-w64-x86_64-boost \
    mingw-w64-x86_64-cpprest \
    mingw-w64-x86_64-jsoncpp \
    mingw-w64-x86_64-openssl \
    mingw-w64-x86_64-curl
```

3. Install [Node.js](https://nodejs.org/) for Windows

## Installation

1. Clone the repository:

```bash
git clone [https://github.com/sam-braun/currency-trading.git]
cd currency-trading
```

2. Install React dependencies:

```bash
cd React
npm install
cd ..
```

3. Create your API key:
Paste your API key into `config.json`. You can get your API key from [APILayer's Exchange Rates Data API](https://apilayer.com/marketplace/exchangerates_data-api?utm_source=apilayermarketplace&utm_medium=featured).

## Running the Application

The entire application (both backend and frontend) can be started using a single script:

```bash
./start.sh
```

This will:

1. Compile the C++ backend
2. Start the backend server
3. Launch the React frontend

The React application should automatically open in your default web browser. If it doesn't, visit http://localhost:3000

## Stopping the Application

To stop the application:

1. Press `Ctrl + C` in the terminal to stop the React development server
2. For the backend process:
   - On macOS/Linux: Run `killall arb_backend`
   - On Windows (in MSYS2): Run `taskkill /F /IM arb_backend.exe`
