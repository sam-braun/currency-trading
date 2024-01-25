# Arbitrage Opportunity Detector

## Overview

This project is an Arbitrage Opportunity Detector that analyzes exchange rates to identify potential arbitrage opportunities across different currencies. It includes a backend implemented in C++ using the C++ REST SDK (cpprest) for handling HTTP requests and a frontend built with React.

## Project Structure

The project is divided into several key components:

- `http_listener`: Handles HTTP requests and responses.
- `ApiClient`: Fetches exchange rates from an external API.
- `ArbitrageDetector`: Analyzes exchange rates to detect arbitrage opportunities.
- `React Frontend`: A user interface for interacting with the backend.

## Backend

### Requirements and Dependencies

- C++17 or later
- C++ REST SDK (cpprest)
- nlohmann/json for JSON parsing

### Exchange Rate API

You will need to create your own API access token. Here are the instructions:

1. Visit https://exchangeratesapi.io.
2. Create an account.
3. Navigate to your dashboard and copy your API access token.
4. Paste the access token in the access_token fields in `main.cpp`.

### Key Functions

- `handleGetRates`: Fetches exchange rates.
- `handleGetAvailableCurrencies`: Provides a list of available currencies.
- `handleFindArbitrageWithSelectedCurrencies`: Finds arbitrage opportunities for selected currencies.

## Frontend

### Dependencies

- React
- Axios for HTTP requests

### Components

- `CurrencyInputForm`: Allows users to select currencies and initiate searches for arbitrage opportunities.
- `OpportunitiesList`: Displays the list of detected arbitrage opportunities.
- `MenuBar`: Provides additional user interface features.
- `InstructionModal`: Displays instructions for using the application.

### Setup

1. Install C++ REST SDK and other required libraries (using a package manager like vcpkg is recommended).
2. Install Node.js and npm.
3. Customize `start.sh` for your machine's package locations.

## Usage

1. Run `bash start.sh` to compile the backend, and lauch the backend and React app.
2. Start the backend server.
3. Open the frontend application in a web browser.
4. Select a base currency and additional currencies to calculate arbitrage.
5. Click 'Find Arbitrage Opportunities' to view the results.
