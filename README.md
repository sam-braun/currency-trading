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

- C++17 or higher
- C++ REST SDK (cpprest)
- nlohmann/json for JSON parsing

### Key Functions

- `handleGetRates`: Fetches exchange rates.
- `handleGetAvailableCurrencies`: Provides a list of available currencies.
- `handleFindArbitrage`: Finds arbitrage opportunities for a given base currency.
- `handleFindArbitrageWithSelectedCurrencies`: Finds arbitrage opportunities for selected currencies.

### Setup

1. Install C++ REST SDK and other required libraries.
2. Compile the C++ backend.
3. Run the backend server.

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

1. Install Node.js and npm.
2. Navigate to the frontend directory and run `npm install` to install dependencies.
3. Run `npm start` to launch the React application.

## Usage

1. Start the backend server.
2. Open the frontend application in a web browser.
3. Select a base currency and additional currencies to calculate arbitrage.
4. Click 'Find Arbitrage Opportunities' to view the results.
