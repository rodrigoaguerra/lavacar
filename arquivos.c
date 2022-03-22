#include "header.h"

/* Working with file */
void salve_backup_clientes(void){
     FILE* arq;
     char strName[55];
     strcpy(strName, "backups\\clientes\\clientes-");
     data_arq(stringTime);
     strcat(strName, stringTime);
     strcat(strName, ".ogid\0");
     arq = fopen(strName, "wb");
     if (arq == 0){
         printf("Erro na abertura do arquivo %s .ogid \n", strName);
     }else{
         ListaCliente *v; /*var. para percorrer a lista*/
         if(clientes != NULL){
           for (v = clientes; v->next != NULL; v = v->next);
           while( v != NULL) {
             Cliente person = v->info;
             if(!(fwrite(&person, sizeof(Cliente), 1, arq) == 1))
                printf("erro ao salvar clientes no arquivo %s.ogid", strName);
             v = v->prev;
           }
           salve_backup_veiculos();
           message_of_info("Backup De Clientes Salvo!");
         }
     }
     fclose(arq);
}

void salve_backup_veiculos(void){
     FILE* arq;
     char strName[55];
     strcpy(strName, "save\\veiculos\\clientes-");
     data_arq(stringTime);
     strcat(strName, stringTime);
     strcat(strName, ".ogid\0");
     arq = fopen(strName, "wb");
     if (arq == 0){
         printf("Erro na abertura do arquivo %s .ogid \n", strName);
     }else{
         save_veicle(vehicles, arq);
         message_of_info("Backup De Veiculos Salvo!");
     }
     fclose(arq);
}

void salve_backup_servicos(void){
     FILE* arq;
     char strName[55];
     strcpy(strName, "backups\\servicos\\servicos-");
     data_arq(stringTime);
     strcat(strName, stringTime);
     strcat(strName, ".ogid\0");
     arq = fopen(strName, "wb");
     if (arq == 0){
         printf("Erro na abertura do arquivo %s .ogid \n", strName);
     }else{
         ListaServico *v; /*var. para percorrer a lista*/
         if(services != NULL){
           for (v = services; v->next != NULL; v = v->next);
           while( v != NULL) {
             Servico ser = v->info;
             if(!(fwrite(&ser, sizeof(Servico), 1, arq) == 1))
                printf("erro ao salvar servicos no arquivo %s.ogid", strName);
             v = v->prev;
           }
           message_of_info("Backup De Servicos Salvo!");
         }
     }
     fclose(arq);
}
void salve_backup_insumos(void){
     FILE* arq;
     char strName[55];
     strcpy(strName, "backups\\insumos\\insumos-");
     data_arq(stringTime);
     strcat(strName, stringTime);
     strcat(strName, ".ogid\0");
     arq = fopen(strName, "wb");
     if (arq == 0){
         printf("Erro na abertura do arquivo %s .ogid \n", strName);
     }else{
         ListaInsumo *v; /*var. para percorrer a lista*/
         if(insumos != NULL){
           for (v = insumos; v->next != NULL; v = v->next);
           while( v != NULL) {
             Insumo ins = v->info;
             if(!(fwrite(&ins, sizeof(Insumo), 1, arq) == 1))
                printf("erro ao salvar clientes no arquivo %s.ogid", strName);
             v = v->prev;
           }
            message_of_info("Backup De Insumo Salvo!");
         }
     }
     fclose(arq);
}
void salve_backup_funcionarios(void){
     FILE* arq;
     char strName[55];
     strcpy(strName, "backups\\funcionarios\\funcionarios-");
     data_arq(stringTime);
     strcat(strName, stringTime);
     strcat(strName, ".ogid\0");
     arq = fopen(strName, "wb");
     if (arq == 0){
         printf("Erro na abertura do arquivo %s .ogid \n", strName);
     }else{
         ListaUsuario *v; /*var. para percorrer a lista*/
         if(funcionarios != NULL){
           for (v = funcionarios; v->next != NULL; v = v->next);
           while( v != NULL) {
             Usuario usu = v->info;
             if(!(fwrite(&usu, sizeof(Usuario), 1, arq) == 1))
                printf("erro ao salvar clientes no arquivo %s.ogid", strName);
             v = v->prev;
           }
            message_of_info("Backup De Funcionarios Salvo!");
         }
     }
     fclose(arq);
}


