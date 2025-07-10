import logo from './logo.svg';
import './App.css';

function App() {
    // let workshop = process.env.PUBLIC_URL + "/workshop1.png";
    let ubi = process.env.PUBLIC_URL + "/ubi.png";

    const moveRobot = (direction) =>{
        const backend = "http://localhost:4000/"+direction;
        fetch(backend, {mode: 'no-cors'}).then(response => {
            console.log('Fetch done');
        }).catch(error => {
            console.log('Fetch error:', error);
        })
    }

    return (
        <div className="App">
        <header className="App-header">
        <h2>Nemo Robot Controller</h2>
        <svg class="robot" viewBox="0 0 200 200" xmlns="http://www.w3.org/2000/svg">
        <line x1="100" y1="30" x2="100" y2="50" stroke="#61dafb" stroke-width="4"/>
        <circle cx="100" cy="25" r="5" fill="#61dafb"/>
        <rect x="60" y="50" width="80" height="80" rx="10" fill="#61dafb" stroke="#333" stroke-width="2"/>
        <circle cx="80" cy="80" r="6" fill="#000"/>
        <circle cx="120" cy="80" r="6" fill="#000"/>
        <rect x="85" y="100" width="30" height="6" rx="3" fill="#333"/>
        <rect x="50" y="130" width="100" height="20" rx="10" fill="#444"/>
        <circle cx="60" cy="140" r="4" fill="#888"/>
        <circle cx="75" cy="140" r="4" fill="#888"/>
        <circle cx="90" cy="140" r="4" fill="#888"/>
        <circle cx="105" cy="140" r="4" fill="#888"/>
        <circle cx="120" cy="140" r="4" fill="#888"/>
        <circle cx="135" cy="140" r="4" fill="#888"/>
        </svg>
        <div style={{display: "flex", flexDirection: "column", gap: "8px"}}>
        <button onClick={() => moveRobot("forward")} style={{width:"120px", height:"60px"}}>GO FORWARD</button>
        <button onClick={() => moveRobot("backward")} style={{width:"120px", height:"60px"}}>GO BACKWARD</button>
        </div>
        <div className="logos">
        <img src={ubi} alt="UBI" />
        </div>
        <span style={{fontSize: "12px", color: "#fff", fontWeight: "bold"}}>
        Universidade da Beira Interior | Departamento de Informática
        </span>
        </header>
        </div>
    );
}

export default App;
