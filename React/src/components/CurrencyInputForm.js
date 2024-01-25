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

    return (
        <form onSubmit={handleSubmit}>
            <label>
                Select a base currency:
                <select onChange={handleBaseCurrencyChange} value={baseCurrency} style={inputStyle}>
                    <option value="">Select a currency</option>
                    {availableCurrencies.map((currency) => (
                        <option key={currency.code} value={currency.code}>
                            {currency.code} - {currency.name}
                        </option>
                    ))}
                </select>
            </label>
            <br />
            <label>
                Choose additional currencies:
            </label>
            <input 
                type="text"
                placeholder="Search currencies..."
                value={searchTerm}
                onChange={handleSearchChange}
                style={inputStyle}
            />
            <div style={currencyCheckboxContainerStyle}>
                {filteredCurrencies.map(currency => (
                    <div key={currency.code}>
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
