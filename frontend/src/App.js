import React, { useState } from 'react';
import axios from 'axios';
import CurrencyInputForm from './components/CurrencyInputForm';
import OpportunitiesList from './components/OpportunitiesList';

function App() {
  const [opportunities, setOpportunities] = useState([]);

  const fetchArbitrageOpportunities = async (baseCurrency) => {
    try {
      const response = await axios.get(`http://localhost:8080/arbitrage?baseCurrency=${baseCurrency}`);
      console.log(response.data);
      setOpportunities(response.data);
    } catch (error) {
      console.error('Error fetching data:', error);
    }
  };

  return (
    <div>
      <h1>Arbitrage Opportunities Finder</h1>
      <CurrencyInputForm onSubmit={fetchArbitrageOpportunities} />
      <OpportunitiesList opportunities={opportunities} />
    </div>
  );
}

export default App;