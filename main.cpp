#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
//#include <mpi.h>

using namespace std;

typedef struct Nodo{
    int numero;
    bool esFijo; //para comprobar si es ingresado por la consola
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
    Lista p;
    p = new(Nodo);
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
            cout<<matriz[i][j]->numero<<" ";
		}
		cout<<endl;
        if(i==2 || i==5){
             cout<<"-----------------"<<endl;
        }
	}
}

void darIndiceSubMatriz(int i, int j, int &ini_i, int &ini_j,int &fin_i, int &fin_j){
    if(i>=0 && i<=2){
        ini_i=0;
        fin_i=2;
    }
    else {
        if(i>=3 && i<=5){
            ini_i=3;
            fin_i=5;
        }
        else{
            ini_i=6;
            fin_i=8;
        }
    }

    if(j>=0 && j<=2){
        ini_j=0;
        fin_j=2;
    }
    else{
        if(j>=3 && j<=5){
            ini_j=3;
            fin_j=5;
        }
        else{
            ini_j=6;
            fin_j=8;
        }
    }
}

bool revisarSubMatriz(int i, int j, int valor){
    int ini_i=0, ini_j=0, fin_i=0, fin_j=0;
    darIndiceSubMatriz( i, j, ini_i, ini_j, fin_i, fin_j);
    for(int m=ini_i;m<=fin_i;m++){
        for(int n=ini_j;n<fin_j;n++){
            if(matriz[m][n]->numero==valor){
                return true;
            }
        }
    }
    return false;
}

bool revisarFila(int i, int valor){
    for(int j=0;j<9;j++){
        if(matriz[i][j]->numero==valor){
            return true;
        }
    }
    return false;
}

bool revisarColumna(int j, int valor){
    for(int i=0;i<9;i++){
        if(matriz[i][j]->numero==valor){
            return true;
        }
    }
    return false;
}

void revisarEnMatriz(int valor){
    Lista p;
    p = new(Nodo);
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(matriz[i][j]->numero==0){
                if(!revisarSubMatriz(i,j,valor)){
                    if(!revisarColumna(j,valor)){
                        if(!revisarFila(i,valor) ){
                            p->numero = valor;
                            p->esFijo = false;
                            p->link = NULL;
                            matriz[i][j] = p;
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char* argv[]){

	//Para ingresar los datos, se ingresa por ejemplo: ./ejecutable "[1;2;3][4;5;6][7;8;9]"
    Lista p;
    p=new(Nodo);
	p->numero = 0;
    p->esFijo = false;
    p->link = NULL;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
            matriz[i][j] = p;
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
            Lista p;
            p = new(Nodo);
            p->numero=detalle[j+2];
            p->esFijo = true;
            p->link = NULL;
            matriz[detalle[j]][detalle[j+1]] = p;
            j=j+3;
        }
        else{
            cout<<"ya se ingreso un dato en el punto ("<<detalle[j]<<","<<detalle[j+1]<<"), no se actualizo"<<endl;
            j=j+3;
        }
    }
    mostrarMatriz();
    cout<<endl;

	revisarEnMatriz(3);

    mostrarMatriz();

    for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
            if(j==8){
                fs<<matriz[i][j]->numero;
            }
            else{
			    fs<<matriz[i][j]->numero<<";";
            }
        }
        fs<<endl;
    }
    fs.close();
	return 0;
}
