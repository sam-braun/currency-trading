import React, { useState, useEffect } from 'react';
import axios from 'axios';
import CurrencyInputForm from './components/CurrencyInputForm';
import OpportunitiesList from './components/OpportunitiesList';

function App() {
  const [currencies, setCurrencies] = useState([]);
  const [opportunities, setOpportunities] = useState([]);

  useEffect(() => {
    fetchAvailableCurrencies();
  }, []);

  const fetchAvailableCurrencies = async () => {
    try {
      const response = await axios.get(`http://localhost:8080/availableCurrencies`);
      setCurrencies(response.data);
    } catch (error) {
      console.error('Error fetching available currencies:', error);
    }
  };

  const fetchArbitrageOpportunities = async (baseCurrency) => {
    try {
      const response = await axios.get(`http://localhost:8080/arbitrage?baseCurrency=${baseCurrency}`);
      setOpportunities(response.data);
    } catch (error) {
      console.error('Error fetching data:', error);
    }
  };

  return (
    <div>
      <h1>Arbitrage Opportunities Finder</h1>
      <CurrencyInputForm onSubmit={fetchArbitrageOpportunities} availableCurrencies={currencies} />
      <OpportunitiesList opportunities={opportunities} />
    </div>
  );
}

export default App;
