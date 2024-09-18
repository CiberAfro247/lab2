#include "../include/clientesSucursalesLDE.h"
typedef struct rep_sucursal *TSucursal;
struct rep_clientesSucursalesLDE {
	TSucursal inicio;
	TSucursal fin;
	};
struct rep_sucursal{
	TSucursal sig;
	TSucursal ant;
	int idSucursal;
	TClientesABB clientes;	
};
TClientesSucursalesLDE crearTClientesSucursalesLDEVacia(){
	TClientesSucursalesLDE cabezal = new rep_clientesSucursalesLDE;
	cabezal->inicio = NULL;
	cabezal->fin = NULL;
	return cabezal;
}
void insertarClientesABBTClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE, TClientesABB clientesABB, int idSucursal){
// ingresar un arbol en una sucursal, voy a tener que evaluar la edad promedio de las sucursales e insertar ordeanadamente
	if(clientesSucursalesLDE->inicio == NULL || edadPromedioTClientesABB(clientesABB) < edadPromedioTClientesABB(clientesSucursalesLDE->inicio->clientes)){
		TSucursal nuevaSucursal = new rep_sucursal;
		nuevaSucursal->clientes = clientesABB;
		nuevaSucursal->idSucursal = idSucursal;
		nuevaSucursal->ant = NULL;
		nuevaSucursal->sig = clientesSucursalesLDE->inicio;
		if (clientesSucursalesLDE->inicio != NULL) {
    		clientesSucursalesLDE->inicio->ant = nuevaSucursal;
		} else {
    		clientesSucursalesLDE->fin = nuevaSucursal;
		}
		clientesSucursalesLDE->inicio = nuevaSucursal;
	} else{
		TSucursal nuevaSucursal = new rep_sucursal;
		nuevaSucursal->clientes = clientesABB;
		nuevaSucursal->idSucursal = idSucursal;		
		TSucursal iter = clientesSucursalesLDE->inicio;
		
		while(iter->sig != NULL && edadPromedioTClientesABB(clientesABB) >= edadPromedioTClientesABB(iter->sig->clientes)){
			iter = iter->sig;
		}

		if (iter->sig != NULL){
			iter->sig->ant = nuevaSucursal;
		}else {
			clientesSucursalesLDE->fin = nuevaSucursal;
		}
		
		nuevaSucursal->sig = iter->sig;
		iter->sig = nuevaSucursal;
		nuevaSucursal->ant = iter;
	}
}

void liberarTClientesSucursalesLDE(TClientesSucursalesLDE &clientesSucursalesLDE){
	TSucursal iter = clientesSucursalesLDE->inicio;
	while(iter != NULL){
		TSucursal del = iter;
		iter = iter->sig;
		liberarTClientesABB(del->clientes);
		delete del;
	}
	delete clientesSucursalesLDE;
	clientesSucursalesLDE = NULL;
}

void imprimirTClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	printf("clientesSucursalesLDE de grupos:\n");
	TSucursal iter = clientesSucursalesLDE->inicio;
	while(iter != NULL){
			printf("Grupo con edad promedio %.2f:\n",edadPromedioTClientesABB(iter->clientes));
			imprimirTClientesABB(iter->clientes);
			iter = iter->sig;
	}
}

void imprimirInvertidoTClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	printf("clientesSucursalesLDE de grupos:\n");
	TSucursal iter = clientesSucursalesLDE->fin;
	while(iter != NULL){
			printf("Grupo con edad promedio %.2f:\n",edadPromedioTClientesABB(iter->clientes));
			imprimirTClientesABB(iter->clientes);
			iter = iter->ant;
	}
}

nat cantidadTClientesABBClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	if (clientesSucursalesLDE == NULL){
			return 0;
	}
	TSucursal iter = clientesSucursalesLDE->inicio;
	nat cntSucursales = 0;
	while(iter != NULL){
			cntSucursales++;
			iter = iter->sig;
	}
	return cntSucursales;
}

TClientesABB obtenerPrimeroClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	return clientesSucursalesLDE->inicio->clientes;
}

