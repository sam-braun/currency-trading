import React, { useState } from 'react';

const PAGE_SIZE = 20; // Number of opportunities per page

function OpportunitiesList({ opportunities }) {
    const [currentPage, setCurrentPage] = useState(1);
    const totalPages = Math.ceil(opportunities.length / PAGE_SIZE);

    if (!opportunities.length) {
        return <p>No arbitrage opportunities found.</p>;
    }

    const startIndex = (currentPage - 1) * PAGE_SIZE;
    const currentOpportunities = opportunities.slice(startIndex, startIndex + PAGE_SIZE);

    const goToPage = (pageNumber) => {
        setCurrentPage(pageNumber);
    };

    return (
        <>
            <ul>
                {currentOpportunities.map((opp, index) => (
                    <li key={index}>
                        {opp.from} -&gt; {opp.mid} -&gt; {opp.to} -&gt; {opp.from}, Profit: {opp.profit}
                    </li>
                ))}
            </ul>
            <div>
                {Array.from({ length: totalPages }, (_, i) => i + 1).map((pageNumber) => (
                    <button
                        key={pageNumber}
                        onClick={() => goToPage(pageNumber)}
                        disabled={pageNumber === currentPage}
                    >
                        {pageNumber}
                    </button>
                ))}
            </div>
        </>
    );
}

export default OpportunitiesList;
