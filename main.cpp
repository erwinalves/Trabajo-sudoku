#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

int ConvierteANumero(char valor){
	int n = (int)valor;
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

void mostrarMatriz(int matriz[][9]){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout<<matriz[i][j]<<" ";
		}
		cout<<endl;
	}
}

bool revisarValorFila(int i, int valor, int matriz[][9]){
    for(int j=0;j<9;j++){
        if(matriz[i][j]==valor){
            return true;
        }
    }
    return false;
}

bool revisarValorColumna(int j, int valor, int matriz[][9]){
    for(int i=0;i<9;i++){
        if(matriz[i][j]==valor){
            return true;
        }
    }
    return false;
}

bool revisarSubMatriz(int i, int j, int valor, int matriz[][9]){
    for(int ii=0;ii<i;ii++){
        for(int jj=0;jj<9;jj++){
            if(matriz[ii][jj]==valor){
                return true;
            }
        }
    }
    return false;
}

void dividirArgumento(string argumento, int detalle[], int largoDetalle, bool comprobar){
    comprobar=true;
    largoDetalle=1;
    int largoArgumento = 1;
    if(argumento[0]=='['){
        while(largoArgumento<argumento.size() && comprobar){
            if(esNumero(argumento[largoArgumento]) && (argumento[largoArgumento+1]==',' || argumento[largoArgumento+1]==']' || argumento[largoArgumento+1]=='[')){
                if(ConvierteANumero(argumento[largoDetalle])>=0 && ConvierteANumero(argumento[largoDetalle])<9){
                    detalle[largoDetalle] = (int)(argumento[largoDetalle]);
                    largoDetalle++;
                    largoArgumento++;
                }
            }
            else{
                if(argumento[largoDetalle]==' ' || argumento[largoDetalle]==','){
                    largoArgumento++;
                }
                else{
                    comprobar=false;
                }
            }
        }
    }
    else
        comprobar=false;
}

int main(int argc, char* argv[]){

	//Para ingresar los datos, se ingresa por ejemplo: ./ejecutable "[1;2;3]" "[4;5;6]" "[7;8;9]"
	int matriz[9][9];
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			matriz[i][j]=0;

	string argumento = argv[2];
	bool comprobar = true;
	int aux = argumento.size()/7*4;
	int detalle[argumento.size()- aux];
	int largoDetalle=1;

	dividirArgumento(argumento,detalle,largoDetalle,comprobar);

	int i=0;
	while(i<largoDetalle){
        matriz[detalle[i]][detalle[i+1]] = detalle[i+2];
        i=i+3;
	}

    mostrarMatriz(matriz);
    cout<<endl;
	return 0;
}
