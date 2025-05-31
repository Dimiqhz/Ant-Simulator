# 🐜 Ant Simulator

**Ant Simulator** is a console-based simulation of ant colony life, written in modern C++ using object-oriented programming principles. The project demonstrates the basics of simulation, behavioral AI, object interaction, and world state management.

---

## 📁 Project Structure

```
include/            # Header files for classes and components
src/
 ├── core/          # Core structures (e.g., Grid)
 ├── entities/      # Entities like Ant, Food, Enemy, etc.
 ├── utils/         # Utility modules (e.g., Random)
 ├── world/         # World modeling and updates
 └── main.cpp       # Entry point
CMakeLists.txt      # Project build script
```

---

## 🧠 Features

- 🐜 Worker and warrior ants with unique behaviors
- 🍞 Food searching and delivery to the anthill
- 🧪 Pheromone-based navigation system
- ⚔️ Battles with enemies (e.g., beetles)
- 💨 Pheromone spreading and fading over time
- 🧱 Obstacles (e.g., cigarette butts)

---

## 🛠️ Build and Run

### 🔧 Requirements

- C++20
- CMake 3.15+
- UTF-8 capable terminal (for proper display)

### ⚙️ Build

```bash
git clone https://github.com/Dimiqhz/Ant-Simulator
cd Ant-Simulator
mkdir build && cd build
cmake ..
make
```

### ▶️ Run

```bash
./ant_simulator --auto (or ./ant_simulator for manual step-by-step stimulation)
```

---

## 📷 Example Output

```
. . . . . . . . 
. . W . W . . .
. . . + H H . .
. . . . H H . .
```

---

## 🔍 CLI Options

Future planned CLI features:

- `--auto` — automatic simulation mode
- `--height` — set a custom height for the map
- `--width` — set a custom width for the map

---

## 🗺️ Legend (Map Symbols)

| Symbol | Meaning                   |
|--------|---------------------------|
| `W`    | Worker Ant                |
| `C`    | Worker Ant with food      |
| `@`    | Food                      |
| `H`    | Anthill                   |
| `+`    | Pheromone                 |
| `.`    | Empty Tile                |
| `B`    | Beetle (Enemy)            |
| `M`    | Warrior Ant               |
| `~`    | Cigarette Butt (Obstacle) |

---

## ✅ Project Status

- [x] Pheromone system
- [x] Basic ant AI
- [x] Food searching behavior
- [x] Enemy interaction
- [ ] GUI/visualization
- [ ] State saving/loading

---

## 📜 License

This project is licensed under the GNU License.
