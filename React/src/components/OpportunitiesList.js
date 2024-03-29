import React, { useState } from 'react';

const PAGE_SIZE = 18; // Number of opportunities per page
const MAX_PAGE_BUTTONS = 10; // Maximum number of page buttons to display

function OpportunitiesList({ opportunities }) {
    const [currentPage, setCurrentPage] = useState(1);
    const totalPages = Math.ceil(opportunities.length / PAGE_SIZE);

    if (!opportunities.length) {
        return <p>No arbitrage opportunities found yet.. Please try selecting more currency demoninations.</p>;
    }

    const startIndex = (currentPage - 1) * PAGE_SIZE;
    const currentOpportunities = opportunities.slice(startIndex, startIndex + PAGE_SIZE);

    const goToPage = (pageNumber) => {
        setCurrentPage(pageNumber);
    };

    const renderPageButtons = () => {
        let buttons = [];
        let startPage, endPage;

        if (totalPages <= MAX_PAGE_BUTTONS) {
            startPage = 1;
            endPage = totalPages;
        } else {
            if (currentPage <= 6) {
                startPage = 1;
                endPage = 9;
            } else if (currentPage + 4 >= totalPages) {
                startPage = totalPages - 8;
                endPage = totalPages;
            } else {
                startPage = currentPage - 4;
                endPage = currentPage + 4;
            }
        }

        if (startPage > 1) {
            buttons.push(renderButton(1));
            if (startPage > 2) {
                buttons.push('...');
            }
        }

        for (let i = startPage; i <= endPage; i++) {
            buttons.push(renderButton(i));
        }

        if (endPage < totalPages) {
            if (endPage < totalPages - 1) {
                buttons.push('...');
            }
            buttons.push(renderButton(totalPages));
        }

        return buttons;
    };

    const renderButton = (pageNumber) => (
        <button
            key={pageNumber}
            onClick={() => goToPage(pageNumber)}
            disabled={pageNumber === currentPage}
        >
            {pageNumber}
        </button>
    );

    const tableStyle = {
        margin: '0 auto',
        borderCollapse: 'collapse'
    };

    const cellStyle = {
        padding: '7px 20px' // add space between columns
    };

    const paginationStyle = {
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        padding: '10px',
        marginTop: '10px'
    };

    return (
        <>
            <div style={{ overflowX: 'auto' }}> {/* Wrapper to handle overflow and centering */}
                <table style={tableStyle}>
                    <thead>
                        <tr>
                            <th style={cellStyle}>Opportunity</th>
                            <th style={cellStyle}>Profit</th>
                        </tr>
                    </thead>
                    <tbody>
                        {currentOpportunities.map((opp, index) => (
                            <tr key={index}>
                                <td style={cellStyle}>{opp.from} &#8594; {opp.mid} &#8594; {opp.to} &#8594; {opp.from}</td>
                                <td style={cellStyle}>{parseFloat(opp.profit).toFixed(2)}</td> {/* Round to 2 decimal points */}
                            </tr>
                        ))}
                    </tbody>
                </table>
            </div>
            <div style={paginationStyle}>
                {renderPageButtons()}
            </div>
        </>
    );
}

export default OpportunitiesList;