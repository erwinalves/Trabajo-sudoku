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

Lista matriz[9][9];//matriz de listas, variable local

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
            p=matriz[i][j];
            cout<<p->numero<<" ";
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
            if(i>=6 && i<=8){
                ini_i=6;
                fin_i=8;
            }
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
            if(j>=6 && j<=8){
                ini_j=6;
                fin_j=8;
            }
        }
    }
}

bool revisarSubMatriz(int i, int j, int valor){
    int ini_i=0, ini_j=0, fin_i=0, fin_j=0;
    darIndiceSubMatriz( i, j, ini_i, ini_j, fin_i, fin_j);
    for(int m=ini_i;m<=fin_i;m++){
        for(int n=ini_j;n<=fin_j;n++){
            if(matriz[m][n]->numero==valor && matriz[m][n]->esFijo){
                return true;
            }
        }
    }
    return false;
}

bool revisarFila(int i, int valor){
    for(int j=0;j<9;j++){
        if(matriz[i][j]->numero==valor && matriz[i][j]->esFijo){
            return true;
        }
    }
    return false;
}

bool revisarColumna(int j, int valor){
    for(int i=0;i<9;i++){
        if(matriz[i][j]->numero==valor && matriz[i][j]->esFijo){
            return true;
        }
    }
    return false;
}

void mostrarListas(Lista m){
    Lista p;
    p = new(Nodo);
    cout<<"matriz = ";
    if(m->link==NULL){
        cout<<m->numero<<endl;
    }
    else{
        p=m;
        while(p->link!=NULL){
            cout<<p->numero;
            p = p->link;
            if(p->link!=NULL){
                cout<<" -> ";
            }
            else{
                cout<<" -> "<<p->numero<<endl;
            }
        }
    }
}

int encontrarMayor(int vector[]){
    int aux=0;
    for(int i=0;i<9;i++){
        if(vector[aux]<vector[i]){
            aux=i;
        }
    }
    vector[aux]=-1;
    return aux;
}

void verificarTodosLlenos(bool &respuesta, int &contador){
    contador =0;
    respuesta = false;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(matriz[i][j]->esFijo==true){
                contador++;
            }
            if(contador==81){
                respuesta = true;
            }
            else{
                if(contador < 81){
                    respuesta = false;
                }
            }
        }
    }
}

bool estaEnLista(int valor, Lista l){
    Lista p;
    p = new(Nodo);
    p = l;
    while(p->link!=NULL){
        if(p->numero == valor){
            return true;
        }
        p = p->link;
        if(p->numero == valor && p->link == NULL){
            return true;
        }
    }
    return false;
}

