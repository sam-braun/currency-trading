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
    <div>
      <center><h1>Arbitrage Opportunity Detector</h1></center>
      <MenuBar availableCurrencies={currencies} onCurrencySelect={handleMenuCurrencyChange} />
      <div style={{ display: 'flex', justifyContent: 'space-between', padding: '20px' }}>
        <div style={{ flex: '0 0 30%', marginRight: '10px' }}> {/* Changed this line */}
          <CurrencyInputForm onSubmit={fetchArbitrageOpportunities} availableCurrencies={currencies} />
        </div>
        <div style={{ flex: '0 0 70%', marginLeft: '10px' }}> {/* Changed this line */}
          <OpportunitiesList opportunities={opportunities} />
        </div>
      </div>
    </div>
  );
}

export default App;
