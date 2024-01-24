import React, { useState, useEffect } from 'react';

function CurrencyInputForm({ onSubmit, availableCurrencies }) {
    const [baseCurrency, setBaseCurrency] = useState('');
    const [selectedCurrencies, setSelectedCurrencies] = useState({});
    const [selectAll, setSelectAll] = useState(false);

    useEffect(() => {
        const updatedSelectedCurrencies = availableCurrencies.reduce((acc, currency) => {
            acc[currency] = selectAll;
            return acc;
        }, {});
        setSelectedCurrencies(updatedSelectedCurrencies);
    }, [selectAll, availableCurrencies]);

    const handleBaseCurrencyChange = (event) => {
        setBaseCurrency(event.target.value);
    };

    const handleCurrencyCheckboxChange = (currency) => {
        setSelectedCurrencies(prevSelectedCurrencies => ({
            ...prevSelectedCurrencies,
            [currency]: !prevSelectedCurrencies[currency]
        }));
    };

    const handleSelectAllCurrencies = () => {
        setSelectAll(!selectAll);
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

    // Sort availableCurrencies alphabetically
    const sortedCurrencies = [...availableCurrencies].sort();

    return (
        <form onSubmit={handleSubmit}>
            <label>
                Select base currency: {' '}
                <select value={baseCurrency} onChange={handleBaseCurrencyChange}>
                    {sortedCurrencies.map(currency => (
                        <option key={currency} value={currency}>{currency}</option>
                    ))}
                </select>
            </label>
            <br />

            <label>
                Select target currencies:
            </label>
            <div style={currencyCheckboxContainerStyle}>
                {sortedCurrencies.map(currency => (
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

            <div style={{ marginTop: '10px' }}>
                <button type="button" onClick={handleSelectAllCurrencies}>
                    {selectAll ? 'Deselect All Currencies' : 'Select All Currencies'}
                </button>
            </div>

            <div style={{ marginTop: '10px' }}>
                <button type="submit">Find Arbitrage Opportunities</button>
            </div>
        </form>
    );
}

export default CurrencyInputForm;
