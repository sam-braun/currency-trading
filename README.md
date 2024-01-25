# Arbitrage Opportunity Detector

## Overview

This project is an Arbitrage Opportunity Detector that analyzes exchange rates to identify potential arbitrage opportunities across different currencies. It includes a backend implemented in C++ using the C++ REST SDK (cpprest) for handling HTTP requests and a frontend built with React.

## Table of Contents

1. [Requirements and Dependencies](#Requirements and Dependencies)
2. [Backend Key Functions](#Backend Key Functions)
3. [Frontend Components](#Frontend Components)
4. [Setup](#Setup)
5. [Usage](#Usage)

## Requirements and Dependencies

To correctly compile the backend:

- C++17 or later
- C++ REST SDK (cpprest)
- nlohmann/json for JSON parsing

To correctly run the react app:

- React
- NPM package manager
- Axios for HTTP requests

## Backend Key Functions

- `handleGetRates`: Fetches up-to-date exchange rates.
- `handleGetAvailableCurrencies`: Provides a list of available currencies to use to calculate arbitragr.
- `handleFindArbitrageWithSelectedCurrencies`: Finds arbitrage opportunities for selected currencies.

## Frontend Components

- `CurrencyInputForm`: Allows users to select currencies and initiate searches for arbitrage opportunities.
- `OpportunitiesList`: Displays list of detected arbitrage opportunities.
- `MenuBar`: Dislays time of arbitrage calculations and provides usage instructions.
- `InstructionModal`: Displays instructions for using the application.

## Setup

1. Install C++ REST SDK and other required libraries (using a package manager like vcpkg is recommended).
2. Install Node.js and npm.
3. Customize `start.sh` for your machine's package locations.

## Usage

1. Run `bash start.sh` to compile the backend, and lauch the backend and React app.
2. Start the backend server.
3. Open the frontend application in a web browser.
4. Select a base currency and additional currencies to calculate arbitrage.
5. Click 'Find Arbitrage Opportunities' to view the results.
