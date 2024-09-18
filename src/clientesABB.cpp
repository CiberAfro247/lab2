#include "../include/clientesABB.h"

struct rep_clientesABB {
    TCliente cliente;
    TClientesABB left, right;
};

TClientesABB crearTClientesABBVacio(){
    return NULL;
}
//insert ordenado por id
void insertarTClienteTClientesABB(TClientesABB &clientesABB, TCliente cliente){
    if (clientesABB == NULL){
        clientesABB = new rep_clientesABB;
        clientesABB->cliente = cliente;
        clientesABB->left = clientesABB->right = NULL;
    } else if(idTCliente(cliente)<idTCliente(clientesABB->cliente)){
            insertarTClienteTClientesABB(clientesABB->left, cliente);
    } else if(idTCliente(cliente)>idTCliente(clientesABB->cliente)){
            insertarTClienteTClientesABB(clientesABB->right, cliente);
    }
}

void imprimirTClientesABB(TClientesABB clientesABB){
    if (clientesABB != NULL){
        imprimirTClientesABB(clientesABB->left);
        imprimirTCliente(clientesABB->cliente);
        imprimirTClientesABB(clientesABB->right);
    }
}

void liberarTClientesABB(TClientesABB &clientesABB){
    if (clientesABB != NULL){
        liberarTClientesABB(clientesABB->left);
        liberarTCliente(clientesABB->cliente);
        liberarTClientesABB(clientesABB->right);
        delete clientesABB;
    }
    clientesABB = NULL;
}

bool existeTClienteTClientesABB(TClientesABB clientesABB, int idCliente){
    if(clientesABB == NULL){
        return false;
    } else
        if (idCliente == idTCliente(clientesABB->cliente)){
            return true;
        } else if (idCliente > idTCliente(clientesABB->cliente)){
                return existeTClienteTClientesABB(clientesABB->right,idCliente);
                } else {
                return existeTClienteTClientesABB(clientesABB->left,idCliente);
                }
} 
TCliente obtenerTClienteTClientesABB(TClientesABB clientesABB, int idCliente){
    if( clientesABB == NULL){
            return NULL;
        } else if (idCliente == idTCliente(clientesABB->cliente)){
            return clientesABB->cliente;
        } else if (idCliente > idTCliente(clientesABB->cliente)){
            return obtenerTClienteTClientesABB(clientesABB->right,idCliente);
        } else if(idCliente < idTCliente(clientesABB->cliente)){
            return obtenerTClienteTClientesABB(clientesABB->left,idCliente);
        }
    return clientesABB->cliente;    
}
nat max(nat cntleft, nat cntright){
    nat max = 0;
    if (cntleft > cntright){
        max = cntleft;
    }
    else max = cntright;
    return max;
}
nat alturaTClientesABB(TClientesABB clientesABB){
    if (clientesABB == NULL){
        return 0;
    } else {
        nat altleft = alturaTClientesABB(clientesABB->left);
        nat altright = alturaTClientesABB(clientesABB->right);
        return max(altleft,altright) + 1;
    }
}

TCliente maxIdTClienteTClientesABB(TClientesABB clientesABB){
    TClientesABB iter = clientesABB;
    while(iter->right != NULL){
        iter = iter->right;
    }
    return iter->cliente;
}
void removerTClienteTClientesABB(TClientesABB &clientesABB, int idCliente){
        if(clientesABB != NULL){
            if(idCliente < idTCliente(clientesABB->cliente))
                removerTClienteTClientesABB(clientesABB->left,idCliente);
            else if(idCliente > idTCliente(clientesABB->cliente))
                removerTClienteTClientesABB(clientesABB->right,idCliente);
            else{
                if(clientesABB->left == NULL && clientesABB->right == NULL){
                    liberarTCliente(clientesABB->cliente);
                    delete clientesABB;
                    clientesABB = NULL;
                }
                else if(clientesABB->left == NULL){
                    TClientesABB aborrar = clientesABB;
                    clientesABB = clientesABB->right;
                    liberarTCliente(aborrar->cliente);
                    delete aborrar;
               } else if (clientesABB->right == NULL){
                    TClientesABB aborrar = clientesABB;
                    clientesABB = clientesABB->left;
                    liberarTCliente(aborrar->cliente);
                    delete aborrar;
                } else{
                    TCliente maxCliente = maxIdTClienteTClientesABB(clientesABB->left);
                    liberarTCliente(clientesABB->cliente);
                    clientesABB->cliente = copiarTCliente(maxCliente);
                    removerTClienteTClientesABB(clientesABB->left,idTCliente(clientesABB->cliente));
                }
            }     
        }
}
int cantidadClientesTClientesABB(TClientesABB clientesABB){
    if(clientesABB == NULL){
        return 0;
    }
    else 
        return 1 + cantidadClientesTClientesABB(clientesABB->left) + cantidadClientesTClientesABB(clientesABB->right);
}
int edadtotalClientes(TClientesABB clientesABB){
 if(clientesABB == NULL){
    return 0.;
    }else{
        int edadraiz = edadTCliente(clientesABB->cliente);
        nat edadLeft = edadtotalClientes(clientesABB->left);
        nat edadRight = edadtotalClientes(clientesABB->right);
        int total = edadraiz + edadLeft + edadRight;
        return total; 
    }
}
float edadPromedioTClientesABB(TClientesABB clientesABB){
   if(clientesABB == NULL){
    return 0.;
    } else{
        int cntClientes = cantidadClientesTClientesABB(clientesABB);
        float total = edadtotalClientes(clientesABB);
        return total/cntClientes;
    }
}

TCliente obtenerNesimoClienteTClientesABB(TClientesABB clientesABB, int n){
    if(clientesABB == NULL || n == 0){
        return NULL;
    }
    else{
        int cantClientLeft = cantidadClientesTClientesABB(clientesABB->left);
        if(n == cantClientLeft+1){
            return clientesABB->cliente;
        }else if(n <= cantClientLeft){
                return obtenerNesimoClienteTClientesABB(clientesABB->left,n);
        }else 
            return obtenerNesimoClienteTClientesABB(clientesABB->right,n-(cantClientLeft+1));
    }
}