void eliminarValorLista(int valor, int i, int j){
    Lista p,l;
    for(int jj=0;jj<9;jj++){//recorrer columna
        if(matriz[i][jj]->esFijo==false && matriz[i][jj]->link!=NULL && estaEnLista(valor,matriz[i][jj])){
            Lista pp,ll;
            pp = new(Nodo);
            ll = new(Nodo);
            ll = matriz[i][jj];
            pp = matriz[i][jj]->link;
            if(pp->link==NULL){
                if(ll->numero==valor){
                    matriz[i][jj] = pp;
                    ll->link=NULL;
                }
                else{
                    if(pp->numero==valor){
                        matriz[i][jj]->link=NULL;
                    }
                }
            }
            else{
                if(ll->numero==valor){
                    matriz[i][jj] = pp;
                    ll->link=NULL;
                }
                else{
                    if(pp->numero==valor){
                        matriz[i][jj]->link = pp->link;
                        pp->link=NULL;
                    }
                    else{
                        while(pp->link != NULL){
                            if(pp->numero == valor){
                                ll->link = pp->link;
                                pp->link=NULL;
                            }
                            else{
                                pp = pp->link;
                                ll = ll->link;
                                if(pp->link == NULL && pp->numero==valor){
                                    ll->link=NULL;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for(int ii=0;ii<9;ii++){//recorrer fila
        if(matriz[ii][j]->esFijo==false && matriz[ii][j]->link!=NULL && estaEnLista(valor,matriz[ii][j])){
            Lista p,l;
            p = new(Nodo);
            l = new(Nodo);
            l = matriz[ii][j];
            p = matriz[ii][j]->link;
            if(p->link==NULL){
                if(l->numero==valor){
                    matriz[ii][j] = p;
                    l->link=NULL;
                }
                else{
                    if(p->numero==valor){
                        matriz[ii][j]->link=NULL;
                    }
                }
            }
            else{
                if(l->numero==valor){
                    matriz[ii][j] = p;
                    l->link=NULL;
                }
                else{
                    if(p->numero==valor){
                        matriz[ii][j]->link = p->link;
                        p->link=NULL;
                    }
                    else{
                        while(p->link != NULL){
                            if(p->numero == valor){
                                l->link = p->link;
                                p->link=NULL;
                            }
                            else{
                                p = p->link;
                                l = l->link;
                                if(p->link == NULL && p->numero==valor){
                                    l->link=NULL;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    int ini_i=0, ini_j=0, fin_i=0, fin_j=0;
    darIndiceSubMatriz( i, j, ini_i, ini_j, fin_i, fin_j);
    for(int m=ini_i;m<=fin_i;m++){// recorrer submatriz
        for(int n=ini_j;n<=fin_j;n++){
            if(matriz[m][n]->esFijo==false && matriz[m][n]->link!=NULL && estaEnLista(valor,matriz[m][n])){
                Lista ppp,lll;
                ppp = new(Nodo);
                lll = new(Nodo);
                ppp = matriz[m][n]->link;
                lll = matriz[m][n];
                if(ppp->link==NULL){
                    if(lll->numero==valor){
                        matriz[m][n] = ppp;
                        lll->link=NULL;
                    }
                    else{
                        if(ppp->numero==valor){
                            matriz[m][n]->link=NULL;
                        }
                    }
                }
                else{
                    if(lll->numero==valor){
                        matriz[m][n] = ppp;
                        lll->link=NULL;
                    }
                    else{
                        if(ppp->numero==valor){
                            matriz[m][n]->link = ppp->link;
                            ppp->link=NULL;
                        }
                        else{
                            while(ppp->link != NULL){
                                if(ppp->numero == valor){
                                    lll->link = ppp->link;
                                    ppp->link=NULL;
                                }
                                else{
                                    ppp = ppp->link;
                                    lll = lll->link;
                                    if(ppp->link == NULL && ppp->numero==valor){
                                        lll->link=NULL;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void revisarEnMatriz(int valor, int aux[][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(matriz[i][j]->esFijo==false){
                if(!revisarFila(i,valor)){
                    if(!revisarColumna(j,valor)){
                        if(!revisarSubMatriz(i,j,valor)){
                            Lista p;
                            p = new(Nodo);
                            p->numero = valor;
                            p->esFijo = false;
                            p->link = NULL;
                            aux[i][j]++;
                            if(matriz[i][j]->numero==0){
                                matriz[i][j] = p;
                            }
                            else{
                                if(matriz[i][j]->link==NULL && matriz[i][j]->numero!=0){
                                    matriz[i][j]->link=p;
                                }
                                else{
                                    Lista l;
                                    l = new(Nodo);
                                    l = matriz[i][j];
                                    while(l->link!=NULL){
                                        l=l->link;
                                    }
                                    l->link=p;
                                }
                            }
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

    int matrizAux[9][9];
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            matrizAux[i][j]=0;

    int contador[9];
    for(int i=0;i<9;i++){
        contador[i]=0;
    }
    
	string argumento = argv[1];
	bool comprobar = true;
	int aux = (argumento.size()/7*4);// entrega numero de caracteres en argumento
	int detalle[argumento.size()- aux];//vector de largo del total de numeros
	int largoDetalle=0;
    int i=0;
    int largoArgumento = argumento.size();

    while(i<largoArgumento && comprobar){
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
    
    int j=0, cont=0;
    while(j<largoDetalle){
        if(matriz[detalle[j]][detalle[j+1]]->numero==0){
            Lista p;
            p = new(Nodo);
            p->numero=detalle[j+2];
            p->esFijo = true;
            p->link = NULL;
            matriz[detalle[j]][detalle[j+1]] = p;
            contador[detalle[j+2]-1]++;
            j=j+3;
        }
        else{
            cout<<"ya se ingreso un dato en el punto ("<<detalle[j]<<","<<detalle[j+1]<<"), no se actualizo"<<endl;
            j=j+3;
        }
    }

    mostrarMatriz();
    cout<<endl;


    int indice;
    for(int i=0;i<9;i++){
        indice=encontrarMayor(contador);
        revisarEnMatriz(indice+1,matrizAux);//se suma uno por que los valores que entrega indice parten desde el 0
    }

    bool completo = false;
    int contAux = 0;
    while(contAux<=81 && completo!=true){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(matriz[i][j]->esFijo==false && matriz[i][j]->link==NULL){
                    matriz[i][j]->esFijo=true;
                    eliminarValorLista(matriz[i][j]->numero,i,j);
                }
            }
        }
        verificarTodosLlenos(completo,contAux);
    }
    
    cout<<endl;
    mostrarMatriz();

    for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
            if(matriz[i][j]->esFijo==true){
                if(j==8){
                    fs<<matriz[i][j]->numero;
                }
                else{
			        fs<<matriz[i][j]->numero<<";";
                }
            }
        }
        fs<<endl;
    }
    fs.close();
	return 0;
}
