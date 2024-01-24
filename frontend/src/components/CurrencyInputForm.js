import React, { useState, useEffect } from 'react';

function CurrencyInputForm({ onSubmit, availableCurrencies }) {
    const [baseCurrency, setBaseCurrency] = useState('');
    const [selectedCurrencies, setSelectedCurrencies] = useState({});
    const [selectAll, setSelectAll] = useState(false);

    useEffect(() => {
        const updatedSelectedCurrencies = availableCurrencies.reduce((acc, currency) => {
            acc[currency.code] = selectAll;
            return acc;
        }, {});
        setSelectedCurrencies(updatedSelectedCurrencies);
    }, [selectAll, availableCurrencies]);

    const handleBaseCurrencyChange = (event) => {
        setBaseCurrency(event.target.value);
    };

    const handleCurrencyCheckboxChange = (currencyCode) => {
        setSelectedCurrencies(prevSelectedCurrencies => ({
            ...prevSelectedCurrencies,
            [currencyCode]: !prevSelectedCurrencies[currencyCode]
        }));
    };

    const handleSelectAllCurrencies = () => {
        setSelectAll(!selectAll);
    };

    const handleSubmit = (e) => {
        e.preventDefault();
        onSubmit(baseCurrency, Object.keys(selectedCurrencies).filter(currencyCode => selectedCurrencies[currencyCode]));
    };

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

    // Sort availableCurrencies alphabetically using the code property
    const sortedCurrencies = [...availableCurrencies].sort((a, b) => {
        const codeA = a.code || a;
        const codeB = b.code || b;
        return codeA.localeCompare(codeB);
    });

    return (
        <form onSubmit={handleSubmit}>
            <label>
                Select base currency: {' '}
                <select value={baseCurrency} onChange={handleBaseCurrencyChange}>
                    {sortedCurrencies.map(currency => (
                        <option key={currency.code} value={currency.code}>
                            {currency.code} - {currency.name}
                        </option>
                    ))}
                </select>
            </label>
            <br />

            <label>
                Select target currencies:
            </label>
            <div style={currencyCheckboxContainerStyle}>
                {sortedCurrencies.map(currency => (
                    <div key={currency.code} style={currencyCheckboxColumnStyle}>
                        <input 
                            type="checkbox"
                            id={currency.code}
                            checked={!!selectedCurrencies[currency.code]}
                            onChange={() => handleCurrencyCheckboxChange(currency.code)}
                        />
                        <label htmlFor={currency.code}>{currency.code} - {currency.name}</label>
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
