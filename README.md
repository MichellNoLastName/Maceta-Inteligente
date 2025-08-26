# 🌱 Maceta Inteligente para el Crecimiento de un Crisantemo

Este proyecto fue desarrollado como parte de la asignatura **Proyecto Integrador**, con el objetivo de diseñar y programar una **maceta inteligente** que monitorea y controla las condiciones ambientales necesarias para el óptimo crecimiento de un **crisantemo**.  

La maceta integra sensores, un sistema de riego automático, control de luz artificial y una interfaz LCD para mostrar información en tiempo real, todo gestionado mediante un **Arduino**.

---

## 🚀 Características principales

- 📊 **Monitoreo de temperatura y humedad ambiental** mediante un sensor **DHT11**.  
- 💧 **Control automático de riego** con bomba de agua y sensores de nivel de tanque.  
- ☀️ **Control de fotoperiodo** mediante un sistema de iluminación artificial, activado según el ciclo programado para la planta.  
- 🔔 **Alarmas sonoras** (buzzer) para advertencias de exceso/falta de agua, luz o temperatura.  
- 🖥️ **Pantalla LCD 20x4 con I2C**, que muestra:
  - Fecha y hora (RTC DS1307).  
  - Temperatura y humedad.  
  - Estado del tanque y la luz.  
  - Menú de configuración y selección de planta.  
- 🌼 **Base de datos de parámetros óptimos** para 3 plantas (incluyendo el crisantemo), con rangos de temperatura, humedad y fotoperiodo.  

---

## 🛠️ Componentes utilizados

- **Arduino UNO**  
- **Sensor DHT11** → temperatura y humedad ambiental  
- **Sensor de humedad de suelo** (analógico)  
- **Sensores de nivel de agua** (mínimo y máximo)  
- **Bomba de agua** + relevador para riego automático  
- **LED / lámpara de cultivo** para control de luminosidad  
- **Pantalla LCD 20x4 con módulo I2C**  
- **Módulo RTC DS1307** → control de fecha y hora  
- **Buzzer piezoeléctrico**  
- **Botones de navegación** (izquierda, derecha, enter)  

---

## 📋 Funcionalidades del software

1. **Selección de planta al inicio** (Crisantemo, Rosa de alabastro o Petunia).  
2. **Adquisición de datos en tiempo real** (temperatura, humedad, nivel de agua, fotoperiodo).  
3. **Acciones automáticas**:
   - Activa la bomba de riego si la humedad del suelo es baja.  
   - Activa o apaga la luz según el ciclo fotoperiódico de la planta seleccionada.  
   - Alarmas en caso de exceso de temperatura, sequedad extrema o falta de agua en el tanque.  
4. **Interfaz de usuario en LCD** con menús:
   - Estado actual del sistema.  
   - Parámetros de la planta seleccionada.  
   - Información del sustrato recomendado.  
   - Control manual de la luz.  
   - Activar o desactivar modo silencioso.  
5. **Uso de RTC DS1307** para el control exacto de horarios.  

---

## 📂 Estructura del código

El programa está desarrollado en **C++ para Arduino**, con las siguientes secciones principales:

- Configuración de **pines y sensores**.  
- Inicialización de **LCD y RTC**.  
- **Menú de selección de planta** al inicio.  
- **Loop principal**:
  - Lectura de sensores.  
  - Actualización de pantalla LCD.  
  - Ejecución de alarmas y acciones automáticas.  
- Funciones auxiliares:
  - `read_ds1307()` → lectura del reloj en tiempo real.  
  - `bcd2bin()` → conversión de valores BCD.  
  - `antireboot()` → debounce de botones.  

---

## 📊 Parámetros configurados para el Crisantemo

- 🌡️ **Temperatura óptima**: 10°C – 32°C  
- 💧 **Humedad óptima del suelo**: 65% – 70%  
- ☀️ **Fotoperiodo**: 7:00 a 18:00  
- 🌱 **Sustrato recomendado**:  
  - 2/3 tierra de jardín  
  - 1/3 composta  

---

## 📸 Ejemplo del flujo de trabajo

1. Al encender el sistema, el usuario selecciona la planta en el menú LCD.  
2. El sistema comienza a **monitorear los sensores** y controla automáticamente el riego y la luz.  
3. Si la planta está en riesgo (frío, calor, exceso de agua, falta de tanque), se activa el **buzzer y mensajes en LCD**.  
4. El usuario puede navegar en el menú para ver información o activar/desactivar funciones manualmente.  

---

## 📌 Futuras mejoras

- Comunicación con una **aplicación móvil** vía Bluetooth o WiFi.  
- Registro de datos en **tarjeta SD** para análisis histórico.  
- Implementación de un **modo automático de aprendizaje** que ajuste parámetros según el crecimiento real de la planta.  

---

## 👨‍💻 Autores

Este proyecto fue desarrollado por estudiantes de la asignatura **Proyecto Integrador**, con el objetivo de aplicar conocimientos en:  
- Programación de microcontroladores.  
- Electrónica y sensores.  
- Automatización y control ambiental.  

---
📖 **Asignatura:** Proyecto Integrador  
🌼 **Planta principal de estudio:** Crisantemo  
⚡ **Tecnologías usadas:** Arduino, C++, Electrónica de control  

---
