import React from 'react';

function InstructionModal({ onClose }) {
    return (
        <div style={{
            position: 'fixed',
            top: 0,
            left: 0,
            width: '100%',
            height: '100%',
            backgroundColor: 'rgba(0, 0, 0, 0.5)',
            display: 'flex',
            justifyContent: 'center',
            alignItems: 'center',
            zIndex: 1000
        }}>
            <div style={{
                backgroundColor: 'white',
                padding: '20px',
                borderRadius: '5px',
                maxWidth: '500px',
                width: '100%'
            }}>
                <h2>Welcome to the Arbitrage Opportunity Detector!</h2>
                <p>Instructions on how to use the application:</p>
                <ul>
                    <li>Select a base currency.</li>
                    <li>Choose additional currencies to compare.</li>
                    <li>Click 'Find Arbitrage Opportunities' to see the results.</li>
                </ul>
                <button onClick={onClose} style={{ marginTop: '20px' }}>Close</button>
            </div>
        </div>
    );
}

export default InstructionModal;
