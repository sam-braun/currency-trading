import React, { useState, useEffect } from 'react';
import axios from 'axios';
import CurrencyInputForm from './components/CurrencyInputForm';
import OpportunitiesList from './components/OpportunitiesList';
import MenuBar from './components/MenuBar';

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
    <div>
      <center><h1>Arbitrage Opportunities Finder</h1></center>
      <MenuBar availableCurrencies={currencies} onCurrencySelect={handleMenuCurrencyChange} />
      <CurrencyInputForm onSubmit={fetchArbitrageOpportunities} availableCurrencies={currencies} baseCurrency={menuCurrency} />
      <OpportunitiesList opportunities={opportunities} />
    </div>
  );
}

export default App;
