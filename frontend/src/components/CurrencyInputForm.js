import React, { useState } from 'react';

function CurrencyInputForm({ onSubmit, availableCurrencies }) {
    const [baseCurrency, setBaseCurrency] = useState('');
    const [selectedCurrencies, setSelectedCurrencies] = useState({});

    const handleBaseCurrencyChange = (event) => {
        setBaseCurrency(event.target.value);
    };

    const handleCurrencyCheckboxChange = (currency) => {
        setSelectedCurrencies(prevSelectedCurrencies => ({
            ...prevSelectedCurrencies,
            [currency]: !prevSelectedCurrencies[currency]
        }));
    };

    const handleSubmit = (e) => {
        e.preventDefault();
        onSubmit(baseCurrency, Object.keys(selectedCurrencies).filter(currency => selectedCurrencies[currency]));
    };

    // CSS styles for currency checkbox container
    const currencyCheckboxContainerStyle = {
        display: 'flex',
        flexWrap: 'wrap',
        maxHeight: '200px', 
        overflowY: 'auto',
        columnGap: '10px',
        padding: '10px'
    };


    const currencyCheckboxColumnStyle = {
        width: '30%',
        boxSizing: 'border-box'
    };

    return (
        <form onSubmit={handleSubmit}>
            <label>
                Select base currency:
                <select value={baseCurrency} onChange={handleBaseCurrencyChange}>
                    {availableCurrencies.map(currency => (
                        <option key={currency} value={currency}>{currency}</option>
                    ))}
                </select>
            </label>

            <div style={currencyCheckboxContainerStyle}>
                Select target currencies:
                {availableCurrencies.map(currency => (
                    <div key={currency} style={currencyCheckboxColumnStyle}>
                        <input 
                            type="checkbox"
                            id={currency}
                            checked={!!selectedCurrencies[currency]}
                            onChange={() => handleCurrencyCheckboxChange(currency)}
                        />
                        <label htmlFor={currency}>{currency}</label>
                    </div>
                ))}
            </div>

            <button type="submit">Find Arbitrage Opportunities</button>
        </form>
    );
}

export default CurrencyInputForm;
