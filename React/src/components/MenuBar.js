import React, { useState, useEffect } from 'react';

function MenuBar() {
  const [currentTime, setCurrentTime] = useState(new Date());

  useEffect(() => {
    const timer = setInterval(() => {
      setCurrentTime(new Date());
    }, 1000);

    return () => {
      clearInterval(timer);
    };
  }, []);

  return (
    <div style={{ display: 'flex', justifyContent: 'space-between', padding: '10px', background: '#eee', alignItems: 'center' }}>
      <div>{currentTime.toLocaleDateString()} {currentTime.toLocaleTimeString()} </div>
    </div>
  );
}

export default MenuBar;
