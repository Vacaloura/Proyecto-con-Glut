# Proyecto OpenGL - Templo Japonés

Proyecto de gráficos 3D desarrollado con OpenGL y GLUT que representa una escena de un templo japonés tradicional.

## 📋 Descripción

Este proyecto implementa una escena 3D interactiva que incluye:
- Templo japonés tradicional
- Puerta Torii (portal característico japonés)
- Camino de acceso
- Árboles decorativos
- Sistema de iluminación avanzado con múltiples luces
- Texturas realistas
- Efectos de niebla atmosférica

## 🖼️ Capturas de Pantalla

### Vista Frontal
![Vista del Templo](Imagen1.png)

### Vista superior
![Puerta Torii](Imagen2.png)

### Vista lateral
![Entorno Completo](Imagen3.png)

## 🛠️ Tecnologías Utilizadas

- **OpenGL**: API gráfica para renderizado 3D
- **GLUT** (OpenGL Utility Toolkit): Gestión de ventanas y eventos
- **C/C++**: Lenguaje de programación

## 📁 Estructura del Proyecto

```
Proyecto-con-Glut/
├── glut.h              # Cabecera principal de GLUT
├── examinar.h          # Sistema de cámara y navegación
├── modelado.h          # Definición de modelos 3D
├── material.h          # Gestión de materiales y texturas
├── luces.h             # Sistema de iluminación
└── [archivos fuente]   # Implementación (.c/.cpp)
```

## 🎮 Controles y Navegación

El proyecto incluye tres modos de navegación:

- **WALK**: Modo caminar
- **EXAMINAR**: Modo examinación
- **FLY**: Modo vuelo

### Controles de Teclado
Utiliza el teclado para navegar por la escena (los controles específicos dependen de la implementación).

## ⚙️ Características Técnicas

### Sistema de Iluminación
- Iluminación ambiente, difusa y especular

### Sistema de Texturas
- Soporte para hasta 10 texturas simultáneas
- Formato de texturas: TGA
- Resolución: 256x256 píxeles
- Mapeo de texturas en superficies 3D

### Sistema de Cámara
- Conversión de grados a radianes
- Posición del observador ajustable
- Punto de interés configurable
- Tamaño de ventana: 500x500 píxels (configurable)

## 🏗️ Componentes de la Escena

### Suelo
Superficie base de la escena con textura.

### Puerta Torii
Portal tradicional japonés que marca la entrada al espacio sagrado.

### Templo
Estructura principal del edificio con arquitectura japonesa tradicional.

### Camino
Sendero que guía hacia el templo.

### Árboles
Elementos decorativos de vegetación.

### Caja Envolvente
Delimitación del espacio de la escena.

## 📄 Licencia
Este proyecto es de código abierto y está disponible para fines educativos.