void save_relat_ins(gchar* date_arq){
     FILE* arq;
     char strName[45];
     strcpy(strName, "relatorios-ins-mes\\relatorio-mes-");
     //subtrair os dias da string date_arq
     strcat(strName, &date_arq[3]);
     strcat(strName, ".ogid\0");
     //printf("%s\n", strName);
     arq = fopen(strName, "a+b");

     data_arq(stringTime);

     if (arq == 0){
         printf("Erro na abertura do arquivo");
     }else{
        int i;
        char data[15];
        strcpy(data, date_arq);
        //printf("%s", data);
        for (i=0; i < quant_ins; i++){
            int id_ins = insumosDia[i];
            ListaInsumo* no = procurar_insumos(insumos, id_ins);
               if(!(fwrite(&data, 15 * sizeof(char), 1, arq) == 1)){
                   printf("erro ao salvar a data no mes.\n");
               }

               if(!(fwrite(&no->info, sizeof(Insumo), 1, arq) == 1)){
                   printf("erro ao salvar Insumo no arquivo relatorio do mes.\n");
               }
        }
     }
     fclose(arq);
}

void save_relatorio_dia(void){
     FILE* arq;
     char strName[45];
     strcpy(strName, "relatorios-dia\\relatorio-");
     strcat(strName, date_d);
     strcat(strName, ".ogid\0");
     arq = fopen(strName, "w");
     strcpy(resultado_dia.data, date_d);

     if (arq == 0){
         printf("Erro na abertura do arquivo");
     }else{
        if((fwrite(&resultado_dia, sizeof(noDia), 1, arq) == 1)){
            //printf("data = %s\nentrada = %.2lf\nsaida = %.2lf\nlucro = %.2lf\n", resultado_dia.data, resultado_dia.entrada, resultado_dia.saida, resultado_dia.resultado);
              printf("relatorio do mes salvo\n");
        }else{
             printf("erro ao salvar veiculos no arquivo relatorio do mes.\n");
        }
     }
     fclose(arq);
}

void read_arqvs(void){
     gchar name_file[20];
     strcpy(name_file,"dados\\client.ogid");
     clientes = readClient(name_file, clientes);
     strcpy(name_file,"dados\\vehicles.dat");
     vehicles = NULL;
     atendidos = NULL;
     vehicles = readVehicles(name_file, vehicles);
     strcpy(name_file,"dados\\insumos.ogid");
     insumos = readInsumos(name_file, insumos);
     strcpy(name_file,"dados\\services.ogid");
     services = readSevices(name_file, services);
     strcpy(name_file,"dados\\user.ogid");
     funcionarios = readFuncion(name_file, funcionarios);
}

ListaUsuario* readFuncion(gchar* arq_name, ListaUsuario* us){
     /*create fila*/
    us = criar_list_usu();
    FILE* arq = fopen(arq_name, "rb");
    if(arq == 0){
			printf("Erro, nao foi possivel abrir o arquivo.: %s\n", arq_name);
			return funcionarios;
    }else{
        Usuario person;
        gtk_list_store_clear                (GTK_LIST_STORE(interface->treemodel_usu));
        while(!feof(arq)){
          if(fread(&person, sizeof(Usuario), 1, arq) == 1){

                //insert in list from page Gerenciar-Clientes
                GtkTreeIter iter;
                pega_data(stringTime);
                gtk_list_store_append (GTK_LIST_STORE (interface->treemodel_usu), &iter);
                gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_usu), &iter,
                         COLUMN_USER_ID,      person.userId,
                         COLUMN_USER_NOME,    person.nome,
                         COLUMN_USER_TELFONE, person.telefone,
                         COLUMN_USER_RG,      person.rg,
                         COLUMN_USER_END,     person.ende,
                         COLUMN_USER_ENT,     "",
                         COLUMN_USER_SAI,     "",
                         COLUMN_USER_PAG,     "",
                         COLUMN_USER_EDIT,    TRUE,
                         COLUMN_USER_DATA,    stringTime, -1);

                us = inserirlistusu(us, person);

          }else{
                printf("termino do carregamento de funcionarios!\n");
                fclose(arq);
                break;
           }
        }
        return us;
    }
}

