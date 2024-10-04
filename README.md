# Sistema de Monitoramento de Temperatura, Umidade e Luminosidade com ESP32
  Este projeto implementa um sistema básico de monitoramento ambiental usando um ESP32, um sensor DHT22 (temperatura e umidade) e um sensor LDR (luminosidade). Os dados coletados são enviados para um broker MQTT e podem ser visualizados em um aplicativo cliente MQTT.


-> Funcionalidades:
- Leitura de temperatura e umidade: O sensor DHT22 mede a temperatura e a umidade do ambiente.
- Leitura de luminosidade: O sensor LDR detecta a intensidade da luz ambiente.
- Mapeamento de luminosidade: A leitura do LDR é convertida para um valor de porcentagem (0-100%) para facilitar a interpretação.
- Publicação MQTT: Os dados dos sensores são publicados em tópicos específicos em um broker MQTT.
- Reconexão automática: O ESP32 tenta se reconectar automaticamente ao WiFi e ao broker MQTT em caso de desconexão.


-> Material Necessário:
- Placa ESP32
- Sensor DHT22
- Sensor LDR
- Jumpers
- Placa de prototipagem (opcional)


-> Esquema de Conexão:
  Conecte os componentes ao ESP32 conforme o diagrama abaixo:
ESP32
      +-----+
      |     |
   D4 | DHT |
      |     |
      +-----+
      |     |
  3.3V| VCC |
      |     |
   GND| GND |
      +-----+
      |     |
  LDR | A0  |
      |     |
      +-----+


-> Instruções de Configuração:
- Configurações do Projeto:
  + Abra o arquivo .ino do projeto no Arduino IDE.
  + Altere as seguintes constantes no código de acordo com o seu ambiente:
    >> default_SSID: Nome da sua rede WiFi.
    >> default_PASSWORD: Senha da sua rede WiFi.
    >> default_BROKER_MQTT: Endereço IP ou nome de domínio do seu broker MQTT.
    >> default_BROKER_PORT: Porta do seu broker MQTT.
    >> topicPrefix: Prefixo usado para os tópicos MQTT.

- Carregar o Código:
  + Compile e carregue o código para o seu ESP32 usando o Arduino IDE.


-> Visualizando os Dados:
- Aplicativo MQTT:
  + Instale um aplicativo cliente MQTT no seu smartphone ou computador (ex: MQTT Dash).
  + Configure o aplicativo com as mesmas credenciais do broker MQTT que você definiu no código (endereço, porta).
  + Inscrever-se nos Tópicos:
    No aplicativo MQTT, inscreva-se nos seguintes tópicos para receber os dados dos sensores:
    >> /TEF/device001/ldr: Luminosidade (0-100%).
    >> /TEF/device001/dht/temperatura: Temperatura em graus Celsius.
    >> /TEF/device001/dht/umidade: Umidade relativa em porcentagem.


-> Observações:
- Este código foi desenvolvido para o ESP32, mas pode ser adaptado para outras placas com suporte ao framework WiFi do Arduino.
- Certifique-se de ter as bibliotecas WiFi.h, PubSubClient.h e DHT.h instaladas no seu Arduino IDE.
- Ajuste o tempo de atraso (delay) no loop principal do código, se necessário, para controlar a frequência de leitura e publicação dos dados.

-> Grupo: InnotechHub
- Integrantes:
  + Davi Vieira (556798) 
  + Felipe Alamino (558819) 
  + Luca Monteiro (556906) 
  + Pedro Sampaio (555613)
  + Yuri Lopes (555522)
