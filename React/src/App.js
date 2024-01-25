import React, { useState, useEffect } from 'react';
import axios from 'axios';
import CurrencyInputForm from './components/CurrencyInputForm';
import OpportunitiesList from './components/OpportunitiesList';
import MenuBar from './components/MenuBar';
import InstructionModal from './components/InstructionModal'; // Import the InstructionModal component
import './App.css';

function App() {
	// state for currencies, opportunities, and instruction modal visibility
	const [currencies, setCurrencies] = useState([]);
	const [opportunities, setOpportunities] = useState([]);
	const [showInstructions, setShowInstructions] = useState(true);

	useEffect(() => {
		fetchAvailableCurrencies();
	}, []);

  	const fetchAvailableCurrencies = async () => {
		try {
			const response = await axios.get(`http://localhost:8080/availableCurrencies`);
			setCurrencies(response.data);
		} catch (error) {
			console.error('Error fetching available currencies:', error);
		}
  	};

	const fetchArbitrageOpportunities = async (baseCurrency, selectedCurrencies) => {
		try {
			const response = await axios.get(`http://localhost:8080/arbitrageWithSelectedCurrencies?baseCurrency=${baseCurrency}&selectedCurrencies=${selectedCurrencies.join(',')}`);
			setOpportunities(response.data);
		} catch (error) {
			console.error('Error fetching data:', error);
		}
	};

	const handleCloseInstructions = () => {
		setShowInstructions(false);
	};

	const handleShowInstructions = () => {
		setShowInstructions(true);
	};

	return (
		<div>
			{showInstructions && <InstructionModal onClose={handleCloseInstructions} />}
			<center><h1>Arbitrage Opportunity Detector</h1></center>
			<MenuBar 
				availableCurrencies={currencies} 
				onShowInstructions={handleShowInstructions} // Add this prop
			/>
			<div style={{ display: 'flex', justifyContent: 'space-between', padding: '20px' }}>
				<div style={{ flex: '0 0 30%', marginRight: '50px' }}> {/* Changed this line */}
				<CurrencyInputForm onSubmit={fetchArbitrageOpportunities} availableCurrencies={currencies} />
				</div>
				<div style={{ flex: '0 0 70%', marginLeft: '10px' }}> {/* Changed this line */}
				<OpportunitiesList opportunities={opportunities} />
				</div>
			</div>
		</div>
	);  
}

export default App;