TClientesABB obtenerNesimoClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE, int n){
	int cantidad = cantidadTClientesABBClientesSucursalesLDE(clientesSucursalesLDE);
	if (n > cantidad){
			return NULL;
		}
		if(n == 1){
			return obtenerPrimeroClientesSucursalesLDE(clientesSucursalesLDE);
		}
		if (n == cantidad){
			return clientesSucursalesLDE->fin->clientes;
		} 
		TSucursal iter = clientesSucursalesLDE->inicio;
		int pos = 1;
		while(iter != NULL && pos < n){
			iter = iter->sig;
			pos++;
		}
		return iter->clientes;
	}

TClientesABB removerUltimoClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	TSucursal aborrar = clientesSucursalesLDE->fin;
	TClientesABB retorna = clientesSucursalesLDE->fin->clientes;
	clientesSucursalesLDE->fin = clientesSucursalesLDE->fin->ant;
	if (clientesSucursalesLDE->fin != NULL){
		clientesSucursalesLDE->fin->sig = NULL;
	}else{
		clientesSucursalesLDE->inicio = NULL;
	}	
	delete aborrar;
	return retorna;
}
TClientesABB remmoverPrimerSucursal(TClientesSucursalesLDE clientesSucursalesLDE){
	TSucursal aborrar = clientesSucursalesLDE->inicio;
	TClientesABB retorna = clientesSucursalesLDE->inicio->clientes;
	clientesSucursalesLDE->inicio = clientesSucursalesLDE->inicio->sig;
	if(clientesSucursalesLDE->inicio !=NULL){
		clientesSucursalesLDE->inicio->ant = NULL;
	} else{
		clientesSucursalesLDE->fin = NULL;
	}	
	delete aborrar;
	return retorna;
}

TClientesABB removerNesimoClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE, int n){
int cantidad = cantidadTClientesABBClientesSucursalesLDE(clientesSucursalesLDE);
		if(n == 1){
			return remmoverPrimerSucursal(clientesSucursalesLDE);
		}
		if (n == cantidad){
			return removerUltimoClientesSucursalesLDE(clientesSucursalesLDE);
		} 
		TSucursal iter = clientesSucursalesLDE->inicio;
		int pos = 1;
		while(iter != NULL && pos < n){
			iter = iter->sig;
			pos++;
		}
		if (iter->ant != NULL) {
        	iter->ant->sig = iter->sig;
  		}
		if (iter->sig != NULL) {
			iter->sig->ant = iter->ant;
		}		
		TClientesABB retorna = iter->clientes;
		delete iter;
		return retorna;
	}

TCliente clienteMasRepetido(TClientesSucursalesLDE clientesSucursalesLDE) {
    if (clientesSucursalesLDE == NULL || clientesSucursalesLDE->inicio == NULL) {
		return NULL;
    }
		int maxID = idTCliente(maxIdTClienteTClientesABB(clientesSucursalesLDE->inicio->clientes));
		TSucursal iter = clientesSucursalesLDE->inicio->sig;	
		while(iter != NULL){
			int cantClientes = cantidadClientesTClientesABB(iter->clientes);
				for(int i = 1; i < cantClientes; i++){
					int id = idTCliente(maxIdTClienteTClientesABB(iter->clientes));
					if(id > maxID){
						maxID = id;
					}
				}
				iter = iter->sig;
			}
			int * ids = new int[maxID+1]();
			TSucursal sucursal = clientesSucursalesLDE->inicio;	
			while(sucursal != NULL){
				for(int i = maxID; i >= 1; i--){
					if (existeTClienteTClientesABB(sucursal->clientes,i)){
						ids[i]++;
					}
				}
				sucursal = sucursal->sig;
			}
			int maxRepes = ids[0];
			int idMaxRepes = 0;
			for(int i = 1; i <= maxID; i++){
				if (ids[i] > maxRepes){
					maxRepes = ids[i];
					idMaxRepes = i;
				} else if(ids[i] == maxRepes){
					if (idMaxRepes > i){
						idMaxRepes = i;
					}
				}
			}
			TSucursal aux = clientesSucursalesLDE->inicio->sig;
			TCliente retorna = NULL;
			while(aux != NULL ){
					if (existeTClienteTClientesABB(aux->clientes, idMaxRepes)) {
						 retorna = obtenerTClienteTClientesABB(aux->clientes,idMaxRepes);
				}
			aux = aux->sig;
			}
		delete[] ids;
		return retorna;
	}
