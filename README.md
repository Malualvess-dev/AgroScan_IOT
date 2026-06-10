# 🌾 AgroScan IoT

Sistema de monitoramento agrícola desenvolvido com ESP32 utilizando sensores simulados no Wokwi, integração com API Spring Boot e visualização dos dados em dashboard web.

---

## 📖 Sobre o Projeto

O AgroScan IoT é uma solução baseada em Internet das Coisas (IoT) capaz de coletar dados ambientais, realizar análises básicas e enviar informações para uma API REST desenvolvida em Java Spring Boot.

O sistema utiliza um ESP32 para capturar informações dos sensores, processar os dados localmente e enviá-los para uma aplicação web responsável pelo armazenamento e exibição das informações.

---

## 🎯 Objetivo

Desenvolver um sistema capaz de:

- 🌡️ Monitorar temperatura ambiente
- 💧 Monitorar umidade do ar
- 🌱 Monitorar umidade do solo
- 🔍 Classificar produtos agrícolas automaticamente
- 🚨 Gerar alertas visuais e sonoros
- 🌐 Enviar dados para uma API REST
- 📊 Exibir informações em dashboard web

---

## 🚀 Tecnologias Utilizadas

- ESP32
- Arduino C++
- Wokwi
- WiFi
- HTTPClient
- Ngrok
- Spring Boot
- HTML
- CSS
- JavaScript

---

## 🔧 Componentes Utilizados

### 🖥️ ESP32

Responsável pelo processamento dos dados e comunicação com a API.

### 🌡️ Sensor DHT22

Utilizado para monitorar:

- Temperatura
- Umidade do ar

### 🌱 Sensor de Umidade do Solo

Responsável por identificar as condições do solo.

### 🔍 Scanner Analógico

Utilizado para simular a identificação de categorias agrícolas.

Categorias identificadas:

- Solo
- Planta
- Verdura
- Fruta
- Legume

### 📺 Display OLED SSD1306

Exibe as informações coletadas em tempo real.

### 🟢 LED Verde

Indica funcionamento normal.

### 🔴 LED Vermelho

Indica situação de alerta.

### 🔊 Buzzer

Responsável pelos alertas sonoros.

---

## ⚙️ Funcionalidades

✅ Leitura de temperatura

✅ Leitura de umidade do ar

✅ Leitura de umidade do solo

✅ Classificação automática

✅ Exibição em display OLED

✅ Alertas visuais

✅ Alertas sonoros

✅ Comunicação com API REST

✅ Dashboard em tempo real

---

## 🔄 Fluxo do Sistema

```text
Sensores
   │
   ▼
ESP32
   │
   ▼
Processamento
   │
   ▼
Display OLED
   │
   ▼
Envio HTTP
   │
   ▼
API Spring Boot
   │
   ▼
Dashboard Web
```

---

## 📦 Exemplo de Dados Enviados

```json
{
  "categoria": "Verdura",
  "temperatura": 24.00,
  "umidadeAr": 40.00,
  "umidadeSolo": 51
}
```

---

## 🌐 Comunicação com a API

Os dados são enviados para a API através de requisições HTTP POST.

Exemplo de endpoint:

```http
POST /scanner/dados
```

URL utilizada durante os testes:

```text
http://SEU-LINK-NGROK/scanner/dados
```

---

## 📁 Estrutura do Repositório

```text
AgroScan-IoT
│
├── codigo
│   └── sketch.ino
│
├── docs
│   ├── circuito.png
│   ├── dashboard.png
│   ├── monitor-serial.png
│   └── ngrok.png
│
├── README.md
├── diagram.json
└── libraries.txt
```

---

## ▶️ Como Executar

### 1. Executar a API

Inicie a aplicação Spring Boot localmente.

### 2. Abrir o Ngrok

```bash
ngrok http 8080 --scheme=http
```

### 3. Copiar a URL gerada

Exemplo:

```text
http://xxxxxxxx.ngrok-free.dev
```

### 4. Atualizar o código do ESP32

```cpp
const char* apiUrl = "http://SEU-LINK-NGROK/scanner/dados";
```

### 5. Executar o projeto no Wokwi

Inicie a simulação e acompanhe o Monitor Serial.

---

## 📊 Resultados Esperados

### Monitor Serial

```text
WiFi conectado
HTTP Code: 200
```

### Ngrok

```text
POST /scanner/dados 200
```

### Dashboard

```text
Atualização automática dos dados recebidos
```

---

## 📸 Demonstrações

### Circuito ESP32

Imagem disponível em:

```text
docs/circuito.png
```

### Dashboard

Imagem disponível em:

```text
docs/dashboard.png
```

### Comunicação com API

Imagem disponível em:

```text
docs/ngrok.png
```

### Monitor Serial

Imagem disponível em:

```text
docs/monitor-serial.png
```

---

## 🏆 Principais Recursos

- 🌡️ Monitoramento ambiental
- 🌱 Análise de solo
- 🔍 Classificação inteligente
- 📺 Interface OLED
- 🚨 Sistema de alertas
- 🌐 Integração com API REST
- 📊 Dashboard em tempo real
- ☁️ Comunicação externa utilizando Ngrok

---

## 📌 Projeto Acadêmico

Projeto desenvolvido para aplicação dos conceitos de Internet das Coisas (IoT), integração entre dispositivos embarcados e APIs REST, comunicação em rede e monitoramento em tempo real.
