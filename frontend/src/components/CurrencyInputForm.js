import React, { useState } from 'react';

function CurrencyInputForm({ onSubmit, availableCurrencies }) {
  const [baseCurrency, setBaseCurrency] = useState('');

  const handleSubmit = (e) => {
    e.preventDefault();
    onSubmit(baseCurrency);
  };

  return (
    <form onSubmit={handleSubmit}>
      <label>
        Select base currency:
        <select value={baseCurrency} onChange={(e) => setBaseCurrency(e.target.value)}>
          {availableCurrencies.map(currency => (
            <option key={currency} value={currency}>{currency}</option>
          ))}
        </select>
      </label>
      <button type="submit">Find Arbitrage Opportunities</button>
    </form>
  );
}

export default CurrencyInputForm;
