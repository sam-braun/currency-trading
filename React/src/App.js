import React, { useState, useEffect } from 'react';
import axios from 'axios';
import CurrencyInputForm from './components/CurrencyInputForm';
import OpportunitiesList from './components/OpportunitiesList';
import MenuBar from './components/MenuBar';
import './App.css';

function App() {
  const [currencies, setCurrencies] = useState([]);
  const [opportunities, setOpportunities] = useState([]);
  const [menuCurrency, setMenuCurrency] = useState('');

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

  const fetchArbitrageOpportunities = async (baseCurrency, selectedCurrencies) => {
    try {
      const response = await axios.get(`http://localhost:8080/arbitrageWithSelectedCurrencies?baseCurrency=${baseCurrency}&selectedCurrencies=${selectedCurrencies.join(',')}`);
      setOpportunities(response.data);
    } catch (error) {
      console.error('Error fetching data:', error);
    }
  };

  const handleMenuCurrencyChange = (currency) => {
    setMenuCurrency(currency);
  };

  return (
    <div className="app">
      <center><h1>Arbitrage Opportunity Detector</h1></center>
      <div className="header">
        <MenuBar availableCurrencies={currencies} onCurrencySelect={handleMenuCurrencyChange} />
      </div>
      <div className="content-container">
        <CurrencyInputForm onSubmit={fetchArbitrageOpportunities} availableCurrencies={currencies} baseCurrency={menuCurrency} />
        <OpportunitiesList opportunities={opportunities} />
      </div>
    </div>
  );
}

export default App;
