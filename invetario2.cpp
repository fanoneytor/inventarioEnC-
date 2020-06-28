#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

void menu();

void cabecera(){
	system("color b");
	cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"					SISTEMA DE INVENTARIO UTP"<<endl;
	cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl<<endl;	
}

bool validarCodigo(string codigoVer){
	string codigo, descripcion, salida;
	int valor, cantidad;
	bool existe = false;
	ifstream archivo("inventario.txt");
	if(archivo.is_open()){
		archivo>>codigo;
		while(!archivo.eof()){
			archivo>>valor;
			archivo>>descripcion;
			archivo>>cantidad;		
			if(codigo == codigoVer){
				existe = true;
			}
			archivo>>codigo;				
		}
		archivo.close();
	}
	return existe;
}

void agregarElemento(){
	cabecera();
	string codigo, descripcion;
	int valor, cantidad;
	cout<<"						AGREGAR ELEMENTO"<<endl<<endl;
	cout<<"					CODIGO ------> ";
	cin>>codigo;
	if(validarCodigo(codigo)){
		cout<<endl<<endl<<"					El codigo ya esta en uso..."<<endl<<"					";
		system("pause");
		system("cls");
		agregarElemento();
	}else{
		cout<<endl<<endl<<"					VALOR -------> ";
		cin>>valor;
		cout<<endl<<endl<<"					DESCRIPCION -> ";
		cin>>descripcion;
		cout<<endl<<endl<<"					CANTIDAD ----> ";
		cin>>cantidad;
	}
	
	ofstream archivo("inventario.txt", ofstream::app);
	archivo <<codigo <<" "<<valor<<" "<<descripcion<<" "<<cantidad<<endl;
	archivo.close();
	
	
	cout<<endl<<endl<<"					El elemento ha sido agregado!!"<<endl<<"					";
	system("pause");
	system("cls");
	menu();
}

void eliminarElemento(){
	cabecera();
	string codigo, codigoKill, descripcion, salida;
	int valor, cantidad;
	bool existe = false;
	
	cout<<"						ELIMINAR ELEMENTO"<<endl<<endl;
	cout<<"					CODIGO DEL ELEMENTO ------> ";
	cin>>codigoKill;
	
	ifstream archivo("inventario.txt"); 
	ofstream temporal("temporal.txt");
	if(archivo.is_open()){
		archivo>>codigo;
		while(!archivo.eof()){
			archivo>>valor;
			archivo>>descripcion;
			archivo>>cantidad;		
			if(codigo != codigoKill){
				temporal <<codigo <<" "<<valor<<" "<<descripcion<<" "<<cantidad<<endl;
			}else{
				cout<<"CODIGO: "<<codigo<<endl;
				cout<<"VALOR: "<<valor<<endl;
				cout<<"DESCRIPCION: "<<descripcion<<endl;
				cout<<"CANTIDAD: "<<cantidad<<endl;
				existe = true;
			}
			archivo>>codigo;				
		}
		archivo.close();
		temporal.close();
	}else{
		cout<<endl<<endl<<"					ERROR: no existe un archivo volver al menu...."<<endl<<"					";
		system("pause");
		system("cls");
		menu();
	}
	remove("inventario.txt");
	rename("temporal.txt", "inventario.txt");
	if(existe){
		cout<<endl<<endl<<"					El elemento ha sido eliminado satisfactoriamente!!"<<endl<<"					";
		system("pause");
		system("cls");
		menu();		
	}else{
		cout<<endl<<endl<<"					El elemento con codigo: "<<codigoKill<<" No existe!"<<endl<<"					";
		system("pause");
		system("cls");
		eliminarElemento();
	}	
}

void listarInventario(){
	cabecera();
	string codigo, descripcion, salida;
	int valor, cantidad;
	cout<<"						LISTA DEL INVENTARIO"<<endl<<endl;
	ifstream archivo("inventario.txt");
	if(archivo.is_open()){
		cout<<endl<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
		archivo>>codigo;
		while(!archivo.eof()){
			archivo>>valor;
			archivo>>descripcion;
			archivo>>cantidad;
			cout<<"CODIGO: "<<codigo<<endl;
			cout<<"VALOR: "<<valor<<endl;
			cout<<"DESCRIPCION: "<<descripcion<<endl;
			cout<<"CANTIDAD: "<<cantidad<<endl;
			cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
			archivo>>codigo;		
		}
	cout<<endl<<endl<<"					La lista a cargado satisfactoriamente!!"<<endl<<"					";
	}else{
		cout<<"					ERROR: no existe un archivo volver al menu...."<<endl<<"					";
	}
	archivo.close();		
	
	system("pause");
	system("cls");
	menu();
}

void backup(){
	cabecera();
	string codigo, descripcion, salida;
	int valor, cantidad;
		
	cout<<"						COPIA DE SEGURIDAD"<<endl<<endl;
	
	ifstream archivo("inventario.txt"); 
	ofstream backup("backup.txt");
	if(archivo.is_open()){
		archivo>>codigo;
		while(!archivo.eof()){
			archivo>>valor;
			archivo>>descripcion;
			archivo>>cantidad;		
			backup <<codigo <<" "<<valor<<" "<<descripcion<<" "<<cantidad<<endl;
			archivo>>codigo;				
		}
		archivo.close();
		backup.close();
	}else{
		cout<<"ERROR...."<<endl;
	}
	for(int i = 0; i<=100; i++){
		system("cls");
		cabecera();
		string codigo, descripcion, salida;
		int valor, cantidad;
			
		cout<<"						COPIA DE SEGURIDAD"<<endl<<endl;
		cout<<"							"<<i<<"%";
		Sleep(1);
	}
	cout<<endl<<endl<<"				Se ha realizado la copia de seguridad satisfactoriamente!!"<<endl<<"				";
	system("pause");
	system("cls");
	menu();	
}

void menu(){
	cabecera();
	int opcion;
	cout<<"					(1). AGREGAR ELEMENTO"<<endl<<endl;
	cout<<"					(2). ELIMINAR ELEMENTO"<<endl<<endl;
	cout<<"					(3). LISTAR INVENTARIO"<<endl<<endl;
	cout<<"					(4). CREAR COPIA DE SEGURIDAD"<<endl<<endl;
	cout<<"					(0). SALIDA"<<endl<<endl; 
	cout<<"					Ingrese una opcion: ";
	cin>>opcion;
	
	switch(opcion){
		case 1:
			system("cls");
			agregarElemento();
			break;
		case 2:
			system("cls");
			eliminarElemento();
			break;
		case 3:
			system("cls");
			listarInventario();
			break;
		case 4:
			system("cls");
			backup();
			break;
		case 0:
			break;
		default:
			cout<<endl<<"					"<<opcion<<" No es una opcion no valida!!"<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
			system("pause");
			system("cls");
			menu();
	}	
}

int main(){
	menu();
}
