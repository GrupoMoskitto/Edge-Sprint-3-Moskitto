# Projeto: Brinquedo com Painel Infantil de Atendimento com ESP32-C3 e FIWARE

## 🎯 Objetivo
O projeto é composto por um brinquedo interativo impresso em 3D no formato de **gatinho**, equipado com um ESP32-C3 SuperMini e um display OLED. O brinquedo é entregue à criança junto com o responsável e exibe a senha de atendimento da criança, informando quando chegar o atendimento, tudo de forma lúdica e acolhedora.

## 🧱 Arquitetura da Solução

### Camadas:

#### 1. IoT
- **Microcontrolador**: ESP32-C3 SuperMini
- **Atuador**: Display OLED (0.96" I2C SSD1306)
- **Comunicação**: Wi-Fi

#### 2. Back-end
- **Plataforma de IoT**: FIWARE
  - **Orion Context Broker**: Gerencia o contexto da aplicação
  - **Entidade**: `Display001` com atributo `value`

#### 3. Aplicação
- **Interface de Gerenciamento**: Painel web ou API para enviar atualizações. (Postman por enquanto)
- **Simulação**: Wokwi (link incluso)
- **Ferramenta para Diagrama**: draw.io

## 🗺️ Diagrama da Arquitetura
![Diagrama da Arquitetura](moskitto_arquitetura_1drawio.png)
