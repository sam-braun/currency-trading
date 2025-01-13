# Arbitrage Opportunity Detector

## Overview

Triangular arbitrage is a strategy that takes advantage of exchange rate discrepancies between three currencies to generate a risk-free profit. This Arbitrage Opportunity Detector analyzes exchange rates to identify potential arbitrage opportunities across different currencies. It includes a backend built in C++ and a frontend built with React.

## Prerequisites

### macOS

```bash
# Install Homebrew if you haven't already
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install required packages
brew install boost cpprestsdk jsoncpp openssl curl
brew install node  # For React frontend
```

## Installation

1. Clone the repository:

```bash
git clone https://github.com/sam-braun/currency-trading.git
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
