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
La cámara (0, 0, 0) es el punto de referencia para lanzar los rayos, pero no
para todas las operaciones matemáticas.

La formula para calcular el vector siempre es DESTINO - ORIGEN

En miniRT siempre hay dos tipos de rayo.
- Rayo principal (Sale de la cámara)
    sirve para descubrir qué objeto ve cada píxel.
- Rayo de sombra (Sale del punto de impacto)
    Sirve para saber si la luz llega o está bloqueada.

La cámara es solo el punto desde donde "miramos" la escena. El ray tracer
dispara rayos desde la cámara porque es una forma mucho más eficiente de
calcular la imagen.

- la cámara diapara el rayo.
¿Este rayo toca algún objeto?
- se la respuesta es si, pintamos un pixel.
- si no, pintamos el color de fondo.
¿Cómo representamos el rayo?
Solo se necesita dos cosas.
- el punto desde donde empieza.
- una dirección.                 {RAYO = ORIGEN + DIRECCIÓN}

"Un rayo es una línea infinita que sale de la cámara en una dirección.
t es simplemente la distancia recorrida sobre esa línea. Cuando un objeto
es alcanzado, calculamos el valor de t donde ocurre el impacto y,
con ese valor, obtenemos el punto exacto de colisión."

origin (2,3,4) direction (0,1,0) ¿dónte esta el rayo para t? 
direction * 5 = (0,5,0)
origin + (0,5,0) = (2,8,4) "Ese es el punto del rayo"