ListaServico* readSevices(gchar* arq_name, ListaServico* ser){
    /*create fila*/
    ser = criar();
    FILE* arq = fopen(arq_name, "rb");
    if(arq == 0){
			printf("Erro, nao foi possivel abrir o arquivo.: %s\n", arq_name);
			return services;
    }else{
        Servico serv;
        gtk_list_store_clear  (GTK_LIST_STORE(interface->treemodel_ser));
        while(!feof(arq)){
           if(fread(&serv, sizeof(Servico), 1, arq) == 1){
                //insert in list from page Gerenciar-Clientes
                GtkTreeIter iter;
                gtk_list_store_append (GTK_LIST_STORE (interface->treemodel_ser), &iter);
                gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_ser), &iter,
                         COLUMN_SERV_ID,      serv.serId,
                         COLUMN_SERV_NOME,    serv.nome,
                         COLUMN_SERV_QUANTP,  g_strdup_printf ("%.2f", serv.valorP),
                         COLUMN_SERV_QUANTM,  g_strdup_printf ("%.2f", serv.valorM),
                         COLUMN_SERV_QUANTG,  g_strdup_printf ("%.2f", serv.valorG),
                         COLUMN_SERV_DESCRI,  serv.descri,
                         COLUMN_SERV_X,       FALSE,-1);
                ser = inserirList(ser, serv);
           }
           else{
                  printf("termino do carregamento de servicos!\n");
                  fclose(arq);
                  break;
           }
        }
        return ser;
    }
}

ListaInsumo* readInsumos(gchar* arq_name, ListaInsumo* in){
    //create fila
    in = criar_list_ins();
    FILE* arq = fopen(arq_name, "rb");
    if(arq == 0){
       printf("Erro, nao foi possivel abrir o arquivo\n");
       return insumos;
    }else{
        Insumo ins;
        gtk_list_store_clear                (GTK_LIST_STORE(interface->treemodel_ins));
        gtk_list_store_clear                (GTK_LIST_STORE(interface->treemodel_insser));
        while(!feof(arq)){
           if(fread(&ins, sizeof(Insumo), 1, arq) == 1){
                //insert in list from page Gerenciar-Insumos
                GtkTreeIter iter;
                gtk_list_store_append (GTK_LIST_STORE (interface->treemodel_ins), &iter);
                gtk_list_store_set    (GTK_LIST_STORE (interface->treemodel_ins), &iter,
                         COLUMN_INSUMOS_ID,        ins.insId,
                         COLUMN_INSUMOS_NOME,      ins.nome,
                         COLUMN_INSUMOS_VALOR,     g_strdup_printf ("%.2f", ins.valor),
                         COLUMN_INSUMOS_QUANT,     g_strdup_printf ("%.3f", ins.quant),
                         COLUMN_INSUMOS_DESCRI,    ins.descri,
                         COLUMN_INSUMOS_TIPO,      ins.tipo, -1);

                 gtk_list_store_append (GTK_LIST_STORE (interface->treemodel_insser), &iter);
                 gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_insser), &iter,
                         COLUMN_INSSER_USA,        FALSE,
                         COLUMN_INSSER_NOME,       ins.nome,
                         COLUMN_INSSER_QUANTP,      "",
                         COLUMN_INSSER_QUANTM,      "",
                         COLUMN_INSSER_QUANTG,      "",
                         COLUMN_INSSER_IDINS,      ins.insId,
                         COLUMN_INSSER_TIPO,       ins.tipo, -1);

                 in = inserirInsumo(in, ins);
           }else{
                  printf("termino do carregamento de insumos!\n");
                  fclose(arq);
                  break;
            }
        }
        return in;
    }
}


