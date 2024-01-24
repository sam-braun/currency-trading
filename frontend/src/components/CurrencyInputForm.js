import React, { useState } from 'react';

function CurrencyInputForm({ onSubmit }) {
  const [baseCurrency, setBaseCurrency] = useState('');

  const handleSubmit = (e) => {
    e.preventDefault();
    onSubmit(baseCurrency);
  };

  return (
    <form onSubmit={handleSubmit}>
      <label>
        Enter base currency (e.g., USD, EUR, JPY):
        <input type="text" value={baseCurrency} onChange={(e) => setBaseCurrency(e.target.value)} />
      </label>
      <button type="submit">Find Arbitrage Opportunities</button>
    </form>
  );
}

export default CurrencyInputForm;