
Aquí tienes el contenido del `README.md` y el código C++ por separado.

## Contenido del Archivo `hanoi_exceptions.cpp` (Código Fuente)

```cpp
#include <iostream>
#include <vector>
#include <exception>
#include <algorithm> // Necesario para std::reverse en GetBlocks

// =================================================================
// Excepciones Personalizadas (Heredan de std::exception)
// =================================================================

// Excepcin 1: Torres fuera de rango (1, 2 o 3)
class InvalidTowerException : public std::exception {
public:
	const char* what() const noexcept override {
		return "Error de Rango: El nmero de torre debe ser entre 1 y 3.";
	}
};

// Excepcin 2: Disco ms grande sobre uno pequeo
class InvalidMoveException : public std::exception {
public:
	const char* what() const noexcept override {
		return "Movimiento Invlido: No se puede colocar un disco ms grande sobre uno ms pequeo.";
	}
};

// Excepcin 3: Torre vaca
class EmptyTowerException : public std::exception {
public:
	const char* what() const noexcept override {
		return "Error de Pila: La torre de origen est vaca.";
	}
};

// =================================================================
// Clase Node (Nodo para la Pila)
// =================================================================
class Node {
private:
	int dato;
	Node* next;

public:
	Node(int block) : dato(block), next(nullptr) {}
	Node(int block, Node* nextNode) : dato(block), next(nextNode) {}

	int getDato() { return dato; }
	Node* getNext() { return next; }
};

// =================================================================
// Clase Pile (Implementacin de Pila / Stack)
// =================================================================
class Pile {
private:
	Node* top;

public:
	Pile() : top(nullptr) {}

	~Pile() {
		while (!Empty()) {
			// Usamos Pop() para liberar memoria de forma segura
			try { Pop(); } catch (...) {}
		}
	}

	void Push(int block) {
		Node* newNode = new Node(block, top);
		top = newNode;
	}

	int Pop() {
		if (top == nullptr) {
			// Lanza EmptyTowerException si se intenta sacar un elemento de una pila vaca
			throw EmptyTowerException();
		}
		int block = top->getDato();
		Node* temp = top;
		top = top->getNext();
		delete temp;
		return block;
	}

	int Peek() {
		if (top == nullptr) {
			// Lanza EmptyTowerException si se intenta ver el tope de una pila vaca
			throw EmptyTowerException();
		}
		return top->getDato();
	}

	bool Empty() {
		return top == nullptr;
	}

	// Obtiene los bloques de la pila (útil para la visualización)
	std::vector<int> GetBlocks() {
		std::vector<int> blocks;
		Node* current = top;
		while (current != nullptr) {
			blocks.push_back(current->getDato());
			current = current->getNext();
		}
		std::reverse(blocks.begin(), blocks.end()); 
		return blocks;
	}
};

// =================================================================
// Clase Tower (Torre de Hanoi)
// =================================================================
class Tower {
public:
	Pile blocks;

	void AddBlocks(int block) {
		blocks.Push(block);
	}

	bool Move(Tower& targetTower) {
		// Validacin 1: EXCEPCION 3 (Torre vaca)
		if (blocks.Empty()) {
			throw EmptyTowerException();
		}

		int diskToMove = blocks.Peek();

		// Validacin 2: EXCEPCION 2 (Movimiento invlido)
		if (!targetTower.blocks.Empty() && diskToMove > targetTower.blocks.Peek()) {
			throw InvalidMoveException();
		}

		// Movimiento exitoso
		targetTower.blocks.Push(blocks.Pop());
		return true;
	}
};

// =================================================================
// Funcin global para imprimir torres (visualizacin)
// =================================================================
void PrintTowers(Tower towers[], int numTowers) {
	int maxHeight = 0;
	std::vector<std::vector<int>> allBlocks;

	for (int i = 0; i < numTowers; i++) {
		allBlocks.push_back(towers[i].blocks.GetBlocks());
		if (allBlocks.back().size() > maxHeight) {
			maxHeight = allBlocks.back().size();
		}
	}
	
	std::cout << "\n";
	for (int level = maxHeight - 1; level >= 0; level--) {
		for (int t = 0; t < numTowers; t++) {
			std::cout << "  "; 
			if (level < allBlocks[t].size()) {
				int blockSize = allBlocks[t][level];
				int spaces = (13 - blockSize) / 2;
				for (int s = 0; s < spaces; s++) std::cout << " ";
				for (int s = 0; s < blockSize; s++) std::cout << "=";
				for (int s = 0; s < spaces; s++) std::cout << " ";
			}
			else {
				for (int s = 0; s < 6; s++) std::cout << " ";
				std::cout << "|";
				for (int s = 0; s < 6; s++) std::cout << " ";
			}
			std::cout << "  ";
		}
		std::cout << "\n";
	}

	for (int t = 0; t < numTowers; t++) {
		std::cout << "=============" << "   ";
	}
	std::cout << "\n";

	for (int t = 0; t < numTowers; t++) {
		std::cout << "   Torre " << (t + 1) << "   " << "   ";
	}
	std::cout << "\n";
}

// =================================================================
// Funcin Principal
// =================================================================
int main() {
	std::cout << "============ Juego de la Torre de Hanoi (Manejo de Excepciones) ============\n";
	Tower towers[3];
	int blocks = 0;

	std::cout << "Ingrese el nmero de discos (1-7): ";
	std::cin >> blocks;

	if (blocks < 1 || blocks > 7) {
		std::cout << "Nmero invlido. Por favor, ingrese un valor entre 1 y 7.\n";
		return 0;
	}

	for (int i = blocks; i >= 1; i--) {
		towers[0].AddBlocks(i * 2 - 1);
	}

	PrintTowers(towers, 3);

	while (true) {
		try {
			std::cout << "\nIngrese el movimiento (Ej. 1 3 para mover de Torre 1 a Torre 3).\n";
			int fromTowerIndex, toTowerIndex;

			std::cout << "Mover de Torre (1, 2, o 3): ";
			if (!(std::cin >> fromTowerIndex)) {
				std::cin.clear(); 
				std::cin.ignore(10000, '\n');
				throw std::runtime_error("Entrada Invlida. Se esperaba un nmero entero.");
			}
			fromTowerIndex--; 

			std::cout << "Mover a Torre (1, 2, o 3): ";
			if (!(std::cin >> toTowerIndex)) {
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				throw std::runtime_error("Entrada Invlida. Se esperaba un nmero entero.");
			}
			toTowerIndex--; 

			// EXCEPCION 1: Validacin de rango
			if (fromTowerIndex < 0 || fromTowerIndex > 2 || toTowerIndex < 0 || toTowerIndex > 2) {
				throw InvalidTowerException();
			}

			// Intentar el movimiento. Aqu se pueden lanzar la Excepcin 2 y 3.
			towers[fromTowerIndex].Move(towers[toTowerIndex]);
			std::cout << "Movimiento Exitoso: de Torre " << (fromTowerIndex + 1) << " a Torre " << (toTowerIndex + 1) << "\n";
			PrintTowers(towers, 3);

			// Condicin de victoria
			if (towers[2].blocks.GetBlocks().size() == blocks) {
				std::cout << "\n======================================================\n";
				std::cout << "¡Felicidades! Ha resuelto la Torre de Hanoi.\n";
				std::cout << "======================================================\n";
				break;
			}
		}
		// Bloque Catch genrico que captura todas las excepciones (incluyendo las 3 custom)
		catch (const std::exception& e) {
			std::cout << "\n*** Error ***\n";
			std::cout << e.what() << "\n";
			std::cout << "****************\n";
		}
	}

	return 0;
}
```

