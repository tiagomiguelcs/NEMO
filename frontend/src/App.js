import './App.css';

function App() {
    const DEBUG = false;
    
    const moveRobot = (obj, direction) =>{
        console.log(obj);
        obj.target.className = "button wait";
        const backend = "http://localhost:4000/"+direction;
        fetch(backend, {mode: 'no-cors'}).then(response => {
            console.log("# Nemo Robot Controller: ", response);
            if (obj.target.id === "stop-button")
                obj.target.className = "button stop"
            else
                obj.target.className = "button direction"
        }).catch(error => {
            console.log("# (Error) Nemo Robot Controller: ", error);
            if (!DEBUG){
                if (obj.target.id === "stop-button")
                    obj.target.className = "button stop"
                else
                    obj.target.className = "button direction"
            }
        })
    }

    return (
     <div id="shell">
        <header className="topbar">
        <div className="brand">
            <div>
                <div className="brand-title">NEMO</div>
                <div className="brand-subtitle">ROBOT CONTROLLER</div>
            </div>
        </div>
        <div className="status-pill" id="connection-pill" role="status" aria-live="polite">
            <span className="status-dot"></span>
            <span id="connection-label">Modo demonstração</span>
        </div>
        </header>
        <main>
            <section className="robot-card panel" aria-label="Robô Nemo">
                <div>
                    <img src="nemo.png" className="robot-image"/>
                </div>
                <h1>Nemo Robot</h1><p className="muted">Controlar o robô em tempo real.</p>
                <br/>
                <div className="dpad" aria-label="Controlos direcionais">
                    <button type="button" className="button direction" data-command="FORWARD" aria-label="Avançar" onClick={(elm) => moveRobot(elm, "forward")}>
                    ↑
                    </button>
                    <button type="button" className="button stop" id="stop-button" aria-label="Parar o robô" onClick={(elm) => moveRobot(elm, "stop")}>
                    ■
                    </button>
                    <button type="button" className="button direction" data-command="BACKWARD" aria-label="Recuar" onClick={(elm) => moveRobot(elm, "backward")}>
                    ↓
                    </button>
                </div>
            </section>
        </main>
        <footer>
            <div className="ubi-symbol" aria-label="UBI">
                <img src="UBI.png"/>
            </div>
            <span>
                Universidade da Beira Interior 
                <span className="footer-separator">|</span> 
                Departamento de Informática
            </span>
        </footer>
     </div>
    );
}

export default App;
