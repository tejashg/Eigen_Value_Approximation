import React, { useEffect, useState } from "react";
import "./App.css";

function App() {
  const [matrixSize, setMatrixSize] = useState(0);
  const [matrixData, setMatrixData] = useState([0]);
  const [maxIterations, setMaxIterations] = useState(5);
  const [precision, setPrecision] = useState(2);
  const [algorithm, setAlgorithm] = useState("");
  const [output, setOutput] = useState("");
  const [appContainerStyle, setAppContainerStyle] = useState({
    height: "calc(100vh - 17.6px)",
  });

  useEffect(() => {
    let arr = [];
    let size = matrixSize;
    for (let i = 0; i < size; i++) {
      arr[i] = [];
      for (let j = 0; j < size; j++) {
        arr[i][j] = 0;
      }
    }
    setMatrixData(arr);
  }, [matrixSize]);

  const handleMatrixSizeChange = (event) => {
    const size = parseInt(event.target.value);
    setMatrixSize(event.target.value);
  };

  const handleMatrixDataChange = (event, row, col) => {
    const value = parseInt(event.target.value);
    const newData = [...matrixData];
    newData[row][col] = value;
    setMatrixData(newData);
  };

  const handleMaxIterationChange = (event) => {
    setMaxIterations(event.target.value);
  };

  const handlePrecisionChange = (event) => {
    setPrecision(event.target.value);
  };

  const handleSubmit = () => {
    setAppContainerStyle({});
    const matrix = {
      size: matrixSize,
      data: matrixData,
      maxIterations: maxIterations,
      precision: precision,
      algorithm: algorithm,
    };

    fetch(import.meta.env.VITE_BACKEND_URL, {
      method: "POST",
      mode: 'no-cors',
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(matrix),
    })
      .then((response) => response.json())
      .then((data) => setOutput(data.output))
      .catch((error) => console.error(error));
  };

  const handleAlgorithmSelection = (event) => {
    const type = event.target.value;
    setAlgorithm(type);
  };

  const renderMatrixInput = () => {
    const matrix = [];
    for (let row = 0; row < matrixSize; row++) {
      const rowData = [];
      for (let col = 0; col < matrixSize; col++) {
        rowData.push(
          <input
            type="number"
            key={`${row}-${col}`}
            onChange={(event) => handleMatrixDataChange(event, row, col)}
          />
        );
      }
      matrix.push(
        <div key={row} className="matrix-row">
          {rowData}
        </div>
      );
    }
    return matrix;
  };

  return (
    <div className="app-container" style={appContainerStyle}>
      <div className="app-content">
        <h1 className="title">Eigen Value Calculator</h1>
        <label className="algorithm-label" htmlFor="algorithm">
          Select Algorithm:
        </label>
        <select
          className="algorithm-select"
          id="algorithm"
          onChange={handleAlgorithmSelection}
        >
          <option value="" selected disabled hidden>
            Choose here
          </option>
          <option value="power">Power Method</option>
          <option value="qr">QR Algorithm</option>
        </select>
        {algorithm && (
          <div className="matrix-size-container">
            <label className="matrix-size-label" htmlFor="matrix-size">
              Matrix Size:
            </label>
            <input
              className="matrix-size-input"
              type="number"
              id="matrix-size"
              onChange={handleMatrixSizeChange}
            />
            {matrixSize > 0 && (
              <>
                <p className="matrix-input-desc">Enter matrix elements:</p>
                <div className="matrix-container">{renderMatrixInput()}</div>
                <label
                  className="max-iterations-label"
                  htmlFor="max-iterations"
                >
                  Maximum Iterations:
                </label>
                <input
                  className="max-iterations-input"
                  type="number"
                  step="any"
                  id="max-iterations"
                  defaultValue={maxIterations}
                  onChange={handleMaxIterationChange}
                />
                <label className="precision-label" htmlFor="precision">
                  Maximum Decimal Places:
                </label>
                <input
                  className="precision-input"
                  type="number"
                  step="any"
                  id="precision"
                  defaultValue={precision}
                  onChange={handlePrecisionChange}
                />
                <button className="calculate-btn" onClick={handleSubmit}>
                  Calculate
                </button>
                {output && (
                  <div className="output-container">
                    <p className="output-label">Output:</p>
                    <pre className="output-value" style={{ fontSize: "18px" }}>
                      {output}
                    </pre>
                  </div>
                )}
              </>
            )}
          </div>
        )}
      </div>
    </div>
  );
}

export default App;