Arvore* readVehicles(gchar *arq_name, Arvore* a){
    //criando a arvore
    a = NULL;
    FILE* arq = fopen(arq_name, "rb");
    if(arq == 0){
          printf("Erro, nao foi possivel abrir o arquivo\n");
          return vehicles;
    }else{
        Veiculo vehicle;
        gtk_list_store_clear                (GTK_LIST_STORE(interface->treemodel_vei));
        while(!feof(arq)){
           if((fread(&vehicle, sizeof(Veiculo), 1, arq) == 1)){
                //insert in list from page Gerenciar-Clientes
                  GtkTreeIter iter;
                  ListaCliente *no = procurarlistcli (clientes, vehicle.cli_id);
                  Cliente person = no->info;
                 //adicionando Veiculo na lista de veiculo.

                    gtk_list_store_append (GTK_LIST_STORE (interface->treemodel_vei), &iter);
                    gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_vei), &iter,
                                 COLUMN_VEHICLE_PLACA,        vehicle.placa,
                                 COLUMN_VEHICLE_MODELO,       vehicle.modelo,
                                 COLUMN_VEHICLE_PROPRIETARIO, person.nome,
                                 COLUMN_VEHICLE_ENTRADA,      vehicle.entrada,
                                 COLUMN_VEHICLE_SAIDA,        vehicle.saida,
                                 COLUMN_VEHICLE_COR,          vehicle.cor,
                                 COLUMN_VEHICLE_TAMANHO,      vehicle.tamanho,
                                 COLUMN_VEHICLE_CLI_ID,       vehicle.cli_id, -1);
               a = inserir(a, vehicle);
           }else{
                  printf("termino do carregamento de veiculos!\n");
                  fclose(arq);
                  break;
            }
        }
        return a;
    }
}


ListaCliente* readClient(gchar *arq_name, ListaCliente* lista){
      /*create fila*/
    lista = criar_list_cli();
    FILE* arq = fopen(arq_name, "rb");
    GtkTreeIter iter;
    //GtkTreeIter siter;
    if(arq == 0){
          printf("Erro, nao foi possivel abrir o arquivo.: %s\n", arq_name);
          return clientes;
    }else{
        gtk_list_store_clear                (GTK_LIST_STORE(interface->treemodel_cli));

        Cliente person;
        while(!feof(arq)){
           if(fread(&person, sizeof(Cliente), 1, arq) == 1){

                //insert in list from page Gerenciar-Clientes

                gtk_list_store_append (GTK_LIST_STORE (interface->treemodel_cli), &iter);
                gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_cli), &iter,
                         COLUMN_ITEM_ID,      person.id,
                         COLUMN_ITEM_NOME,    person.nome,
                         COLUMN_ITEM_TELFONE, person.telefone,
                         COLUMN_ITEM_DATA,    person.data, -1);

                lista = inserirlistcli(lista, person);

           }else{
                  printf("termino do carregamento de clientes!\n");
                  fclose(arq);
                  break;
           }
        }
        return lista;
    }
}


void save_arqvs(void){
     saveInsumos();
     saveServices();
     saveClient();
     saveFuncion();
     FILE* arq_vehicle;
     if((arq_vehicle = fopen("dados\\vehicles.dat", "wb")) == NULL)
                printf("Erro, nao foi possivel abrir o arquivo\n");
     save_veicle(vehicles, arq_vehicle);
     /* ao final do uso, o arquivo deve ser fechado */
     fclose(arq_vehicle);
}

