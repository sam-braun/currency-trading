import React, { useState, useEffect } from 'react';

function MenuBar({ availableCurrencies, onCurrencySelect }) {
  const [currentTime, setCurrentTime] = useState(new Date());
  const [baseCurrency, setBaseCurrency] = useState('');

  useEffect(() => {
    const timer = setInterval(() => {
      setCurrentTime(new Date());
    }, 1000);

    return () => {
      clearInterval(timer);
    };
  }, []);

  const handleCurrencyChange = (e) => {
    const selectedCurrency = e.target.value;
    setBaseCurrency(selectedCurrency);
    onCurrencySelect(selectedCurrency);
  };

  return (
    <div style={{ display: 'flex', justifyContent: 'space-between', padding: '10px', background: '#eee', alignItems: 'center' }}>
      <div>{currentTime.toLocaleDateString()} {currentTime.toLocaleTimeString()}</div>
      <select onChange={handleCurrencyChange} value={baseCurrency}>
        <option value="" >Select a currency</option>
        {availableCurrencies.map((currency) => (
          <option key={currency.code} value={currency.code}>
            {currency.code} - {currency.name}
          </option>
        ))}
      </select>
    </div>
  );
}

export default MenuBar;