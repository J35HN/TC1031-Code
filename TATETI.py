"""
Juego TATETI - Coursera: Estructura de Datos en Python 
Autor: Jeshua Nava Avila
Fecha: 21/02/2021
"""
def print_tabla(tabla):
    "Imprime la tabla de juego"
    print("   A    B    C")
    for fila in range(3):
        print(fila , end="")
        for columna in range(3):
            print(tabla[fila][columna],end="")
        print()

def identificacion_x_y(x, y):
    "Identifica si x o y es letra o número"
    num = 0
    for z in "abc":
        if x == z: 
            x = num 
            return int(y), x
        if y == z:
            y = num
            return int(x), y
        num += 1

def movida(tabla, posiciones, jugador = 1):
    "Ingresa el movimiento del jugador en la tabla"
    while True:
        print_tabla(tabla)
        print("Por favor ingrese la posición de su ficha")
        movimiento = input().lower()    
        if movimiento in posiciones:
            x = movimiento[:1]
            y = movimiento[1:]
            for i in range(2):
                if i == 0:
                    reemplazo = "{}{}".format(x,y)
                    posiciones = posiciones.replace(reemplazo, "")
                else:
                    reemplazo = "{}{}".format(y,x)
                    posiciones = posiciones.replace(reemplazo, "")
            x, y = identificacion_x_y(x, y) 
            if jugador == 1:
                tabla[x][y] = ["X"]
                return tabla, posiciones 
            else:
                tabla[x][y] = ["O"]
                return tabla, posiciones 
        else:
            print("El movimiento que ingreso no es válido")

def ganar(tabla):
    "Verifica si un jugador a ganado, o por si han empatado"
    esp_libres = 0
    DerX, DerO, IzqX, IzqO = 0, 0, 0, 0
    for i in range(3):
        esp_libres += tabla[i].count(["_"])
        FilX, FilO, ColX, ColO = 0, 0, 0, 0
        FilX = tabla[i].count(["X"])
        FilO = tabla[i].count(["O"])
        for e in range(3):
            if tabla[e][i] == ["X"]: ColX += 1
            if tabla[e][i] == ["O"]: ColO += 1
            if i == e and tabla[i][e] == ["X"]:
                DerX += 1
                if i == 1 and e == 1 and tabla[i][e] == ["X"]:
                    IzqX += 1
            if i == e and tabla[i][e] == ["O"]:
                DerO += 1
                if i == 1 and e == 1 and tabla[i][e] == ["O"]:
                    IzqO += 1
            if i == 2 and e == 0 and tabla[i][e] == ["X"]:
                IzqX += 1
            if i == 2 and e == 0 and tabla[i][e] == ["O"]:
                IzqO += 1
            if i == 0 and e == 2 and tabla[i][e] == ["X"]:
                IzqX += 1
            if i == 0 and e == 2 and tabla[i][e] == ["O"]:
                IzqO += 1
        if FilX == 3 or ColX == 3: return 1
        if DerX == 3 or IzqX == 3: return 1
        if FilO == 3 or ColO == 3: return 2
        if DerO == 3 or IzqO == 3: return 2
    if esp_libres == 0: return -1
    return 0 

tabla = [
[ ["_"], ["_"], ["_"] ],
[ ["_"], ["_"], ["_"] ],
[ ["_"], ["_"], ["_"] ]
]

posiciones = """
0a/a0/1a/a1/2a/a2
0b/b0/1b/b1/2b/b2
0c/c0/1c/c1/2c/c2
"""
ganador = 0
player = 1
while True: 
    jugador = player
    tabla, posiciones = movida(tabla, posiciones, jugador)
    ganador = ganar(tabla)
    if ganador == 1:
        print_tabla(tabla)
        print("GANO EL JUGADOR 1")
        break
    elif ganador == 2:
        print_tabla(tabla)
        print("GANO EL JUGADOR 2")
        break
    elif ganador == -1:
        print_tabla(tabla)
        print("EMPATE")
        break
    if player == 1:
        player = 2
    else:
        player = 1