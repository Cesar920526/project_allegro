#include <allegro.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <sstream>

#include <fstream>
#include <nlohmann/json.hpp> // se incluye libreria json

#include "Clases/Imagenes.cpp"

BITMAP *buffer;
BITMAP *fondo;

using namespace std;
using namespace nlohmann; //para poder hacer uso del json

string str;

int menu();
int opciones();
void jugar(int basepal);

vector<Imagen> cargarJson(string categoria); //vector para cargar las imagenes alojadas en el json

int main()
{
    int opcionppal, salir, basepal;

    allegro_init(); //iniciar libreria alegro
    install_keyboard(); //instalar e iniciar el teclado
    install_mouse(); //instalar e iniciar el mouse

    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0); //tamaño de la consola de allegro
    show_mouse(screen); //mostrar mouse

    set_window_title("A PENSAR");

    buffer = create_bitmap(640, 480); //cargar el buffer *resevar un espacio de la memoria en el sistema

    fondo = load_bitmap("img/Fondo.bmp", NULL);

//menú con las opciones del juego
    while(salir != 3){

        opcionppal = menu();

        switch(opcionppal){

            case 1:
                jugar(opciones());
            break;

            case 2:

            break;
        }
    }

    draw_sprite(buffer,fondo,0,0); //dibuja el fondo
    masked_blit(fondo,buffer, 0,0,0,0,716,506); //carga el fondo
    blit(buffer,screen, 0,0,0,0,640,480); //carga el buffer
    clear(buffer);

    readkey();

    return 0;
}
END_OF_MAIN();

int menu(){ //esta funcion se encarga de mostrar las diferentes imagenes a paso de que el usuario va moviendo el cursor

    int i, click = 1, accion;

    BITMAP *buffer = create_bitmap(640,480);

    BITMAP *menu;
    BITMAP *menu1;
    BITMAP *menu2;
    BITMAP *menu3;

    menu = load_bitmap("img/Menu.bmp",NULL); //se carga el menu con su respectiva ruta
    menu1 = load_bitmap("img/Menu1.bmp",NULL);
    menu2 = load_bitmap("img/Menu2.bmp",NULL);
    menu3 = load_bitmap("img/Menu3.bmp",NULL);

    while(click == 1){

        i = 0;

        if(i == 0){
            draw_sprite(buffer,menu,0,0); //se muestra el munú sin resaltar las opciones
        }

        if(mouse_x > 30 && mouse_x < 320 && mouse_y > 180 && mouse_y < 240){ // se muestra opción del menu1 (jugar)
            draw_sprite(buffer,menu1,0,0);

            if(mouse_b & 1){//se asigna 1 a  mouse_b (click izquierdo)
                accion = 1;
                click = 0;
            }

            i = 1;
        }

        if(mouse_x > 30 && mouse_x < 490 && mouse_y > 250 && mouse_y < 320){ // se muestra opción del menu2 (creditos)
            draw_sprite(buffer, menu2, 0, 0);

            if(mouse_b & 1){
                accion = 2;
                click = 0;
            }

            i = 2;
        }

        if(mouse_x > 30 && mouse_x < 255 && mouse_y > 330 && mouse_y < 410){// se muestra opción del menu3 (salir)
            draw_sprite(buffer,menu3,0,0);

            if(mouse_b & 1){
                accion = 3;
                click = 0;
            }

            i = 3;
        }

        blit(buffer, screen, 0, 0, 0, 0, 640, 480);
    }

    clear(buffer);
    return accion;//retorna la acción escogida

}

int opciones(){ //esta funcion se encarga de mostrar las diferentes imagenes a paso de que el usuario va moviendo el cursor en opciones

    int i, click = 1, basepal;

    buffer = create_bitmap(640, 480);

    BITMAP *fondo_opciones;
    BITMAP *fondo_opciones1;
    BITMAP *fondo_opciones2;
    BITMAP *fondo_opciones3;

    fondo_opciones = load_bitmap("img/Menu_Opciones.bmp", NULL);
    fondo_opciones1 = load_bitmap("img/Menu_Opciones1.bmp", NULL);
    fondo_opciones2 = load_bitmap("img/Menu_Opciones2.bmp", NULL);
    fondo_opciones3 = load_bitmap("img/Menu_Opciones3.bmp", NULL);

    while(click == 1){

        i = 0;

        if(i == 0){
            draw_sprite(buffer, fondo_opciones, 0, 0);//se muestra el munú sin resaltar las opciones
        }

        if(mouse_x > 45 && mouse_x < 215 && mouse_y > 225 && mouse_y < 275){// se muestra opción de opciones (facil)
            draw_sprite(buffer, fondo_opciones1, 0, 0);

            if(mouse_b & 1){//se asigna 1 a  mouse_b (click izquierdo)
                click = 0;
                basepal = 1;
            }

            i = 1;
        }

        if(mouse_x > 45 && mouse_x < 280 && mouse_y > 305 && mouse_y < 375){// se muestra opción de opciones (medio)
            draw_sprite(buffer, fondo_opciones2, 0, 0);

            if(mouse_b & 1){
                click = 0;
                basepal = 2;
            }

            i = 2;
        }

        if(mouse_x > 45 && mouse_x < 265 && mouse_y > 400 && mouse_y < 460){// se muestra opción de opciones (dificil)
            draw_sprite(buffer, fondo_opciones3, 0, 0);

            if(mouse_b & 1){
                click = 0;
                basepal = 3;
            }

            i = 3;
        }

        blit(buffer, screen, 0, 0, 0, 0, 640, 480);
    }

    return basepal;//retornaa la opción escogida
}

