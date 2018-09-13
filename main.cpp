#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
//#include <mpi.h>

using namespace std;

typedef struct Nodo{
    int numero;
    bool esFijo;
    Nodo* link;
};
typedef Nodo* Lista;

Lista matriz[9][9];

int ConvierteANumero(char valor){
	int n = (int)valor - 48;
    return n;
}

bool esNumero(char valor){
    if(valor>47 && valor<58){
        return true;
    }
    else{
        return false;
    }
}

void mostrarMatriz(){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
            if(matriz[i][j]->link == NULL){
			    cout<<matriz[i][j]->numero<<" ";
            }
		}
		cout<<endl;
	}
}

bool revisarSubMatriz(int i, int j, int valor){
    Lista p;
    p = new(Nodo);
    for(int ii=0;ii<i;ii++){
        for(int jj=0;jj<j;jj++){
            p = matriz[ii][jj];
            while(p->link != NULL){
                if(matriz[ii][jj]->numero==valor){
                    return true;
                    p->link = NULL;
                }
                else{
                    p = matriz[ii][jj]->link; 
                }
            }
        }
    }
    return false;
}
/*
void verificar(Lista aux){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(matriz[i][j]->esFijo==false){
                for(int k=1;k<=9;k++){
                    if(revisarSubMatriz(j,k,matriz[i][j]->numero)){
                        matriz[i][j].push_back(k);
                    }
                }
            }
        }
    }
}
*/
int main(int argc, char* argv[]){

	//Para ingresar los datos, se ingresa por ejemplo: ./ejecutable "[1;2;3][4;5;6][7;8;9]"
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
            Lista p; 
            p = matriz[i][j];
            while(p->link != NULL){
                cout<<"hola"<<endl;
			    matriz[i][j]->numero = 0;
                matriz[i][j]->esFijo = false;
                matriz[i][j]->link = NULL;
                p->link = NULL;
            }
        }
    }
    
	string argumento = argv[1];
	bool comprobar = true;
	int aux = (argumento.size()/7*4);// entrega numero de caracteres en argumento
	int detalle[argumento.size()- aux];//vector de largo del total de numeros
	int largoDetalle=0;
    int i=0;
    int largoArgumento = argumento.size();

    while(i<largoArgumento){
        if(argumento[i]=='['){
            i++;
            if(esNumero(argumento[i]) && (argumento[i]>=48 && argumento[i]<57)){
                detalle[largoDetalle]=ConvierteANumero(argumento[i]);
                i++;
                largoDetalle++;
                if(argumento[i]==';'){
                    i++;
                    if(esNumero(argumento[i]) && (argumento[i]>=48 && argumento[i]<57)){
                        detalle[largoDetalle]=ConvierteANumero(argumento[i]);
                        i++;
                        largoDetalle++;
                        if(argumento[i]==';'){
                            i++;
                            if(esNumero(argumento[i]) && (argumento[i]>48 && argumento[i]<=58)){
                                detalle[largoDetalle]=ConvierteANumero(argumento[i]);
                                i++;
                                largoDetalle++;
                                if(argumento[i]==']'){
                                    i++;
                                }
                                else{
                                    comprobar = false;
                                    i=largoArgumento;    
                                }
                            }
                            else{
                                comprobar = false;
                                i=largoArgumento;
                            }
                        }
                        else{
                            comprobar = false;
                            i=largoArgumento;
                        }
                    }
                    else{
                        comprobar = false;
                        i=largoArgumento;    
                    }
                }
                else{
                    comprobar = false;
                    i=largoArgumento;
                }
            }
            else{
                comprobar = false;
                i=largoArgumento;    
            }
        }
        else{
            comprobar = false;
            i=largoArgumento;
        }
    }

    if(comprobar){
        cout<<"Guardados"<<endl;
    }
    else{
        cout<<"Error de formato"<<endl;
    }

    ofstream fs("sudoku.csv");
    
    int j=0;
    while(j<largoDetalle){
        if(matriz[detalle[j]][detalle[j+1]]->numero==0){
            matriz[detalle[j]][detalle[j+1]]->numero=detalle[j+2];
            matriz[detalle[j]][detalle[j+1]]->esFijo = true;
            matriz[detalle[j]][detalle[j+1]]->link = NULL;
            j=j+3;
        }
        else{
            cout<<"ya se ingreso un dato en el punto ("<<detalle[j]<<","<<detalle[j+1]<<"), no se actualizo"<<endl;
            j=j+3;
        }
    }

    mostrarMatriz();

    for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			fs<<matriz[i][j]->numero<<";";
        }
        fs<<endl;
    }
    fs.close();
	return 0;
}
