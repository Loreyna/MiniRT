un venctor simplemente guarda cuánto de mueves en cada eje
no dice dónde estas, dice cómo moverte.

La cámara esta en (0, 0, 0) la esfera en (5, 2, 10)
¿Cómo llegas desde la cámara hasta la esfera?
(X) 5 a la derecha
(Y) 2 arriba
(Z) 10 hacia delante.
Ese movimiento es el vector. (5, 2, 10)
Y este es exactamente el tipo de cálculo que harás continuamente cn miniRT

Un vector, por lo tanto, es el desplazamiento necesario para ir de un sitio
a otro.
La cámara (0, 0, 0) es el punto de referencia para lanzar los rayos, pero no para todas las operaciones matemáticas.

La formula para calcular el vector siempre es DESTINO - ORIGEN

En miniRT siempre hay dos tipos de rayo.
-1 Rayo principal (Sale de la cámara)
    sirve para descubrir qué objeto ve cada píxel.
2- Rayo de sombra (Sale del punto de impacto)
    Sirve para saber si la luz llega o está bloqueada.

La cámara es solo el punto desde donde "miramos" la escena. El ray tracer
dispara rayos desde la cámara porque es una forma mucho más eficiente de calcular la imagen.