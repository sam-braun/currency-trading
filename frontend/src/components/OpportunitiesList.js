import React from 'react';

function OpportunitiesList({ opportunities }) {
    if (!opportunities.length) {
        return <p>No arbitrage opportunities found.</p>;
    }

    return (
        <ul>
            {opportunities.map((opportunity, index) => {
                return (
                    <li key={index}>
                        Arbitrage Opportunity: {opportunity.from} -&gt; {opportunity.to}, Profit: {opportunity.profit}
                    </li>
                );
            })}
        </ul>
    );
}

export default OpportunitiesList;