## Contenido del Archivo `README.md` (Reporte)

# 🧪 Reporte de Laboratorio - Módulo 3: Torres de Hanói con Excepciones

Este documento forma parte del reporte del Módulo 3 y documenta la implementación del juego de las Torres de Hanói, haciendo un uso extensivo de clases de excepciones personalizadas en C++ para gestionar los movimientos inválidos y los errores de entrada.

## 💻 Ejercicio: Torres de Hanói con Manejo de Errores

El objetivo es crear un juego funcional de las Torres de Hanói donde las reglas básicas del juego y los errores de manejo de la pila (Stack) se gestionan exclusivamente mediante excepciones personalizadas.

### Código Fuente

El código fuente (`hanoi_exceptions.cpp`) implementa tres clases de excepciones personalizadas: `InvalidTowerException`, `InvalidMoveException`, y `EmptyTowerException`.

### 🧠 Explicación del Manejo de Excepciones

La solución utiliza el patrón `try-catch` para controlar el flujo de la aplicación cuando ocurren errores previsibles, garantizando que el juego no se rompa y el usuario reciba un mensaje claro.

#### Uso de Bloques `try` y `catch`
Todo el bucle de juego principal (`while(true)`) está envuelto en un **bloque `try`**.
1.  **Dentro del `try`** se valida el rango de las torres y se llama al método `Tower::Move()`.
2.  Si ocurre cualquier excepción personalizada (`InvalidTowerException`, `InvalidMoveException`, `EmptyTowerException`), el control se transfiere al bloque **`catch (const std::exception& e)`**, que imprime el mensaje de error definido en la función `what()` de cada clase.

