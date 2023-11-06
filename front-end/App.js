import React, { useState, useEffect } from 'react';
import './App.css';

function App() {
  const [data, setData] = useState([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    fetchArbitrageOpps();
  }, []);

  const fetchArbitrageOpps = async () => {
    try {
      const response = await fetch('/api/arbitrage-opportunities');
      if (!response.ok) {
        throw new Error('Network response was not ok ' + response.statusText);
      }
      const data = await response.json();
      setData(data);
    } catch (error) {
      console.error('There has been a problem with your fetch operation:', error);
    } finally {
      setLoading(false);
    }
  };



  return (
    <div className="App">
      <header className="App-header">
        <h1>Arbitrage Opportunities</h1>
      </header>
      {loading ? (
        <p>Loading...</p>
      ) : (
        <table>
          <thead>
            <tr>
              <th>Currency Pair</th>
              <th>Rate</th>
            </tr>
          </thead>
          <tbody>
            {data.map((opportunity, index) => (
              <tr key={index}>
                <td>{opportunity.route.join(' -> ')}</td>
                <td>{opportunity.rate}</td>
              </tr>
            ))}
          </tbody>
        </table>
      )}
    </div>
  );
}

export default App;