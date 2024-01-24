import React from 'react';

function OpportunitiesList({ opportunities }) {
    if (!opportunities.length) {
        return <p>No arbitrage opportunities found.</p>;
    }

    return (
        <ul>
            {opportunities.map((opp, index) => {
                return (
                    <li key={index}>
                        {opp.from} -&gt; {opp.mid} -&gt; {opp.to} -&gt; {opp.from}, Profit: {opp.profit}
                    </li>
                );
            })}
        </ul>
    );
}

export default OpportunitiesList;