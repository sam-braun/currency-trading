import React, { useState, useEffect } from 'react';

function CurrencyInputForm({ onSubmit, availableCurrencies, baseCurrency }) {
    const [selectedCurrencies, setSelectedCurrencies] = useState({});
    const [selectAll, setSelectAll] = useState(false);

    useEffect(() => {
        const updatedSelectedCurrencies = availableCurrencies.reduce((acc, currency) => {
            acc[currency.code] = selectAll;
            return acc;
        }, {});
        setSelectedCurrencies(updatedSelectedCurrencies);
    }, [selectAll, availableCurrencies]);

    const handleCurrencyCheckboxChange = (currencyCode) => {
        setSelectedCurrencies(prevSelectedCurrencies => ({
            ...prevSelectedCurrencies,
            [currencyCode]: !prevSelectedCurrencies[currencyCode]
        }));
    };

    const handleSelectAllCurrencies = () => {
        const newSelectAll = !selectAll;
        setSelectAll(newSelectAll);
        setSelectedCurrencies(availableCurrencies.reduce((acc, currency) => {
            acc[currency.code] = newSelectAll;
            return acc;
        }, {}));
    };

    const handleSubmit = (e) => {
        e.preventDefault();
        const selectedCurrencyCodes = Object.keys(selectedCurrencies).filter(currencyCode => selectedCurrencies[currencyCode]);
        if (baseCurrency && selectedCurrencyCodes.length > 0) {
            onSubmit(baseCurrency, selectedCurrencyCodes);
        }
    };

    const isSubmitDisabled = !baseCurrency || Object.values(selectedCurrencies).every(v => !v);

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

    const sortedCurrencies = [...availableCurrencies].sort((a, b) => a.code.localeCompare(b.code));

    return (
        <form onSubmit={handleSubmit}>
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
                <button type="submit" disabled={isSubmitDisabled}>Find Arbitrage Opportunities</button>
            </div>
        </form>
    );
}

export default CurrencyInputForm;