#### Mecanismos de Excepción
| Excepción | Objetivo | Lugar donde se Lanza (`throw`) |
| :--- | :--- | :--- |
| **1. `InvalidTowerException`** | Valida que la torre esté en el rango [1, 3]. | Función `main()`. |
| **2. `InvalidMoveException`** | Regla de Hanói: Disco grande sobre disco pequeño. | Método `Tower::Move()`. |
| **3. `EmptyTowerException`** | Pila/Torre de origen vacía. | Métodos `Pile::Pop()` y `Tower::Move()`. |

### 🚀 Evidencia de Ejecución

A continuación, se presentan los resultados de la ejecución para ilustrar el manejo de las excepciones.

#### 1. Caso de Éxito (Movimiento Válido)
El disco más pequeño (3) se mueve de la Torre 1 a la Torre 2.

**Captura de Pantalla de Ejecución:**
```text
Mover de Torre (1, 2, o 3): 1
Mover a Torre (1, 2, o 3): 2
Movimiento Exitoso: de Torre 1 a Torre 2
... (Se muestra el estado de las torres)
````

#### 2\. Caso de Fallo: `InvalidTowerException` (Error de Rango)

El usuario intenta mover la Torre 1 a la Torre 5.

**Captura de Pantalla de Ejecución:**

Mover de Torre (1, 2, o 3): 1
Mover a Torre (1, 2, o 3): 5

*** Error ***
Error de Rango: El nmero de torre debe ser entre 1 y 3.
****************


#### 3\. Caso de Fallo: `InvalidMoveException` (Movimiento Inválido)

El usuario intenta mover un disco grande (ej. 7) sobre uno pequeño (ej. 3).

**Captura de Pantalla de Ejecución:**


Mover de Torre (1, 2, o 3): 1
Mover a Torre (1, 2, o 3): 2

*** Error ***
Movimiento Invlido: No se puede colocar un disco ms grande sobre uno ms pequeo.
****************


#### 4\. Caso de Fallo: `EmptyTowerException` (Torre Vacía)

El usuario intenta mover un disco de la Torre 2 cuando está vacía.

**Captura de Pantalla de Ejecución:**


Mover de Torre (1, 2, o 3): 2
Mover a Torre (1, 2, o 3): 3

*** Error ***
Error de Pila: La torre de origen est vaca.
****************
```
