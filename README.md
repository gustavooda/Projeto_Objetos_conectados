# Projeto Arduino com Sensores, LED e MQTT

Este é um projeto Arduino que combina o uso de sensores PIR (Passive Infrared) para detectar movimento, uma fita de LED RGB para exibir diferentes cores e o protocolo MQTT (Message Queuing Telemetry Transport) para controle remoto das luzes.

## Componentes Necessários

- Arduino (qualquer modelo compatível)
- Sensor PIR
- Fita de LED RGB (com 4 vias ou 2 vias)
- Módulo Wi-Fi (se necessário)
- Fonte de energia externa (se necessário)

## Configuração e Funcionamento

1. Conecte o Arduino ao seu computador usando um cabo USB.
2. Conecte o sensor PIR aos pinos digitais do Arduino.
3. Conecte a fita de LED RGB aos pinos PWM do Arduino.
4. Se estiver usando um módulo Wi-Fi, conecte-o ao Arduino.
5. Se estiver usando uma fonte de energia externa, conecte-a ao Arduino.
6. Certifique-se de ter as bibliotecas necessárias instaladas (por exemplo, PubSubClient para MQTT).
7. Configure corretamente as informações do servidor MQTT (endereço, porta, usuário, senha) no código.
8. Carregue o código no Arduino usando a IDE do Arduino.

O código do projeto permite que, ao detectar movimento através do sensor PIR, a fita de LED exiba uma determinada cor. Através do protocolo MQTT, é possível enviar comandos para ligar e desligar as luzes remotamente.

## Como Contribuir

Se você tiver sugestões de melhorias ou correções para o projeto, sinta-se à vontade para abrir uma issue ou enviar um pull request. Sua contribuição é bem-vinda!

## Licença

Este projeto é distribuído sob a licença [MIT](LICENSE). Sinta-se livre para usá-lo e modificá-lo conforme suas necessidades.

