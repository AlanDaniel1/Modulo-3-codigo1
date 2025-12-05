# 🧪 Reporte de Laboratorio - Módulo 3: Manejo de Excepciones en C++

Este repositorio contiene la evidencia y documentación del ejercicio práctico del Módulo 3, centrado en el manejo de excepciones mediante los bloques `try` y `catch` en C++.

## 💻 Ejercicio: Control de División por Cero

El objetivo de este ejercicio es implementar un mecanismo de manejo de excepciones para prevenir y reportar un error cuando el usuario intenta realizar una división por cero, un caso que causa un comportamiento indefinido o un fallo de ejecución.

### Código Fuente

El siguiente código (`div_by_zero.cpp`) utiliza un bloque `try` para verificar el divisor antes de la operación. Si el divisor es `0`, se lanza una excepción de tipo `bool`.

```cpp
#include <iostream>

const bool divZero = true;

int main()
{
	int a = 8, b = 0, c = 0;
	
	std::cout << "Ingrese un divisor para a=" << a << ": \n";
	std::cin >> b;

	try {
		if (b == 0) {
			throw divZero;
		}
		c = a / b;
		std::cout << "Resultado de la división (c = a/b): ";
	}
	catch (bool isZero)
	{
		std::cout << "¡Error! Su entrada no es válida. No se puede dividir por cero. \n";
	}
    
	std::cout << c << "\n"; 

	return 0;
}
```

### 🧠 Explicación del Manejo de Excepciones

**Objetivo:** El programa busca realizar la división de un número (`a=8`) entre un divisor (`b`) ingresado por el usuario, asegurando que la operación sea segura.

**Mecanismo de Excepción:**

1.  **Bloque `try`:** Envuelve la lógica de validación y la operación de división (`c = a / b`). Si el valor de `b` es `0`, la instrucción `throw divZero;` se ejecuta, lanzando una excepción de tipo `bool`.

2.  **Bloque `catch`:** Captura específicamente la excepción de tipo `bool` (`catch (bool isZero)`). Cuando se lanza la excepción, el control del programa salta inmediatamente a este bloque, imprimiendo un mensaje de error legible por el usuario.

3.  **Flujo Normal:** Si `b` no es `0`, el bloque `try` completa la división, y el bloque `catch` es ignorado, permitiendo que el programa continúe normalmente.

Este uso del `try-catch` evita un fallo catastrófico y permite un manejo limpio y controlado de un error previsible.

### 🚀 Evidencia de Ejecución

#### 1\. Caso de Éxito (Sin Excepción)

Cuando el usuario ingresa un valor diferente de cero (ej. `4`), el programa ejecuta la división normalmente.

**Captura de Pantalla de Ejecución:**

```text
Ingrese un divisor para a=8: 
4
Resultado de la división (c = a/b): 2
```

#### 2\. Caso de Fallo (Manejo de Excepción)

Cuando el usuario ingresa `0`, se lanza la excepción y se ejecuta el bloque `catch`.

**Captura de Pantalla de Ejecución:**

```text
Ingrese un divisor para a=8: 
0
¡Error! Su entrada no es válida. No se puede dividir por cero. 
0
```