void jugar(int basepal){

    char respuesta;

    BITMAP *abecedario[26] = {}; //arreglo de bitmap donde estan contenidas las letras del abecedario

    for(int i = 0 ; i < 26 ; i++){ //se cargan las imagenes del abecedario

        str = "img/ ";
        str[4] = i+65; //carácteres en código ascii
        str += ".bmp";

        abecedario[i] = load_bitmap(str.c_str(), NULL);
    }

    BITMAP *numeros[11] = {};//arreglo de # de vidas

    for(int i = 0 ; i < 11 ; i++){//se cargan las imagenes de vidas

        str = "img/ ";
        int code = i+48;

        str[4] = (code != 58) ? code : 49;

        str += (code == 58) ? "0.bmp" : ".bmp";

        numeros[i] = load_bitmap(str.c_str(), NULL);
    }

    //se carga la información alojada en el json con sus niveles
    vector<Imagen> imagenesFacil = cargarJson("Facil");
    vector<Imagen> imagenesNormal = cargarJson("Normal");
    vector<Imagen> imagenesDificil = cargarJson("Dificil");

    BITMAP *buffer = create_bitmap(640, 480);
    BITMAP *fondo_niveles;
    BITMAP *x;
    BITMAP *digitar_letra;
    BITMAP *intentos;

    fondo_niveles = load_bitmap("img/Fondo_niveles.bmp", NULL);
    x = load_bitmap("img/X1.bmp", NULL);
    digitar_letra = load_bitmap("img/Digitar_Letra.bmp", NULL);
    intentos = load_bitmap("img/Intentos.bmp", NULL);

    while(respuesta != 'n'){

        int j = 0, vidas = 10, t = 0;
        string temporal, palgen;


        srand(time(0)); //inicializar random
        j = 0 + rand() % 5;

        switch(basepal){ //return de la función opciones(facil, medio, dificil)

            case 1: //caso facil
                temporal = imagenesFacil[j].getTexto();
                draw_sprite(buffer, fondo_niveles, 0, 0);
                masked_blit(load_bitmap(imagenesFacil[j].getUrl().c_str() , NULL), buffer, 0, 0, 205, 100, 260, 194);
            break;
            case 2://caso medio
                temporal = imagenesNormal[j].getTexto();
                draw_sprite(buffer, fondo_niveles, 0, 0);
                masked_blit(load_bitmap(imagenesNormal[j].getUrl().c_str() , NULL), buffer, 0, 0, 205, 100, 260, 194);
            break;
            case 3://caso dificil
                temporal = imagenesDificil[j].getTexto();
                draw_sprite(buffer, fondo_niveles, 0, 0);
                masked_blit(load_bitmap(imagenesDificil[j].getUrl().c_str() , NULL), buffer, 0, 0, 205, 100, 260, 194);
            break;
        }


        for(int i = 0; i < temporal.size(); i++){
            palgen += " ";
            masked_blit(x, buffer, 0, 0, 25+i*60, 400, 60, 60);//carga las x de acuerdo al tamaño de la palabra
        }

        while(vidas > 0 && t == 0){ //ciclo para realizar los intentos al ingresar un caracter

            masked_blit(digitar_letra, buffer, 0, 0, 190, 325, 293, 60);
            masked_blit(intentos, buffer, 0, 0, 15, 25, 472, 58);
            masked_blit(numeros[vidas], buffer, 0, 0, 500, 25, 60, 60);//subindices del arreglo de numeros en posición vidas
            blit(buffer, screen, 0, 0, 0, 0, 640, 480);

            char letra = readkey();
            bool perder = true;

            for(int i = 0; i < temporal.size(); i++){

                if(tolower(letra) == tolower(temporal[i])){//se valida que la letra escrita sea la correcta
                    perder = false;
                    masked_blit(abecedario[tolower(letra) - 97], buffer, 0, 0, 25+i*60, 400, 60, 60);

                    palgen[i] = letra;
                }
            }

            if(palgen == temporal){

                BITMAP *ganaste = load_bitmap("img/Ganaste.bmp", NULL);
                draw_sprite(buffer, ganaste, 0, 0);
                blit(buffer, screen, 0, 0, 0, 0, 640, 480);

                respuesta = readkey();//se asigna a respuesta la letra digitada
                rest(50);
                t = 1;
            }

            if(perder){//disminuye vida
               vidas--;
            }


            if(vidas == 0){
                BITMAP *ganaste = load_bitmap("img/Ganaste.bmp", NULL);
                draw_sprite(buffer, ganaste, 0, 0);
                blit(buffer, screen, 0, 0, 0, 0, 640, 480);
                respuesta = readkey();

                t = 1;
            }
        }
        blit(buffer,screen, 0,0,0,0,640,480);
    }
}

//Se carga la informacion de las imagenes
//almacenadas en un archivo Json
//dependiendo de la categoria indicada
vector<Imagen> cargarJson(string categoria){


    vector<Imagen> images;

    json imagenes;
    ifstream people_file("imagenes.json", ifstream::binary);
    people_file >> imagenes;

    for (json element : imagenes["imagenes"][categoria]){
        images.push_back( Imagen(element["url"],element["texto"]) );
    }

    return images;
}