void saveInsumos(void){
     FILE* arqI;
     if((arqI = fopen("dados\\insumos.ogid", "wb")) == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
     ListaInsumo *v; /*var. para percorrer a lista*/
     if(insumos != NULL){
        for (v = insumos; v->next != NULL; v = v->next);
        while( v != NULL) {
            Insumo ins = v->info;
            if(fwrite(&ins, sizeof(Insumo), 1, arqI) == 1){
                printf("id: %d\nnome: %s\nvalor: %.2lf \n quantidade: %.2lf \n tipo: %s\ndescri: %s\n", ins.insId,  ins.nome, ins.valor, ins.quant, ins.tipo, ins.descri);
            }else{
                printf("erro ao salvar clientes no arquivo insumos.ogid");
            }
           v = v->prev;
        }
     }
     fclose(arqI);
}

void saveServices(void){
     FILE* arqS;
     if((arqS = fopen("dados\\services.ogid", "wb")) == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
     ListaServico *v; /*var. para percorrer a lista*/
     if(services != NULL){
       for (v = services; v->next != NULL; v = v->next);
       while( v != NULL) {
         Servico serv = v->info;
         int i = 0;
         if(fwrite(&serv, sizeof(Servico), 1, arqS) == 1){
             printf("id: %d\n nome: %s\n valorP %.2lf\n valorM %.2lf\n valorG %.2lf\n", serv.serId, serv.nome, serv.valorP, serv.valorM, serv.valorG );
             while  (serv.gastos[i].id_ins != 0 && i < 10){
                   printf("id-ins: %d\n qntdP %.2lf\n qntdM %.2lf\n qntdG %.2lf\n", serv.gastos[i].id_ins, serv.gastos[i].qntdP, serv.gastos[i].qntdM, serv.gastos[i].qntdG);
                   i++;
             }
          }else{
             printf("erro ao salvar clientes no arquivo servicos.ogid");
          }
         v = v->prev;
       }
     }
     fclose(arqS);
}

void saveClient(void){
     FILE* arqC;
     if((arqC = fopen("dados\\client.ogid", "wb")) == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
     ListaCliente *v; /*var. para percorrer a lista*/
     if(clientes != NULL){
       for (v = clientes; v->next != NULL; v = v->next);
       while( v != NULL) {
         Cliente person = v->info;
         if(fwrite(&person, sizeof(Cliente), 1, arqC) == 1){
             printf("id: %d\n nome: %s\n data: %s\n ", person.id, person.nome, person.data);

          }else{
             printf("erro ao salvar clientes no arquivo clientes.ogid");
          }
         v = v->prev;
       }
     }
     fclose(arqC);
}

void saveFuncion(void){
     FILE* arqF;
     if((arqF = fopen("dados\\user.ogid", "wb")) == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
     ListaUsuario *v; /*var. para percorrer a lista*/
     if(funcionarios != NULL){
       for (v = funcionarios; v->next != NULL; v = v->next);
       while( v != NULL) {
         Usuario person = v->info;
         if(fwrite(&person, sizeof(Usuario), 1, arqF) == 1){
             printf("id: %d\nnome: %s\nrg: %s\n ", person.userId, person.nome, person.rg);
          }else{
             printf("erro ao salvar funcionarios no arquivo user.ogid");
          }
         v = v->prev;
       }
     }
     fclose(arqF);
}

void save_veicle(Arvore *a, FILE* arq_vehicle){
    if(!verifica_arv_vazia(a)){
        Veiculo veiculos = a->info;
        int i = 0;
        if(!(fwrite(&veiculos, sizeof(Veiculo), 1, arq_vehicle) != 1)){
             printf("id: %d\nmodelo: %s\nplaca: %s\n", veiculos.cli_id,  veiculos.modelo, veiculos.placa);
             while(veiculos.servicos[i] != 0 && i < 10){
                   printf("serv-id: %d\n", veiculos.servicos[i]);
                   i++;
             }
        }else{
             printf("erro ao salvar veiculos no arquivo vehicles.dat");
        }
        save_veicle(a->esq, arq_vehicle);
        save_veicle(a->dir, arq_vehicle);
    }
}
