import React, { useState, useEffect } from 'react';

function CurrencyInputForm({ onSubmit, availableCurrencies }) {
    const [selectedCurrencies, setSelectedCurrencies] = useState({});
    const [selectAll, setSelectAll] = useState(false);
    const [searchTerm, setSearchTerm] = useState('');
    const [baseCurrency, setBaseCurrency] = useState('');

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

    const handleBaseCurrencyChange = (e) => {
        setBaseCurrency(e.target.value);
    };

    const handleSearchChange = (e) => {
        setSearchTerm(e.target.value);
    };

    const handleSubmit = (e) => {
        e.preventDefault();
        const selectedCurrencyCodes = Object.keys(selectedCurrencies).filter(currencyCode => selectedCurrencies[currencyCode]);
        if (baseCurrency && selectedCurrencyCodes.length > 0) {
            onSubmit(baseCurrency, selectedCurrencyCodes);
        }
    };

    const isSubmitDisabled = !baseCurrency || Object.values(selectedCurrencies).every(v => !v);

    const filteredCurrencies = searchTerm
        ? availableCurrencies.filter(currency =>
            currency.code.toLowerCase().includes(searchTerm.toLowerCase()) ||
            currency.name.toLowerCase().includes(searchTerm.toLowerCase())
          )
        : availableCurrencies;

    const currencyCheckboxContainerStyle = {
        height: 'calc(100vh - 420px)',
        overflowY: 'auto',
        padding: '10px'
    };

    const inputStyle = {
        width: '100%',
        padding: '10px',
        margin: '10px 0'
    };

    const currencyItemStyle = {
        display: 'flex',
        alignItems: 'center',
        padding: '4px 0'
    };

    const emojiStyle = {
        marginRight: '8px',
        fontSize: '1.2em'
    };

    return (
        <form onSubmit={handleSubmit}>
            <label>
                Select a base currency:
                <select onChange={handleBaseCurrencyChange} value={baseCurrency} style={inputStyle}>
                    <option value="">Select a currency</option>
                    {availableCurrencies
                        .sort((a, b) => a.name.localeCompare(b.name))
                        .map((currency) => (
                            <option key={currency.code} value={currency.code}>
                                {currency.emoji} {currency.code} - {currency.name}
                            </option>
                        ))
                    }
                </select>
            </label>
            <br />
            <label>
                Choose additional currencies:
            </label>
            <input 
                type="text"
                placeholder="Search currencies by code or name..."
                value={searchTerm}
                onChange={handleSearchChange}
                style={inputStyle}
            />
            <div>
                <label style={currencyItemStyle}>
                    <input 
                        type="checkbox"
                        checked={selectAll}
                        onChange={handleSelectAllCurrencies}
                    />
                    <span style={{ marginLeft: '8px' }}>Select All</span>
                </label>
            </div>
            <div style={currencyCheckboxContainerStyle}>
                {filteredCurrencies.map(currency => (
                    <div key={currency.code} style={currencyItemStyle}>
                        <label style={{ display: 'flex', alignItems: 'center', width: '100%' }}>
                            <input 
                                type="checkbox"
                                checked={selectedCurrencies[currency.code] || false}
                                onChange={() => handleCurrencyCheckboxChange(currency.code)}
                            />
                            <span style={emojiStyle}>{currency.emoji}</span>
                            <span>{currency.code} - {currency.name}</span>
                        </label>
                    </div>
                ))}
            </div>
            <button 
                type="submit" 
                disabled={isSubmitDisabled}
                style={{
                    padding: '10px 20px',
                    marginTop: '10px',
                    backgroundColor: isSubmitDisabled ? '#cccccc' : '#4CAF50',
                    color: 'white',
                    border: 'none',
                    borderRadius: '4px',
                    cursor: isSubmitDisabled ? 'not-allowed' : 'pointer'
                }}
            >
                Find Arbitrage Opportunities
            </button>
        </form>
    );
}

export default CurrencyInputForm;
