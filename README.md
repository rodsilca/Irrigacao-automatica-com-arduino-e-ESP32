# Protótipo de Irrigação Automática com Arduino e ESP32 🌱💧
Bem-vindo ao repositório do Protótipo de Irrigação Automática, desenvolvido como um projeto acadêmico para a Feira de Tecnologia da Universidade FAMETRO em Manaus, 2024. Este projeto visa demonstrar uma solução simples e eficiente para automação agrícola, utilizando sensores e tecnologias acessíveis para monitorar e gerenciar o uso da água em sistemas de irrigação.

# 🔧 Descrição do Projeto
O protótipo utiliza um Arduino Uno como controlador principal, conectado a sensores e atuadores para monitorar condições ambientais e ativar uma bomba de água de forma automatizada. Um ESP32 é usado como interface de visualização e conectividade, permitindo que os dados coletados sejam acessados remotamente através de uma página web.

# Componentes Utilizados
• Arduino Uno: Controla sensores e relé para ativar a bomba de água.
• ESP32: Gerencia a comunicação web e exibe os dados via um servidor HTTP.
• Sensor de Umidade do Solo: Monitora a umidade do solo e envia leituras para o Arduino pela porta analógica.
• Sensor DHT11: Mede temperatura e umidade do ambiente.
• Relé de 1 Canal: Controla o acionamento da bomba de água.
• Bomba de Água: Irriga o solo quando os níveis de umidade estão abaixo do limiar definido.
• Fontes de Alimentação: Alimentam o Arduino, ESP32 e a bomba.

# Funcionamento do Sistema
1. O sensor de umidade do solo detecta os níveis de umidade e envia os dados para o Arduino.
2. O sensor DHT11 mede a temperatura e a umidade do ambiente, adicionando contexto à análise.
3. Quando a umidade do solo está abaixo de um valor predefinido, o Arduino aciona o relé, ativando a bomba de água para irrigação.
4. O Arduino envia os dados de umidade do solo e temperatura ao ESP32 via comunicação serial (portas TX/RX do Arduino conectadas às portas RX/TX do ESP32).
5. O ESP32 abre um servidor web, onde os dados podem ser visualizados em tempo real por meio de uma interface desenvolvida com HTML e CSS.
