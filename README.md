# Note-detector

## Sobre o projeto
Este é um projeto para detecção de notas musicas através do som emitido.

## Especificações de harware

Componentes necessários para o projeto:
- Arduino Uno ou Nano
- Display de 7 segmentos
- Módulo microfone compatível e amplificado de forma apropriada para o Arduino
- Notebook e cabo USB (para alimentação)

Através do microfone captamos as ondas de som do instrumento e a partir de cálculos feitos no microcontrolador podemos identificar a nota musical tocada. Uma vez detectada, ela é exibida no display de 7 segmentos de forma apropriada.

## Especificações de software

O projeto foi executado em cima da plataforma Arduino IDE para facilitar a programação. Além disso, foi utilizado o algoritmo Fast Fourier Transformation (FFT) para detecção das notas a partir do valor analógico do microfone.

O algoritmo FFT, ou Transformada Rápida de Fourier, é uma versão otimizada da Transformada de Fourier Discreta, reduzindo sua complexidade computacional de O(N²) para O(N log N). Ele funciona com a abordagem de dividir para conquistar, decompondo a transformação em partes menores e resolvendo-as recursivamente. A implementação mais comum, conhecida como Cooley-Tukey, exige que o número de pontos seja uma potência de 2 e separa os coeficientes em partes pares e ímpares para facilitar os cálculos. O FFT é amplamente utilizado em diversas áreas, como processamento de sinais, compressão de dados e análise espectral, sendo essencial para aplicações em áudio, telecomunicações e processamento de imagens.

## Observações

Inicialmente o projeto contava com a funcionalidade de girar um motor DC de acordo com a nota tocada. Assim, pessoas com deficiência auditiva poderiam conseguir afinar instrumentos por meio da variação da vibração transmitida pelo motor. Porém, esta funcionalidade foi retirada.