#include "header.h"

//functions System

const gchar* get_name_widget(GtkWidget *widget){
     const gchar    *obj_name = NULL;
     GtkBuildable   *name = GTK_BUILDABLE(widget);
     obj_name = gtk_buildable_get_name(name);
     return obj_name;
}

void load_file(GtkWidget *widget){
     const gchar* name;
     name = get_name_widget(widget);

     if(strcmp(name, "carregarClientes") == 0){
        loadFile = 1;
     /*}else if(strcasecmp(name, "carregarVeiculos") == 0){
        loadFile = 2;*/
     }else if(strcasecmp(name, "carregarServicos") == 0){
        loadFile = 3;
     }else if(strcasecmp(name, "carregarInsumos") == 0){
        loadFile = 4;
     }else{
        loadFile = 5;
     }
     //printf("%s\n", name);
     //printf("%d\n", loadFile);
     show_widget(GTK_WIDGET(interface->getfile));
}

void get_file_clientes(void){
     gchar* name;
     gchar way_of_dir[55];
     gchar* way_of_file;
     name = gtk_file_chooser_get_uri     (GTK_FILE_CHOOSER(interface->getfile));
     if(name != NULL){
        way_of_file = &name[8];
        if(loadFile == 1){
         name = strstr(way_of_file, "clientes");
         strcpy(way_of_dir, "backups\\Clientes\\");
        }else if(loadFile == 2){
         name = strstr(way_of_file, "clientes");
         strcpy(way_of_dir, "save\\Veiculos\\");
        }
        else if(loadFile == 3)
         name = strstr(way_of_file, "servicos"),
         strcpy(way_of_dir, "backups\\Servicos\\");
        else if(loadFile == 4)
         name = strstr(way_of_file, "insumos"),
         strcpy(way_of_dir, "backups\\Insumos\\");
        else
         name = strstr(way_of_file, "funcionarios"),
         strcpy(way_of_dir, "backups\\Funcionarios\\");
        if(name != NULL){
            printf("%s\n", name);
            strcat(way_of_dir, name);
            name = strstr(way_of_file, ".ogid");
          if(name != NULL){
             //load file
             printf("%s\n", way_of_dir);
             if(loadFile == 1){
                ListaCliente *list;
                clientes = readClient(way_of_dir, list);
                loadFile = 2;
                get_file_clientes();
                message_of_info("Carregamento do Backup De Clientes \n concluido!");
             }else if(loadFile == 2){
                Arvore* ar;
                vehicles = readVehicles(way_of_dir, ar);
                message_of_info("Carregamento do Backup De Veiculos \n concluido!");
             }else if(loadFile == 3){
                ListaServico *list;
                services = readSevices(way_of_dir, list);
                message_of_info("Carregamento do Backup De Servicos \n concluido!");
             }else if(loadFile == 4){
                ListaInsumo *list;
                insumos = readInsumos(way_of_dir, list);
                message_of_info("Carregamento do Backup De Insumos \n concluido!");
             }else{
                ListaUsuario *list;
                funcionarios = readFuncion(way_of_dir, list);
                message_of_info("Carregamento do Backup De Fucionarios \n concluido!");
             }
             close_widget(GTK_WIDGET (interface->getfile));
          }else
            message_of_error("A extencao do arquivo esta errada! \n so e permitida a extencao '.ogid' .");
        }else
        message_of_error("A extencao do arquivo esta errada! \n so e permitida a extencao '.ogid' .");
     }else
        message_of_error("caminho do aquivo vazio nao foi possivel carregar!");
}

int cria_n_os(int id){
      char* c_id;
	  char* nv;
	  char* n_os;
      int n_os_id;
	  /* pega data atual */
	  n_os = (char*) malloc(51 * sizeof(char));
      c_id = (char*) malloc(20 * sizeof(char));
      nv   = (char*) malloc(20 * sizeof(char));

	  time_t currentTime;
	  struct tm *timeinfo;
	  currentTime = time(NULL);
	  timeinfo = localtime(&currentTime);

	  /*
        Cria a string com os codigos de fomatacao no formato: dia/mes/ano.
      */

	  strftime(n_os, 51, "%d%m%H", timeinfo);
	  itoa(id, c_id, 10);
      itoa(num_treevehicles, nv, 10);
      strcat( n_os, c_id);
      strcat( n_os, nv);

      //printf("nos .: %s \n", n_os);

      n_os_id = atoi(n_os);

	  //printf("nos .: %d \n", n_os_id);

	  return n_os_id;
}

/* Starting all variable with values NULL */
void criaClient(Cliente *person){
     person->data[0]     = 0;
     person->id          = 0;
     person->nome[0]     = 0;
     person->telefone[0] = 0;
}

void criaUsuario(Usuario *person){
     person->ende[0]     = 0;
     person->rg[0]       = 0;
     person->data[0]     = 0;
     person->userId      = 0;
     person->nome[0]     = 0;
     person->telefone[0] = 0;
}

void criaVehicle(Veiculo  *veiculo){
     veiculo->cli_id      = 0;
     veiculo->cor[0]      = 0;
     veiculo->data[0]     = 0;
     veiculo->descri[0]   = 0;
     veiculo->entrada[0]  = 0;
     veiculo->modelo[0]   = 0;
     veiculo->placa[0]    = 0;
     veiculo->saida[0]    = 0;
     veiculo->tamanho[0]  = 0;
     veiculo->servicos[0] = 0;
}

//functions InterFace
/* widget & windows */
void  show_widget(GtkWidget* win){
      gtk_widget_show(win);
}

void  close_widget(GtkWidget* win){
      gtk_widget_hide(win);
}

/* entry */
void valida_date_m(GtkEntryBuffer *buffer){
     gint totalnum = NULL;
     totalnum = gtk_entry_buffer_get_length(buffer);
     const gchar *numero = NULL;
     numero = gtk_entry_buffer_get_text(buffer);
     if(totalnum > 0 && totalnum < 7  && totalnum != 3){
        if(!(numero[totalnum-1] >= '0' && numero[totalnum-1] <= '9')){
         gtk_entry_buffer_delete_text(buffer,totalnum-1,totalnum);
         message_of_error("Erro utilize apenas numeros! ex: 123 ");
        }
     }else  if (totalnum == 3){
        if(!(numero[totalnum-1] == '-')){
         gtk_entry_buffer_delete_text(buffer,totalnum-1,totalnum);
         message_of_error("Erro utilize '-' para separar as datas ");
        }
     }
}

void valida_date_a(GtkEntryBuffer *buffer){
     gint totalnum = NULL;
     totalnum = gtk_entry_buffer_get_length(buffer);
     const gchar *numero = NULL;
     numero = gtk_entry_buffer_get_text(buffer);
     if(totalnum > 0 && totalnum < 10  && totalnum != 3 && totalnum != 6){
        if(!(numero[totalnum-1] >= '0' && numero[totalnum-1] <= '9')){
         gtk_entry_buffer_delete_text(buffer,totalnum-1,totalnum);
         message_of_error("Erro utilize apenas numeros! ex: 123 ");
        }
     }else  if (totalnum == 3 || totalnum == 6){
        if(!(numero[totalnum-1] == '-')){
         gtk_entry_buffer_delete_text(buffer,totalnum-1,totalnum);
         message_of_error("Erro utilize '-' para separar as datas ");
        }
     }
}


void valida_char(GtkEntryBuffer *buffer){
     gint totalchar = gtk_entry_buffer_get_length(buffer);
     const gchar *name = NULL;
     name = gtk_entry_buffer_get_text(buffer);
     if( !((name[totalchar-1] >= 'A' && name[totalchar-1] <= 'Z' )
         ||(name[totalchar-1] >= 'a' && name[totalchar-1] <= 'z' ))){
        gtk_entry_buffer_delete_text(buffer,totalchar-1,totalchar);
     }
}

void valida_end(GtkEntryBuffer *buffer){
     gint totalchar = gtk_entry_buffer_get_length(buffer);
     const gchar *end = NULL;
     end = gtk_entry_buffer_get_text(buffer);
     if( !((end[totalchar-1] >= 'A' && end[totalchar-1] <= 'Z' )
         ||(end[totalchar-1] >= 'a' && end[totalchar-1] <= 'z' )
         ||(end[totalchar-1] >= '0' && end[totalchar-1] <= '9' )
         || end[totalchar-1] == ' ' || end[totalchar-1] == ',')){
         gtk_entry_buffer_delete_text(buffer,totalchar-1,totalchar);
     }
}

void valida_char_esp(GtkEntryBuffer *buffer){
     gint totalchar = gtk_entry_buffer_get_length(buffer);
     const gchar *name = NULL;
     name = gtk_entry_buffer_get_text(buffer);
     if( !(name[totalchar-1] == ' ' || (name[totalchar-1] >= 'A' && name[totalchar-1] <= 'Z' )
         ||(name[totalchar-1] >= 'a' && name[totalchar-1] <= 'z' ))){
        gtk_entry_buffer_delete_text(buffer,totalchar-1,totalchar);
     }
     //char esp...
     /*if((name[totalchar-1] >= '!' && name[totalchar-1] <= '@')
        || (name[totalchar-1] >= '[' && name[totalchar-1] <= '`')
        || (name[totalchar-1] >= '{' && name[totalchar-1] <= '~')){
        gtk_entry_buffer_delete_text(buffer,totalchar-1,totalchar);
        message_of_error("Erro utilize apenas caracteres! ex.Abc");
     }*/
}

void valida_num(GtkEntryBuffer *buffer){
     gint totalnum = NULL;
     totalnum = gtk_entry_buffer_get_length(buffer);
     const gchar *numero = NULL;
     numero = gtk_entry_buffer_get_text(buffer);
     if(totalnum > 0){
        if(!(numero[totalnum-1] >= '0' && numero[totalnum-1] <= '9')){
         gtk_entry_buffer_delete_text(buffer,totalnum-1,totalnum);
         message_of_error("Erro utilize apenas numeros! ex: 123 ");
        }
     }
}

void valida_data(GtkEntryBuffer *buffer){
     gint totalnum = NULL;
     totalnum = gtk_entry_buffer_get_length(buffer);
     const gchar *numero = NULL;
     numero = gtk_entry_buffer_get_text(buffer);
     if(totalnum > 0){
        if(!((numero[totalnum-1] >= '0' && numero[totalnum-1] <= '9') || numero[totalnum-1] == '/')){
         gtk_entry_buffer_delete_text(buffer,totalnum-1,totalnum);
         message_of_error("Erro utilize apenas numeros e ou '/'! ex: 19/09/2015 ");
        }
     }
}

void valida_valor(GtkEntryBuffer *buffer){
     gint totalnum = NULL;
     totalnum = gtk_entry_buffer_get_length(buffer);
     const gchar *numero = NULL;
     numero = gtk_entry_buffer_get_text(buffer);
     int i = 0;
     int virgula = 0;

     if(totalnum > 0){

        while(i < totalnum){
            //não é valido
            if(!(numero[i] == ',' || (numero[i] >= '0' && numero[i] <= '9'))){
               gtk_entry_buffer_delete_text(buffer, i, i+1);
               message_of_error("Erro utilize apenas numeros, ex: 123 \n e para valores quebrados digite ',' !");
            }else{
               if(numero[i] == ',' && virgula == 0){
                  virgula++;
               }else if(numero[i] == ','){
                  gtk_entry_buffer_delete_text(buffer, i, i+1);
                  message_of_error("Erro utilize apenas uma ',' !");
               }
            }
          i++;
        }
        /*funciona
          if(!(numero[totalnum-1] == ',' || (numero[totalnum-1] >= '0' && numero[totalnum-1] <= '9'))){
            gtk_entry_buffer_delete_text(buffer,totalnum-1,totalnum);
            message_of_error("Erro utilize apenas numeros, ex: 123 \n e para valores quebrados digite ',' !");
        }*/
     }
}

void valida_descri(GtkTextBuffer *text){
     gint total;
     total = gtk_text_buffer_get_char_count(text);

     if(total >= 550){
        GtkTextIter iter,iter_end;
        gtk_text_buffer_get_iter_at_offset  (text, &iter, 551);
        gtk_text_buffer_get_end_iter        (text, &iter_end);
        gtk_text_buffer_delete              (text, &iter, &iter_end);
        message_of_error("O numero maximo de caracteres e 500");
     }else if(total >= 501){
        message_of_error("O numero maximo de caracteres e 500");
     }
}

/*set number for phone*/
void ver_numPhone(GtkEntryBuffer *buffer){
     gint totalnum = NULL;
     totalnum = gtk_entry_buffer_get_length(buffer);
     const gchar *phone = NULL;
     phone = gtk_entry_buffer_get_text(buffer);
     if(!(phone[totalnum-1] != ' ' && (phone[totalnum-1] >= '0' && phone[totalnum-1] <= '9' ))){
            gtk_entry_buffer_delete_text(buffer,totalnum-1,totalnum);
     }
}

//entry for number hours
void ver_hours(GtkEntryBuffer *buffer){
     gint totalnum = gtk_entry_buffer_get_length(buffer);
     const gchar *input = NULL;
     input = gtk_entry_buffer_get_text(buffer);
     if((totalnum-1 != 2) && input[totalnum-1] != ' ' && (input[totalnum-1] >= '0' && input[totalnum-1] <= '9' )) {
       if((totalnum-1 == 0) && (!(input[totalnum-1] >= '0' && input[totalnum-1] <= '2' ))){
           gtk_entry_buffer_delete_text(buffer,totalnum-1,totalnum);
       }
       if((totalnum-1 == 3) && (!(input[totalnum-1] >= '0' && input[totalnum-1] <= '6' ))){
            gtk_entry_buffer_delete_text(buffer,totalnum-1,totalnum);
       }
     }else if(totalnum-1 == 2){
        if(!(input[totalnum-1] == ':'))
          gtk_entry_buffer_delete_text(buffer,totalnum-1,totalnum);
     }else{
          gtk_entry_buffer_delete_text(buffer,totalnum-1,totalnum);
     }
}

//entry for number hours
void ver_plac(GtkEntryBuffer *buffer){
     gint totalnum = gtk_entry_buffer_get_length(buffer);
     const gchar *input = NULL;
     input = gtk_entry_buffer_get_text(buffer);
     if((totalnum-1 < 3) && (!(input[totalnum-1] >= 'a' && input[totalnum-1] <= 'z' ))) {
          gtk_entry_buffer_delete_text(buffer,totalnum-1,totalnum);
     }else if(totalnum-1 > 3 && input[totalnum-1] != ' ' && (!(input[totalnum-1] >= '0' && input[totalnum-1] <= '9' ))){
          gtk_entry_buffer_delete_text(buffer,totalnum-1,totalnum);
     }else if(totalnum-1 == 3){
        if(!(input[totalnum-1] == '-'))
          gtk_entry_buffer_delete_text(buffer,totalnum-1,totalnum);
     }
}

/* Assistant */
void search_vehicle(GtkEntry* entryVeh){
     gchar *id_vei;
     id_vei = gtk_entry_get_text(entryVeh);
     GtkTreeIter iter;
     if(*id_vei && id_vei != NULL ){
        Arvore *no = buscar(vehicles, id_vei);
        if(no != NULL){
                ListaCliente *person = procurarlistcli (clientes, no->info.cli_id);
                gtk_list_store_append (GTK_LIST_STORE (interface->treemodel_insert_v), &iter);
                gtk_list_store_set    (GTK_LIST_STORE (interface->treemodel_insert_v), &iter,
                                       INSERT_VEHICLE_PLACA,        no->info.placa,
                                       INSERT_VEHICLE_MODELO,       no->info.modelo,
                                       INSERT_VEHICLE_PROPRIETARIO, person->info.nome,
                                       INSERT_VEHICLE_COR,          no->info.cor,
                                       INSERT_VEHICLE_TAMANHO,      no->info.tamanho, -1);
                pega_hora(stringTime);
                gtk_entry_buffer_set_text(iassistant->bufferInput, stringTime, strlen(stringTime));
                gtk_text_buffer_set_text(iassistant->bufferDescri, no->info.descri, strlen(no->info.descri));

                Fila* noFila = procurar_Ele(id_vei);

                gtk_widget_show(GTK_WIDGET (interface->insertVehicle));

                if( noFila != NULL){
                   closed_assistant(GTK_WIDGET (interface->insertVehicle));
                   error_message("Veiculo ja esta na Fila De Espera!");
                }

        }else{
            error_message("Veiculo nao encontrado!");
        }
     }else{
           error_message("Digite a Placa do veiculo a ser  pesquisado");
     }
}

void applySearchInsertVehicle(GtkAssistant* assistant){
     gchar  *id_vei;
     GtkTreeIter iterP;
     GtkTextIter strat;
     GtkTextIter enditer;

     if(gtk_tree_model_get_iter_first(interface->treemodel_insert_v, &iterP)){
        //Get for conteudo of tree
        gtk_tree_model_get (interface->treemodel_insert_v, &iterP, 0, &id_vei, -1);
        //select cliente's row of people
        Arvore *no  = buscar(vehicles, id_vei);
        ListaCliente   *person = procurarlistcli (clientes, no->info.cli_id);
        GtkTreeIter iter;
        //info data of day
        //day
        pega_data(stringTime);
        //inside
        strcpy(no->info.entrada, gtk_entry_buffer_get_text(iassistant->bufferInput));
        //outside
        strcpy(no->info.saida,   gtk_entry_buffer_get_text(iassistant->bufferOutput));
        gtk_text_buffer_get_start_iter (iassistant->bufferDescri, &strat);
        gtk_text_buffer_get_end_iter        (iassistant->bufferDescri, &enditer);
        strcpy(no->info.descri, gtk_text_buffer_get_text(iassistant->bufferDescri, &strat, &enditer, FALSE));
        GtkTreeIter iters;
        gboolean tf;
        gint serv_id;
        int i = 0;
        double valorserv = 0;
        while(i < 10){
               no->info.servicos[i] = 0;
               i++;
         }

         i = 0;

         if(gtk_tree_model_get_iter_first(interface->treemodel_ser, &iters)){
            //pega o proximo
            do{
               gtk_tree_model_get(interface->treemodel_ser,  &iters,
                                  COLUMN_SERV_X,   &tf,
                                  COLUMN_SERV_ID,  &serv_id, -1);
               if(tf){
                  //save services
                  no->info.servicos[i] = serv_id;
                  //retire insumo
                  ListaServico *ser = services; //var. para percorrer a lista
                  while(ser->info.serId != serv_id && ser != NULL){
                     ser = ser->next;
                  }
                  if(strcmp(no->info.tamanho, "Pequeno") == 0){
                            valorserv += ser->info.valorP;
                  }else if(strcmp(no->info.tamanho, "Medio") == 0){
                            valorserv += ser->info.valorM;
                  }else{
                            valorserv += ser->info.valorG;
                  }
                  int j = 0;
                  if(ser != NULL){
                    while(ser->info.gastos[j].id_ins != 0 && j < 10){
                      ListaInsumo *ins = insumos;
                      while(ins->info.insId != ser->info.gastos[j].id_ins && ins != NULL){
                            ins = ins->next;
                      }
                      if(ins != NULL){
                        if(strcmp(no->info.tamanho, "Pequeno") == 0){
                            ins->info.quant -= ser->info.gastos[j].qntdP;
                        }else if(strcmp(no->info.tamanho, "Medio") == 0){
                            ins->info.quant -= ser->info.gastos[j].qntdM;
                        }else{
                            ins->info.quant -= ser->info.gastos[j].qntdG;
                        }
                      }
                      j++;
                    }
                  }
                  i++;
               }
             }while(gtk_tree_model_iter_next (interface->treemodel_ser, &iters)  && i < 10);
         }

        gtk_list_store_append (GTK_LIST_STORE (interface->treemodel_index), &iter);
        gtk_list_store_set    (GTK_LIST_STORE (interface->treemodel_index), &iter,
                                 COLUMN_ITEM_N,            num_treevehicles,
                                 COLUMN_ITEM_ENTRADA,      no->info.entrada,
                                 COLUMN_ITEM_SAIDA,        no->info.saida,
                                 COLUMN_ITEM_IDVEHICLES,   no->info.placa,
                                 COLUMN_ITEM_VEICULO,      no->info.modelo,
                                 COLUMN_ITEM_PROPREITARIO, person->info.nome,
                                 COLUMN_ITEM_N_OS,         cria_n_os(person->info.id),
                                 COLUMN_ITEM_VALOR,        g_strdup_printf ("%.2f", valorserv),
                                 COLUMN_ITEM_GORJETA,      g_strdup_printf ("%.2f", 0.00),
                                 COLUMN_ITEM_OBS,          no->info.descri,
                                 COLUMN_ITEM_PROCESSO,     0,
                                 COLUMN_ITEM_EDITAR,    TRUE, -1);
        if(num_vehi_aten >= quant_fun){
            //int minutos, segundos;

            if(strcmp(no->info.tamanho, "Pequeno") == 0){
                 /*minutos =  30 / quant_fun;
                 segundos = quant_fun % 30;
                 if(segundos > 4){
                    minutos += 1;
                    segundos = 0;
                 }else{
                    segundos *= 10;
                 }
                 timewait(stringwaitTime,0, minutos, segundos);*/

                 timewait(stringwaitTime,0, 30, 0);
            }else if(strcmp(no->info.tamanho, "Medio") == 0){
                 /*minutos =  50 / quant_fun;
                 segundos = quant_fun % 50;
                 if(segundos > 4){
                    minutos += 1;
                    segundos = 0;
                 }else{
                    segundos *= 10;
                 }
                 timewait(stringwaitTime,0, minutos, segundos);*/

                 timewait(stringwaitTime,0, 50, 0);

            }else{
                 /*minutos =  59 / quant_fun;
                 segundos = quant_fun % 59;
                 if(segundos > 4){
                    minutos += 1;
                    segundos = 0;
                 }else{
                    segundos *= 10;
                 }
                 timewait(stringwaitTime, 0, minutos, segundos);*/
                 timewait(stringwaitTime,0, 59, 59);
            }

            //printf("minutos: %d \n segundos: %d", minutos, segundos);

         }else{
             num_vehi_aten++;
         }

         vehiclesEqueue = enqueueFila (vehiclesEqueue, no->info);

         num_treevehicles++;
     }
}

void apply_insert_vehicle(GtkAssistant *assistant){
     GtkTreeIter iter;
     GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_veicli);
     if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
         //Get for conteudo of tree
          gint id_person;
          gtk_tree_model_get (interface->treemodel_cli, &iter, 0, &id_person, -1);

          //select cliente's row of people
          ListaCliente *no = procurarlistcli(clientes, id_person);
          Cliente person = no->info;

          Veiculo veiculo_cliente;
    //info data of client
          veiculo_cliente.cli_id = person.id;

    //info data of day
         //day
         pega_data(stringTime);
         strcpy(veiculo_cliente.data, stringTime);

         //inside
         strcpy(veiculo_cliente.entrada, gtk_entry_buffer_get_text(iassistant->bufferInput));

         //outside
         strcpy(veiculo_cliente.saida, gtk_entry_buffer_get_text(iassistant->bufferOutput));

       //info car
         //color
         strcpy(veiculo_cliente.cor, gtk_entry_buffer_get_text(iassistant->bufferCor));

         //carId
         strcpy(veiculo_cliente.placa, gtk_entry_buffer_get_text(iassistant->bufferPlaca));

         //model
         strcpy(veiculo_cliente.modelo, gtk_entry_buffer_get_text(iassistant->bufferModelo));

         //length
         strcpy(veiculo_cliente.tamanho, gtk_combo_box_get_active_text(iassistant->tamanho));

         //desc
         GtkTextIter strat;
         gtk_text_buffer_get_start_iter (iassistant->bufferDescri , &strat);
         GtkTextIter enditer;
         gtk_text_buffer_get_end_iter        (iassistant->bufferDescri , &enditer);
         strcpy(veiculo_cliente.descri, gtk_text_buffer_get_text(iassistant->bufferDescri , &strat, &enditer, FALSE));
         GtkTreeIter iters;
         gboolean tf = FALSE;
         gint serv_id;
         int i = 0;
         double valorserv = 0;
         while(i < 10){
               veiculo_cliente.servicos[i] = 0;
               i++;
         }
         i = 0;
         if(gtk_tree_model_get_iter_first(GTK_TREE_MODEL (interface->treemodel_ser), &iters)){
            //pega o proximo
            do{
               gtk_tree_model_get(interface->treemodel_ser,  &iters,
                                  COLUMN_SERV_X,   &tf,
                                  COLUMN_SERV_ID,  &serv_id, -1);
               if(tf  == 1){
                  //save services
                  veiculo_cliente.servicos[i] = serv_id;
                  //retire insumo
                  ListaServico *ser = services; //var. para percorrer a lista
                  while(ser->info.serId != serv_id && ser != NULL){
                     ser = ser->next;
                  }
                  if(strcmp(veiculo_cliente.tamanho, "Pequeno") == 0){
                            valorserv += ser->info.valorP;
                  }else if(strcmp(veiculo_cliente.tamanho, "Medio") == 0){
                            valorserv += ser->info.valorM;
                  }else{
                            valorserv += ser->info.valorG;
                  }
                  int j = 0;
                  if(ser != NULL){
                    while(ser->info.gastos[j].id_ins != 0 && j < 10){
                      ListaInsumo *ins = insumos;
                      while(ins->info.insId != ser->info.gastos[j].id_ins && ins != NULL){
                            ins = ins->next;
                      }
                      if(ins != NULL){
                        if(strcmp(veiculo_cliente.tamanho, "Pequeno") == 0){
                            ins->info.quant -= ser->info.gastos[j].qntdP;
                        }else if(strcmp(veiculo_cliente.tamanho, "Medio") == 0){
                            ins->info.quant -= ser->info.gastos[j].qntdM;
                        }else{
                            ins->info.quant -= ser->info.gastos[j].qntdG;
                        }
                      }
                      j++;
                    }
                  }
                  i++;
               }
             }while(gtk_tree_model_iter_next (interface->treemodel_ser, &iters)  && i < 10);
         }
         vehicles = inserir(vehicles, veiculo_cliente);
                GtkTreeIter iter2;
          //insert in list from page Gerenciar-Clientes
                gtk_list_store_append (GTK_LIST_STORE (interface->treemodel_vei), &iter2);
                gtk_list_store_set    (GTK_LIST_STORE (interface->treemodel_vei), &iter2,
                                 COLUMN_VEHICLE_PLACA,        veiculo_cliente.placa,
                                 COLUMN_VEHICLE_MODELO,       veiculo_cliente.modelo,
                                 COLUMN_VEHICLE_PROPRIETARIO, person.nome,
                                 COLUMN_VEHICLE_ENTRADA,      veiculo_cliente.entrada,
                                 COLUMN_VEHICLE_SAIDA,        veiculo_cliente.saida,
                                 COLUMN_VEHICLE_COR,          veiculo_cliente.cor,
                                 COLUMN_VEHICLE_TAMANHO,      veiculo_cliente.tamanho,
                                 COLUMN_VEHICLE_CLI_ID,       person.id, -1);
                gtk_list_store_append (GTK_LIST_STORE (interface->treemodel_index), &iter2);
                gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_index), &iter2,
                                 COLUMN_ITEM_N,            num_treevehicles,
                                 COLUMN_ITEM_NOME,         person.nome,
                                 COLUMN_ITEM_ENTRADA,      veiculo_cliente.entrada,
                                 COLUMN_ITEM_SAIDA,        veiculo_cliente.saida,
                                 COLUMN_ITEM_IDVEHICLES,   veiculo_cliente.placa,
                                 COLUMN_ITEM_VEICULO,      veiculo_cliente.modelo,
                                 COLUMN_ITEM_PROPREITARIO, person.nome,
                                 COLUMN_ITEM_N_OS,         cria_n_os(person.id),
                                 COLUMN_ITEM_VALOR,        g_strdup_printf ("%.2f", valorserv),
                                 COLUMN_ITEM_GORJETA,      g_strdup_printf ("%.2f", 0.00),
                                 COLUMN_ITEM_OBS,          veiculo_cliente.descri,
                                 COLUMN_ITEM_PROCESSO,     0,
                                 COLUMN_ITEM_EDITAR,    TRUE, -1);
            if(num_vehi_aten >= quant_fun){
                //int minutos, segundos;

                if(strcmp(veiculo_cliente.tamanho, "Pequeno") == 0){
                     /*minutos =  30 / quant_fun;
                     segundos = quant_fun % 30;
                     if(segundos > 4){
                        minutos += 1;
                        segundos = 0;
                     }else{
                        segundos *= 10;
                     }
                     timewait(stringwaitTime,0, minutos, segundos);*/
                     timewait(stringwaitTime, 0, 30, 0);
                }else if(strcmp(veiculo_cliente.tamanho, "Medio") == 0){
                     /*minutos =  50 / quant_fun;
                     segundos = quant_fun % 50;
                     if(segundos > 4){
                        minutos += 1;
                        segundos = 0;
                     }else{
                        segundos *= 10;
                     }
                     timewait(stringwaitTime,0, minutos, segundos);*/
                     timewait(stringwaitTime,0, 50, 0);
                }else{
                     /*minutos =  59 / quant_fun;
                     segundos = quant_fun % 59;
                     if(segundos > 4){
                        minutos += 1;
                        segundos = 0;
                     }else{
                        segundos *= 10;
                     }
                     timewait(stringwaitTime, 0, minutos, segundos);*/
                     timewait(stringwaitTime,0, 59, 59);
                }

            //printf("minutos: %d \n segundos: %d", minutos, segundos);

         }else{
             num_vehi_aten++;
         }
            vehiclesEqueue = enqueueFila (vehiclesEqueue, veiculo_cliente);
            num_treevehicles++;
     }
}

void changes_vehicle(GtkAssistant *assistant){
  GtkTreeIter iter, iter_combox;
  GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_vei);
  GtkTreeModel *combox_model =  gtk_combo_box_get_model(iassistant->alt_tamanho);
  GtkTreePath *path;
  gint id_person;
  gchar *id_vei;
  Arvore* no;
  if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
      path = gtk_tree_model_get_path (interface->treemodel_vei, &iter);

      //Get for conteudo of tree
      gtk_tree_model_get (interface->treemodel_vei, &iter, 7, &id_person, -1);
      gtk_tree_model_get (interface->treemodel_vei, &iter, 0, &id_vei, -1);

      no = buscar( vehicles, id_vei);

      gtk_entry_buffer_set_text(iassistant->bufferInput,   no->info.entrada, strlen(no->info.entrada));
      gtk_entry_buffer_set_text(iassistant->bufferOutput,  no->info.saida, strlen(no->info.saida));
      gtk_entry_buffer_set_text(iassistant->bufferPlaca,   no->info.placa, strlen(no->info.placa));
      gtk_entry_buffer_set_text(iassistant->bufferModelo,  no->info.modelo, strlen(no->info.modelo));
      gtk_entry_buffer_set_text(iassistant->bufferCor,     no->info.cor, strlen(no->info.cor));
      if(gtk_tree_model_get_iter_first (combox_model, &iter_combox)){
         gtk_combo_box_set_active_iter (iassistant->alt_tamanho, &iter_combox);
      }
      gtk_text_buffer_set_text( iassistant->bufferDescri, no->info.descri, strlen(no->info.descri));
      gtk_tree_path_free (path);
      gtk_widget_show (GTK_WIDGET (assistant));
    }
}

void delete_vehicle(GtkWidget *widget, gpointer data){
  GtkTreeIter iter;
  GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_vei);
  if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
      GtkTreePath *path;
      path = gtk_tree_model_get_path (interface->treemodel_vei, &iter);


      //Get for conteudo of tree

      //date of client
      /*gint id_person;
      gtk_tree_model_get (interface->treemodel_vei, &iter, 7, &id_person, -1);
      ListaCliente*   no_person = procurarlistcli (clientes, id_person);*/

      gchar *id_vei;
      gtk_tree_model_get (interface->treemodel_vei, &iter, 0, &id_vei, -1);


      Arvore* no_vehicle = buscar(vehicles, id_vei);

      vehicles = remover_vehicle(vehicles, no_vehicle->info);

      gtk_list_store_remove (GTK_LIST_STORE (interface->treemodel_vei), &iter);

      gtk_tree_path_free (path);
    }
}

void edit_vehicle(GtkAssistant *assistant){
          GtkTreeIter iter2;
          gint  *cli_id;
          GtkTreeSelection *selection2 = gtk_tree_view_get_selection (interface->treeview_vei);
          if (gtk_tree_selection_get_selected (selection2, NULL, &iter2)){
                 GtkTreeIter iter;
                 GtkTreeSelection *selection3 = gtk_tree_view_get_selection (interface->treeview_alt_veicli);
                 if (gtk_tree_selection_get_selected (selection3, NULL, &iter)){

                      GtkTreePath *path1;

                      path1 = gtk_tree_model_get_path (interface->treemodel_cli, &iter);
                      gtk_tree_path_free (path1);

                      //Get for conteudo of tree
                      gint id_person;
                      gtk_tree_model_get (interface->treemodel_cli, &iter, 0, &id_person, -1);

                      //select vehicle's tree of vehicles
                      gchar *id_vei;
                      gtk_tree_model_get (interface->treemodel_vei, &iter2, 0, &id_vei, -1);

                      Arvore* no = buscar(vehicles, id_vei);

                //info data of client
                      if(no->info.cli_id != id_person)
                         no->info.cli_id = id_person;
                //info data of day
                     //select cliente's row of people
                     ListaCliente *person = procurarlistcli(clientes, id_person);
                     //day
                     pega_data(stringTime);
                     strcpy(no->info.data, stringTime);

                     //inside
                     strcpy(no->info.entrada, gtk_entry_buffer_get_text(iassistant->bufferInput));

                     //outside
                     strcpy(no->info.saida, gtk_entry_buffer_get_text(iassistant->bufferOutput));
                //info car
                     //color
                     strcpy(no->info.cor, gtk_entry_buffer_get_text(iassistant->bufferCor));

                     //carId
                     strcpy(no->info.placa, gtk_entry_buffer_get_text(iassistant->bufferPlaca));

                     //model
                     strcpy(no->info.modelo, gtk_entry_buffer_get_text(iassistant->bufferModelo));

                     //length
                      strcpy(no->info.tamanho, gtk_combo_box_get_active_text(iassistant->alt_tamanho));

                      GtkTreeIter iters;
                      gboolean tf;
                      gint serv_id;
                      int i = 0;
                     double valorserv = 0;
                     while(i < 10){
                           no->info.servicos[i] = 0;
                           i++;
                     }
                     i = 0;
                     if(gtk_tree_model_get_iter_first(interface->treemodel_ser, &iters)){
                        //pega o proximo
                        do{
                           gtk_tree_model_get(interface->treemodel_ser,  &iters,
                                              COLUMN_SERV_X,   &tf,
                                              COLUMN_SERV_ID,  &serv_id, -1);
                           if(tf){
                              //save services
                              no->info.servicos[i] = serv_id;
                              //retire insumo
                              ListaServico *ser = services; //var. para percorrer a lista
                              while(ser->info.serId != serv_id && ser != NULL){
                                 ser = ser->next;
                              }
                              if(strcmp(no->info.tamanho, "Pequeno") == 0){
                                        valorserv += ser->info.valorP;
                              }else if(strcmp(no->info.tamanho, "Medio") == 0){
                                        valorserv += ser->info.valorM;
                              }else{
                                        valorserv += ser->info.valorG;
                              }
                              int j = 0;
                              if(ser != NULL){
                                while(ser->info.gastos[j].id_ins != 0 && j < 10){
                                  ListaInsumo *ins = insumos;
                                  while(ins->info.insId != ser->info.gastos[j].id_ins && ins != NULL){
                                        ins = ins->next;
                                  }
                                  if(ins != NULL){
                                    if(strcmp(no->info.tamanho, "Pequeno") == 0){
                                        ins->info.quant -= ser->info.gastos[j].qntdP;
                                    }else if(strcmp(no->info.tamanho, "Medio") == 0){
                                        ins->info.quant -= ser->info.gastos[j].qntdM;
                                    }else{
                                        ins->info.quant -= ser->info.gastos[j].qntdG;
                                    }
                                  }
                                  j++;
                                }
                              }
                              i++;
                           }
                         }while(gtk_tree_model_iter_next (interface->treemodel_ser, &iters)  && i < 10);
                        }
                    //desc
                     GtkTextIter strat;
                     gtk_text_buffer_get_start_iter (iassistant->bufferDescri, &strat);
                     GtkTextIter enditer;
                     gtk_text_buffer_get_end_iter        (iassistant->bufferDescri, &enditer);
                     strcpy(no->info.descri, gtk_text_buffer_get_text(iassistant->bufferDescri, &strat, &enditer, FALSE));

                    //Get for conteudo of
                    gtk_tree_model_get (interface->treemodel_vei, &iter2, 0, &cli_id, -1);
                    //insert in list from page Gerenciar-Clientes
                     gchar *old_placa;
                     gchar *old_modelo;
                     gchar *old_proprietario;
                     gchar *old_entrada;
                     gchar *old_saida;
                     gchar *old_cor;
                     gchar *old_tamanho;
                     gint  *old_id;
                     gtk_tree_model_get (GTK_TREE_MODEL (interface->treemodel_vei), &iter2,
                                 COLUMN_VEHICLE_PLACA,        &old_placa,
                                 COLUMN_VEHICLE_MODELO,       &old_modelo,
                                 COLUMN_VEHICLE_PROPRIETARIO, &old_proprietario,
                                 COLUMN_VEHICLE_ENTRADA,      &old_entrada,
                                 COLUMN_VEHICLE_SAIDA,        &old_saida,
                                 COLUMN_VEHICLE_COR,          &old_cor,
                                 COLUMN_VEHICLE_TAMANHO,      &old_tamanho,
                                 COLUMN_VEHICLE_CLI_ID,       &old_id, -1);
                     g_free (old_placa);
                     g_free (old_modelo);
                     g_free (old_proprietario);
                     g_free (old_entrada);
                     g_free (old_saida);
                     g_free (old_cor);
                     g_free (old_tamanho);
                     g_free (old_id);
                     gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_vei), &iter2,
                                        COLUMN_VEHICLE_PLACA,        no->info.placa,
                                        COLUMN_VEHICLE_MODELO,       no->info.modelo,
                                        COLUMN_VEHICLE_PROPRIETARIO, person->info.nome,
                                        COLUMN_VEHICLE_ENTRADA,      no->info.entrada,
                                        COLUMN_VEHICLE_SAIDA,        no->info.saida,
                                        COLUMN_VEHICLE_COR,          no->info.cor,
                                        COLUMN_VEHICLE_TAMANHO,      no->info.tamanho,
                                        COLUMN_VEHICLE_CLI_ID,       cli_id, -1);

            }
    }
}

void applyAssistantUsuario(GtkAssistant *assistant){
     int id = 1;
     //get id person
     if(funcionarios != NULL) id += funcionarios->info.userId;

     /*Criando Cliente*/
     Usuario person;
     criaUsuario(&person);
     person.userId = id;

     //name
     strcpy(person.nome, gtk_entry_buffer_get_text(iassistant->bufferName));

     //phone
     strcpy(person.telefone, gtk_entry_buffer_get_text(iassistant->bufferPhone));

     //name
     strcpy(person.rg, gtk_entry_buffer_get_text(iassistant->bufferRg));

     //phone
     strcpy(person.ende, gtk_entry_buffer_get_text(iassistant->bufferEnd));

     //add day for client
     pega_data(stringTime);
     strcpy(person.data, stringTime);

    //insert in list from page Gerenciar-Users
    GtkTreeIter iter;
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
             COLUMN_USER_DATA,    person.data, -1);
     //insert person in Fila
     if(id < 200000){
        funcionarios = inserirlistusu(funcionarios, person);
     }else{
        message_of_error("O Numero de cadastros chegou a 200.000!");
     }
}

void  open_assistantUsu_Alt(GtkAssistant* assistant){
      GtkTreeIter iter;
      GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_usu);
      if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
          //Get for conteudo of tree
          gint id_person;
          gtk_tree_model_get (interface->treemodel_usu, &iter, COLUMN_USER_ID, &id_person, -1);

          //find insumos
          ListaUsuario* no = procurarlistusu(funcionarios, id_person);

          //set_text
          gtk_entry_buffer_set_text(iassistant->bufferName,   no->info.nome,   strlen(no->info.nome));
          gtk_entry_buffer_set_text(iassistant->bufferPhone,  no->info.telefone, strlen(no->info.telefone));
          gtk_entry_buffer_set_text(iassistant->bufferRg,     no->info.rg ,   strlen(no->info.rg));
          gtk_entry_buffer_set_text(iassistant->bufferEnd,    no->info.ende,  strlen(no->info.ende));

          gtk_widget_show_now(GTK_WIDGET(assistant));
      }
}

void  apply_assistantUsu_Alt(GtkAssistant* assistant){
      GtkTreeIter iter;
      GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_usu);
      if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
         //Get for conteudo of tree
         gint id_person;
         gtk_tree_model_get (interface->treemodel_usu, &iter, COLUMN_USER_ID, &id_person, -1);

         //find insumos
         ListaUsuario* no = procurarlistusu(funcionarios, id_person);

         Usuario person;
         person.userId = id_person;
         strcpy(person.nome, gtk_entry_buffer_get_text(iassistant->bufferName));
         strcpy(person.telefone, gtk_entry_buffer_get_text(iassistant->bufferPhone));
         strcpy(person.rg, gtk_entry_buffer_get_text(iassistant->bufferRg));
         strcpy(person.ende, gtk_entry_buffer_get_text(iassistant->bufferEnd));
         strcpy(person.data, no->info.data);

         no->info = person;

         gchar *old_name;
         gchar *old_telefone;
         gchar *old_rg;
         gchar *old_end;
         gtk_tree_model_get (interface->treemodel_usu, &iter,
                             COLUMN_USER_NOME,      &old_name,
                             COLUMN_USER_TELFONE,   &old_telefone,
                             COLUMN_USER_RG,        &old_rg,
                             COLUMN_USER_END,       &old_end,-1);
         g_free (old_name);
         g_free (old_telefone);
         g_free (old_rg);
         g_free (old_end);

         gtk_list_store_set(GTK_LIST_STORE (interface->treemodel_usu), &iter,
                             COLUMN_USER_NOME,      &person.nome,
                             COLUMN_USER_TELFONE,   &person.telefone,
                             COLUMN_USER_RG,        &person.rg,
                             COLUMN_USER_END,       &person.ende,-1);
      }
}

void delete_user(void){
     GtkTreeIter iter;
     GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_usu);
     if (gtk_tree_selection_get_selected (selection, NULL, &iter)){

         GtkTreePath *path;

         path = gtk_tree_model_get_path (interface->treemodel_usu, &iter);

         //Get for conteudo of tree
         gint id_user;
         gtk_tree_model_get (interface->treemodel_usu, &iter, COLUMN_USER_ID, &id_user, -1);

         funcionarios =  removerlistusu(funcionarios, id_user);

         gtk_list_store_remove (GTK_LIST_STORE (interface->treemodel_usu), &iter);

         gtk_tree_path_free (path);
    }
}

void applyAssistantClientes(GtkAssistant *assistant){
     int id = 1;
     //get id person
     if(clientes != NULL) id += clientes->info.id;

     /*Criando Cliente*/
     Cliente person;
     criaClient(&person);
     person.id = id;

     //name
     strcpy(person.nome, gtk_entry_buffer_get_text(iassistant->bufferName));

     //phone
     strcpy(person.telefone, gtk_entry_buffer_get_text(iassistant->bufferPhone));

     //add day for client
     pega_data(stringTime);
     strcpy(person.data, stringTime);

     //insert in list from page Gerenciar-Clientes
     GtkTreeIter iter;
     gtk_list_store_append (GTK_LIST_STORE (interface->treemodel_cli), &iter);
     gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_cli), &iter,
                         COLUMN_ITEM_ID,      person.id,
                         COLUMN_ITEM_NOME,    person.nome,
                         COLUMN_ITEM_TELFONE, person.telefone,
                         COLUMN_ITEM_DATA,    person.data, -1);

     //insert person in Fila
     if(id < 200000){
        clientes = inserirlistcli(clientes, person);
     }else{
        message_of_error("O Numero de cadastros chegou a 200.000!");
     }
}

void  open_assistantCli_Alt(GtkAssistant* assistant){
      GtkTreeIter iter;
      GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_cli);
      if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
          //Get for conteudo of tree
          gint id_person;
          gtk_tree_model_get (interface->treemodel_cli, &iter, COLUMN_ITEM_ID, &id_person, -1);

          //find insumos
          ListaCliente* no = procurarlistcli(clientes, id_person);

          //set_text
          gtk_entry_buffer_set_text(iassistant->bufferName,  no->info.nome,   strlen(no->info.nome));
          gtk_entry_buffer_set_text(iassistant->bufferPhone,  no->info.telefone, strlen(no->info.telefone));

          gtk_widget_show_now(GTK_WIDGET(assistant));
      }
}

void  apply_assistantCli_Alt(GtkAssistant* assistant){
      GtkTreeIter iter;
      GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_cli);
      if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
         //Get for conteudo of tree
         gint id_person;
         gtk_tree_model_get (interface->treemodel_cli, &iter, COLUMN_ITEM_ID, &id_person, -1);

         //find insumos
         ListaCliente* no = procurarlistcli(clientes, id_person);

         Cliente person;
         person.id = id_person;
         strcpy(person.nome, gtk_entry_buffer_get_text(iassistant->bufferName));
         strcpy(person.telefone, gtk_entry_buffer_get_text(iassistant->bufferPhone));
         strcpy(person.data, no->info.data);

         no->info = person;

         gchar *old_name;
         gchar *old_telefone;
         gtk_tree_model_get (interface->treemodel_cli, &iter,
                             COLUMN_ITEM_NOME,      &old_name,
                             COLUMN_ITEM_TELFONE,   &old_telefone,-1);
         g_free (old_name);
         g_free (old_telefone);

         gtk_list_store_set(GTK_LIST_STORE (interface->treemodel_cli), &iter,
                            COLUMN_ITEM_NOME,     person.nome,
                            COLUMN_ITEM_TELFONE,  person.telefone,-1);
      }
}

void delete_client(void){
     GtkTreeIter iter;
     GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_cli);
     if (gtk_tree_selection_get_selected (selection, NULL, &iter)){

         GtkTreePath *path;

         path = gtk_tree_model_get_path (interface->treemodel_cli, &iter);

         //Get for conteudo of tree
         gint id_cli;
         gtk_tree_model_get (interface->treemodel_cli, &iter, COLUMN_ITEM_ID, &id_cli, -1);

         //delete client of list
         clientes =  removerlistcli(clientes, id_cli);

         //delete vehicles of client of tree
         delete_veh_cli(vehicles, id_cli);

         gtk_list_store_remove (GTK_LIST_STORE (interface->treemodel_cli), &iter);

         gtk_tree_path_free (path);
    }
}

void applyAssistantServices(GtkAssistant* assistant){
     int id = 1;
     char *ptr;
     int i = 0;
     GtkTreeIter iter;
     gint id_ins;
     gboolean boolean;
     gchar  *quantp;
     gchar  *quantm;
     gchar  *quantg;

     if(services != NULL) id += services->info.serId;

     Servico serv;
     serv.serId = id;
     //insert Name
     strcpy(serv.nome, gtk_entry_buffer_get_text(iassistant->bufferName));

     //insert Valor
     //Transform String in type Double
     serv.valorP = strtod( gtk_entry_buffer_get_text(iassistant->bufferValorP), &ptr);
     serv.valorM = strtod( gtk_entry_buffer_get_text(iassistant->bufferValorM), &ptr);
     serv.valorG = strtod( gtk_entry_buffer_get_text(iassistant->bufferValorG), &ptr);

     //insert insumos
     if(gtk_tree_model_get_iter_first(interface->treemodel_insser, &iter)){
           gtk_tree_model_get (interface->treemodel_insser,  &iter,
                                    COLUMN_INSSER_USA,    &boolean,
                                    COLUMN_INSSER_IDINS,  &id_ins,
                                    COLUMN_INSSER_QUANTP, &quantp,
                                    COLUMN_INSSER_QUANTM, &quantm,
                                    COLUMN_INSSER_QUANTG, &quantg, -1);

            if(boolean){
                serv.gastos[i].id_ins =  id_ins;
                serv.gastos[i].qntdP  =  strtod(quantp, &ptr);
                serv.gastos[i].qntdM  =  strtod(quantm, &ptr);
                serv.gastos[i].qntdG  =  strtod(quantg, &ptr);
                i++;
            }

        //pega o proximo
        while(gtk_tree_model_iter_next (interface->treemodel_insser, &iter) && i < 10){
              gtk_tree_model_get (interface->treemodel_insser,  &iter,
                                    COLUMN_INSSER_USA,    &boolean,
                                    COLUMN_INSSER_IDINS,  &id_ins,
                                    COLUMN_INSSER_QUANTP, &quantp,
                                    COLUMN_INSSER_QUANTM, &quantm,
                                    COLUMN_INSSER_QUANTG, &quantg, -1);

            if(boolean){
                serv.gastos[i].id_ins =  id_ins;
                serv.gastos[i].qntdP  =  strtod(quantp, &ptr);
                serv.gastos[i].qntdM  =  strtod(quantm, &ptr);
                serv.gastos[i].qntdG  =  strtod(quantg, &ptr);
                i++;
            }
        }
         free(quantp);
         free(quantm);
         free(quantg);
         free(ptr);
     }

     while(i < 10){
        serv.gastos[i].id_ins =  0;
        serv.gastos[i].qntdP  =  0;
        serv.gastos[i].qntdM  =  0;
        serv.gastos[i].qntdG  =  0;
        i++;
     }

     //Descri Serv
     GtkTextIter strat;
     gtk_text_buffer_get_start_iter (iassistant->bufferDescri, &strat);
     GtkTextIter enditer;
     gtk_text_buffer_get_end_iter   (iassistant->bufferDescri, &enditer);
     strcpy(serv.descri, gtk_text_buffer_get_text(iassistant->bufferDescri, &strat, &enditer, FALSE));

     GtkTreeIter iterS;
     gtk_list_store_append (GTK_LIST_STORE (interface->treemodel_ser), &iterS);
     gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_ser), &iterS,
             COLUMN_SERV_ID,      serv.serId,
             COLUMN_SERV_NOME,    serv.nome,
             COLUMN_SERV_QUANTP,  g_strdup_printf ("%.2f", serv.valorP),
             COLUMN_SERV_QUANTM,  g_strdup_printf ("%.2f", serv.valorM),
             COLUMN_SERV_QUANTG,  g_strdup_printf ("%.2f", serv.valorG),
             COLUMN_SERV_DESCRI,  serv.descri,
             COLUMN_SERV_X,  FALSE,-1);
    //insert in list
    services = inserirList(services, serv);
}

void  open_assistantSer_Alt(GtkAssistant* assistant){
      GtkTreeIter iter;
      GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_ser);
      if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
          //Get for conteudo of tree
          gint id_service;
          gtk_tree_model_get (interface->treemodel_ser, &iter, COLUMN_SERV_ID, &id_service, -1);

          //find insumos
          ListaServico* no = procurar(services, id_service);

          char valorP[10];
          char valorM[10];
          char valorG[10];

          sprintf(valorP, "%.2lf", no->info.valorP);
          sprintf(valorM, "%.2lf", no->info.valorM);
          sprintf(valorG, "%.2lf", no->info.valorG);

          //set_text
          gtk_entry_buffer_set_text(iassistant->bufferName,  no->info.nome,   strlen(no->info.nome));
          gtk_entry_buffer_set_text(iassistant->bufferValorP, valorP,  strlen(valorP));
          gtk_entry_buffer_set_text(iassistant->bufferValorM, valorM,  strlen(valorM));
          gtk_entry_buffer_set_text(iassistant->bufferValorG, valorG,  strlen(valorG));
          gtk_text_buffer_set_text(iassistant->bufferDescri, no->info.descri, strlen(no->info.descri));

          //insert insumos
          GtkTreeIter iter_in;
          int i = 0;
          gint id_ins;
          if(gtk_tree_model_get_iter_first(interface->treemodel_insser, &iter_in)){
                gtk_tree_model_get (interface->treemodel_insser,  &iter_in,
                                            COLUMN_INSSER_IDINS,   &id_ins, -1);
                if(id_ins == no->info.gastos[i].id_ins){
                     gtk_list_store_set(GTK_LIST_STORE (interface->treemodel_insser), &iter_in,
                            COLUMN_INSSER_USA,      TRUE,
                            COLUMN_INSSER_QUANTP,   g_strdup_printf ("%.2f", no->info.gastos[i].qntdP),
                            COLUMN_INSSER_QUANTM,   g_strdup_printf ("%.2f", no->info.gastos[i].qntdM),
                            COLUMN_INSSER_QUANTG,   g_strdup_printf ("%.2f", no->info.gastos[i].qntdG),
                            -1);
                     i++;
                }
                printf("%d \n", id_ins);
          }
          while(no->info.gastos[i].id_ins < 0){
            while(gtk_tree_model_iter_next (interface->treemodel_insser, &iter_in) && i < 10 && id_ins <= no->info.gastos[i].id_ins){
                   gtk_tree_model_get (interface->treemodel_insser,  &iter_in,
                                        COLUMN_INSSER_IDINS,  &id_ins, -1);
                   if(id_ins == no->info.gastos[i].id_ins){
                        gtk_list_store_set(GTK_LIST_STORE (interface->treemodel_insser), &iter_in,
                            COLUMN_INSSER_USA,      TRUE,
                            COLUMN_INSSER_QUANTP,   g_strdup_printf ("%.2f", no->info.gastos[i].qntdP),
                            COLUMN_INSSER_QUANTM,   g_strdup_printf ("%.2f", no->info.gastos[i].qntdM),
                            COLUMN_INSSER_QUANTG,   g_strdup_printf ("%.2f", no->info.gastos[i].qntdG),
                            -1);
                   }
             }
             printf("%d \n", id_ins);
             i++;
          }

          gtk_widget_show_now(GTK_WIDGET(assistant));
      }
}

void applyAssistSer_Alt(GtkAssistant *assistant){
     GtkTreeIter iter_serv, iter;
     char *ptr;
     int i = 0;
     gboolean boolean;
     gint    id_ins;
     gchar  *quantp;
     gchar  *quantm;
     gchar  *quantg;

     GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_ser);
     if (gtk_tree_selection_get_selected (selection, NULL, &iter_serv)){
         //Get for conteudo of tree
         gint id_service;
         gtk_tree_model_get (interface->treemodel_ser, &iter_serv, COLUMN_INSUMOS_ID, &id_service, -1);

         //find insumos
         ListaServico* no = procurar(services, id_service);

         Servico serv;

         serv.serId = id_service;

         //insert Name
         strcpy(serv.nome, gtk_entry_buffer_get_text(iassistant->bufferName));

         //insert Valor
         //Transform String in type Double
         serv.valorP = strtod( gtk_entry_buffer_get_text(iassistant->bufferValorP), &ptr);
         serv.valorM = strtod( gtk_entry_buffer_get_text(iassistant->bufferValorM), &ptr);
         serv.valorG = strtod( gtk_entry_buffer_get_text(iassistant->bufferValorG), &ptr);

         //insert insumos
         if(gtk_tree_model_get_iter_first(interface->treemodel_insser, &iter)){
               gtk_tree_model_get (interface->treemodel_insser,  &iter,
                                        COLUMN_INSSER_USA,    &boolean,
                                        COLUMN_INSSER_IDINS,  &id_ins,
                                        COLUMN_INSSER_QUANTP, &quantp,
                                        COLUMN_INSSER_QUANTM, &quantm,
                                        COLUMN_INSSER_QUANTG, &quantg, -1);

                if(boolean){
                    serv.gastos[i].id_ins =  id_ins;
                    serv.gastos[i].qntdP  =  strtod(quantp, &ptr);
                    serv.gastos[i].qntdM  =  strtod(quantm, &ptr);
                    serv.gastos[i].qntdG  =  strtod(quantg, &ptr);
                    i++;
                }

            //pega o proximo
            while(gtk_tree_model_iter_next (interface->treemodel_insser, &iter) && i < 10){
                  gtk_tree_model_get (interface->treemodel_insser,  &iter,
                                        COLUMN_INSSER_USA,    &boolean,
                                        COLUMN_INSSER_IDINS,  &id_ins,
                                        COLUMN_INSSER_QUANTP, &quantp,
                                        COLUMN_INSSER_QUANTM, &quantm,
                                        COLUMN_INSSER_QUANTG, &quantg, -1);

                if(boolean){
                    serv.gastos[i].id_ins =  id_ins;
                    serv.gastos[i].qntdP  =  strtod(quantp, &ptr);
                    serv.gastos[i].qntdM  =  strtod(quantm, &ptr);
                    serv.gastos[i].qntdG  =  strtod(quantg, &ptr);
                    i++;
                }
            }
             free(quantp);
             free(quantm);
             free(quantg);
             free(ptr);
         }

         while(i < 10){
            serv.gastos[i].id_ins =  0;
            serv.gastos[i].qntdP  =  0;
            serv.gastos[i].qntdM  =  0;
            serv.gastos[i].qntdG  =  0;
            i++;
         }

         //Descri Serv
         GtkTextIter strat;
         gtk_text_buffer_get_start_iter (iassistant->bufferDescri, &strat);
         GtkTextIter enditer;
         gtk_text_buffer_get_end_iter   (iassistant->bufferDescri, &enditer);
         strcpy(serv.descri, gtk_text_buffer_get_text(iassistant->bufferDescri, &strat, &enditer, FALSE));

         no->info = serv;

         //insert in list
         gtk_list_store_set(GTK_LIST_STORE (interface->treemodel_ser), &iter_serv,
                            COLUMN_SERV_NOME,     no->info.nome,
                            COLUMN_SERV_QUANTP,   g_strdup_printf ("%.2f", no->info.valorP),
                            COLUMN_SERV_QUANTM,   g_strdup_printf ("%.2f", no->info.valorM),
                            COLUMN_SERV_QUANTG,   g_strdup_printf ("%.2f", no->info.valorG),
                            COLUMN_SERV_DESCRI,   no->info.descri,
                            -1);



         /*gtk_list_store_append (GTK_LIST_STORE (interface->treemodel_ser), &iterS);
         gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_ser), &iterS,
             COLUMN_SERV_ID,      serv.serId,
             COLUMN_SERV_NOME,    serv.nome,
             COLUMN_SERV_QUANTP,  serv.valorP,
             COLUMN_SERV_QUANTM,  serv.valorM,
             COLUMN_SERV_QUANTG,  serv.valorG,
             COLUMN_SERV_DESCRI,  serv.descri,
             COLUMN_SERV_X,  FALSE,-1);*/
     }
}

void delete_services(void){
     GtkTreeIter iter;
     GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_ser);
     if (gtk_tree_selection_get_selected (selection, NULL, &iter)){

         GtkTreePath *path;

         path = gtk_tree_model_get_path (interface->treemodel_ser, &iter);

         //Get for conteudo of tree
         gint id_ser;
         gtk_tree_model_get (interface->treemodel_ser, &iter, 0, &id_ser, -1);

         services =  removerList(services, id_ser);

         gtk_list_store_remove (GTK_LIST_STORE (interface->treemodel_ser), &iter);

         gtk_tree_path_free (path);
    }
}

void prepareAssistantVehicles(GtkAssistant *assistant){
     gint page_number;
     GtkWidget *current_page;
     Arvore* vehicle = NULL;
     page_number = gtk_assistant_get_current_page (assistant);
     current_page = gtk_assistant_get_nth_page (assistant, page_number);
     /*apaga o botão de avanca do assitente*/
     //gtk_assistant_set_page_complete (assistant, current_page, FALSE);

     GtkTreeModel *combox_model =  gtk_combo_box_get_model(iassistant->tamanho);
     GtkTreeIter iter_combox;
     //ação para cada pagina.
     switch(page_number){
        printf("%d \n", page_number);
        case 1:
            //set entry input
            pega_hora(stringTime);
            gtk_entry_buffer_set_text(iassistant->bufferInput, stringTime, 8);
            //set leng
            if(gtk_tree_model_get_iter_first (combox_model, &iter_combox)){
               gtk_combo_box_set_active_iter (iassistant->tamanho, &iter_combox);
            }
        break;
        case 2:
            //verifica se placa já foi cadastrada
           if(strcmp("", gtk_entry_buffer_get_text(iassistant->bufferPlaca))!= 0){
              vehicle = buscar(vehicles, gtk_entry_buffer_get_text(iassistant->bufferPlaca));
              if(vehicle != NULL){
                error_message("Um veiculo com essa placa ja foi cadastrado!");
                gtk_assistant_set_page_complete (assistant, current_page, FALSE);
              }else{
               gtk_assistant_set_page_complete (assistant, current_page, TRUE);
              }
           }
        break;
     }
}
void prepareAssistantInsumos(GtkAssistant *assistant){
     gint page_number;
     page_number = gtk_assistant_get_current_page (assistant);
     GtkTreeIter  iter_combox;
     GtkTreeModel *combox_model =  gtk_combo_box_get_model(iassistant->tipo);

     //ação para cada pagina.
     switch(page_number){
        case 0:

            if(gtk_tree_model_get_iter_first (combox_model, &iter_combox)){
               gtk_combo_box_set_active_iter (iassistant->tipo, &iter_combox);
            }
        break;
     }
}

void applyAssistantInsumos(GtkAssistant* assistant){
     int id = 1;
     char *ptr;
     if(insumos != NULL) id += insumos->info.insId;
     Insumo ins;
     ins.insId = id;
     strcpy(ins.nome, gtk_entry_buffer_get_text(iassistant->bufferName));
     //Transform String in type Double8
     ins.valor = strtod( gtk_entry_buffer_get_text(iassistant->bufferValor), &ptr);

     //Transform String in type Double8
     ins.quant = strtod( gtk_entry_buffer_get_text(iassistant->bufferQuant), &ptr);

     //type
     strcpy(ins.tipo, gtk_combo_box_get_active_text(iassistant->tipo));

     if((strcmp(ins.tipo, "Gramas") == 0) || (strcmp(ins.tipo, "Mlitros") == 0 )){
        ins.quant /= 1000;
     }

     //Descri Serv
     free(ptr);
     GtkTextIter strat;
     gtk_text_buffer_get_start_iter (iassistant->bufferDescri, &strat);
     GtkTextIter enditer;
     gtk_text_buffer_get_end_iter   (iassistant->bufferDescri, &enditer);
     strcpy(ins.descri, gtk_text_buffer_get_text(iassistant->bufferDescri, &strat, &enditer, FALSE));
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
        GtkTreeIter iterIS;
        gtk_list_store_append (GTK_LIST_STORE (interface->treemodel_insser), &iterIS);
        gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_insser), &iterIS,
                           COLUMN_INSSER_USA,        FALSE,
                           COLUMN_INSSER_NOME,       ins.nome,
                           COLUMN_INSSER_QUANTP,      "",
                           COLUMN_INSSER_QUANTM,      "",
                           COLUMN_INSSER_QUANTG,      "",
                           COLUMN_INSSER_IDINS,      ins.insId,
                           COLUMN_INSSER_TIPO,       ins.tipo, -1);

        insumos = inserirInsumo(insumos, ins);
        gastcominsumos += strtod( gtk_entry_buffer_get_text(iassistant->bufferValor), &ptr);
        insumosDia[quant_ins] = ins.insId;
        quant_ins++;

        printf("%.2lf \n", gastcominsumos);
}

void  open_assistant_alt(GtkAssistant* assistant){
      GtkTreeIter iter, iter_combox;
      GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_ins);
      GtkTreeModel  *combox_model =  gtk_combo_box_get_model(iassistant->tipo_alt);
      if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
          //Get for conteudo of tree
          gint id_insumo;
          gtk_tree_model_get (interface->treemodel_ins, &iter, COLUMN_INSUMOS_ID, &id_insumo, -1);

          //find insumos
          ListaInsumo* no = procurar_insumos(insumos, id_insumo);

          char valor[10];
          char quant[10];
          sprintf(valor, "%.2lf",   no->info.valor);
          sprintf(quant, "%.3lf",   no->info.quant);


          //set_text
          gtk_entry_buffer_set_text(iassistant->bufferName,  no->info.nome,   strlen(no->info.nome));
          gtk_entry_buffer_set_text(iassistant->bufferValor, valor,  strlen(valor));
          gtk_entry_buffer_set_text(iassistant->bufferQuant, quant,  strlen(quant));
          gtk_text_buffer_set_text(iassistant->bufferDescri, no->info.descri, strlen(no->info.descri));
          if(gtk_tree_model_get_iter_first (combox_model, &iter_combox)){
                gtk_combo_box_set_active_iter (iassistant->tipo_alt, &iter_combox);
                while(strcmp(gtk_combo_box_get_active_text(iassistant->tipo_alt), no->info.tipo) != 0){
                    gtk_tree_model_iter_next (combox_model, &iter_combox);
                    gtk_combo_box_set_active_iter (iassistant->tipo_alt, &iter_combox);
                }

          }
          gtk_widget_show_now(GTK_WIDGET(assistant));
      }
}

void applyAssistIns_Alt(GtkAssistant *assistant){
     GtkTreeIter iter;
     GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_ins);
     if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
         //Get for conteudo of tree
         gint id_insumo;
         gtk_tree_model_get (interface->treemodel_ins, &iter, COLUMN_INSUMOS_ID, &id_insumo, -1);

         //find insumos
         ListaInsumo* no = procurar_insumos(insumos, id_insumo);

         Insumo ins;
         char *ptr;
         ins.insId = id_insumo;
         strcpy(ins.nome, gtk_entry_buffer_get_text(iassistant->bufferName));
         //Transform String in type Double8
         ins.valor = strtod( gtk_entry_buffer_get_text(iassistant->bufferValor), &ptr);

         //Transform String in type Double8
         ins.quant = strtod( gtk_entry_buffer_get_text(iassistant->bufferQuant), &ptr);


         //type
         strcpy(ins.tipo, gtk_combo_box_get_active_text(iassistant->tipo_alt));

         if((strcmp(ins.tipo, "Gramas") == 0) || (strcmp(ins.tipo, "Mlitros") == 0 )){
             ins.quant /= 1000;
         }

         //Descri INS
         free(ptr);
         GtkTextIter strat;
         gtk_text_buffer_get_start_iter (iassistant->bufferDescri, &strat);
         GtkTextIter enditer;
         gtk_text_buffer_get_end_iter   (iassistant->bufferDescri, &enditer);
         strcpy(ins.descri, gtk_text_buffer_get_text(iassistant->bufferDescri, &strat, &enditer, FALSE));

         //atribui ins
         no->info = ins;

         gchar *old_name;
         gchar *old_value;
         gint  *old_quant;
         gchar *old_tipo;
         gchar *old_desc;
         gtk_tree_model_get (interface->treemodel_ins, &iter,
                            COLUMN_INSUMOS_NOME,    &old_name,
                            COLUMN_INSUMOS_VALOR,   &old_value,
                            COLUMN_INSUMOS_QUANT,   &old_quant,
                            COLUMN_INSUMOS_TIPO,    &old_tipo,
                            COLUMN_INSUMOS_DESCRI,  &old_desc,-1);


         gtk_list_store_set(GTK_LIST_STORE (interface->treemodel_ins), &iter,
                            COLUMN_INSUMOS_NOME,    no->info.nome,
                            COLUMN_INSUMOS_VALOR,     g_strdup_printf ("%.2f", ins.valor),
                            COLUMN_INSUMOS_QUANT,     g_strdup_printf ("%.3f", ins.quant),
                            COLUMN_INSUMOS_TIPO,    no->info.tipo,
                            COLUMN_INSUMOS_DESCRI,  no->info.descri,
                            -1);

             int i;
             int flag = 0;
             for(i = 0; i < quant_ins; i++){
                 if(ins.insId == insumosDia[i]){
                    flag++;
                    i = 50;
                 }
             }

             if(flag != 0){
                double valorantigo = strtod( old_value, &ptr);
                gastcominsumos -= valorantigo;
             }

             g_free (old_name);
             g_free (old_value);
             g_free (old_quant);
             g_free (old_tipo);
             g_free (old_desc);


          GtkTreeIter iter_in;
          gint id_ins;
          if(gtk_tree_model_get_iter_first(interface->treemodel_insser, &iter_in)){
                gtk_tree_model_get (interface->treemodel_insser,  &iter_in,
                                            COLUMN_INSSER_IDINS,   &id_ins, -1);
                if(id_ins == id_insumo){
                     gtk_list_store_set(GTK_LIST_STORE (interface->treemodel_insser), &iter_in,
                            COLUMN_INSSER_NOME,      no->info.nome,
                            COLUMN_INSSER_TIPO,     no->info.tipo,
                            -1);
                }
          }
          while(gtk_tree_model_iter_next (interface->treemodel_insser, &iter_in)){
               gtk_tree_model_get (interface->treemodel_insser,  &iter_in,
                                        COLUMN_INSSER_IDINS,  &id_ins, -1);
               if(id_ins == id_insumo){
                    gtk_list_store_set(GTK_LIST_STORE (interface->treemodel_insser), &iter_in,
                        COLUMN_INSSER_NOME,      no->info.nome,
                        COLUMN_INSSER_TIPO,      no->info.tipo,
                        -1);
               }
          }
     }
     question_message ("Escolha uma opcao", "Voce alterou o valor do produto ?");
}

void delete_insumos(void){
     GtkTreeIter iter;
     GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_ins);
     if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
         GtkTreePath *path;

         path = gtk_tree_model_get_path (interface->treemodel_ins, &iter);

         //Get for conteudo of tree
         gint id_insumo;
         gchar *valor;
         gtk_tree_model_get (interface->treemodel_ins, &iter,
                                        COLUMN_INSUMOS_ID, &id_insumo,
                                        COLUMN_INSUMOS_VALOR, &valor,-1);

         int i;
         int flag = 0;
         for(i = 0; i < quant_ins; i++){
             if(id_insumo == insumosDia[i]){
                flag++;
                i = 50;
             }
         }

         if(flag != 0){
            char* ptr;
            double valorantigo = strtod( valor, &ptr);
            gastcominsumos -= valorantigo;
         }

         insumos =  removerInsumo (insumos, id_insumo);

         //removendo serviços com o insumos excluído
         ListaServico* s;
         if(services != NULL){
            for (s = services; s->next != NULL; s = s->next);
            while( s != NULL) {
                Servico serv = s->info;
                int i = 0;
                while(serv.gastos[i].id_ins != 0 && i < 10){
                    printf("delete insumo serv id is: %d \n insumo id serv is: %d \n insumo id is: %d \n", serv.serId, serv.gastos[i].id_ins, id_insumo);
                    if(serv.gastos[i].id_ins == id_insumo){
                       services = removerList(services, serv.serId);
                          //remove da arvore de windows servicos
                          GtkTreeIter iter_servlist;
                          gint id_servlist;
                          if(gtk_tree_model_get_iter_first(interface->treemodel_ser, &iter_servlist)){
                                gtk_tree_model_get (interface->treemodel_ser,  &iter_servlist,
                                                               COLUMN_SERV_ID,   &id_servlist, -1);
                                if(id_servlist == serv.serId){
                                   gtk_list_store_remove (GTK_LIST_STORE (interface->treemodel_ser), &iter_servlist);
                                }else{
                                    while(gtk_tree_model_iter_next (interface->treemodel_ser, &iter_servlist)){
                                          gtk_tree_model_get (interface->treemodel_ser,  &iter_servlist,
                                                                   COLUMN_SERV_ID,  &id_servlist, -1);
                                        if(id_servlist == serv.serId){
                                          gtk_list_store_remove (GTK_LIST_STORE (interface->treemodel_ser), &iter_servlist);
                                        }
                                    }
                                }
                          }
                       break;
                    }
                 i++;
                }
             s = s->prev;
           }
         }
          GtkTreeIter iter_in;
          gint id_ins;
          if(gtk_tree_model_get_iter_first(interface->treemodel_insser, &iter_in)){
                gtk_tree_model_get (interface->treemodel_insser,  &iter_in,
                                            COLUMN_INSSER_IDINS,   &id_ins, -1);
                if(id_ins == id_insumo){
                   gtk_list_store_remove (GTK_LIST_STORE (interface->treemodel_ins), &iter);
                   gtk_list_store_remove (GTK_LIST_STORE (interface->treemodel_insser), &iter_in);
                }else{
                    while(gtk_tree_model_iter_next (interface->treemodel_insser, &iter_in) == TRUE){
                          gtk_tree_model_get (interface->treemodel_insser,  &iter_in,
                                                   COLUMN_INSSER_IDINS,  &id_ins, -1);
                        if(id_ins == id_insumo){
                           gtk_list_store_remove (GTK_LIST_STORE (interface->treemodel_ins), &iter);
                           GtkTreeIter iter_in_rem = iter_in;
                           gtk_list_store_remove (GTK_LIST_STORE (interface->treemodel_insser), &iter_in_rem);
                        }
                    }
                }
          }
          gtk_tree_path_free (path);
    }
}

void  closed_assistant(GtkWidget* assistant){

      //buffer's
        gtk_entry_buffer_set_text(iassistant->bufferName,   "", 0);
        gtk_entry_buffer_set_text(iassistant->bufferPhone,  "", 0);
        gtk_entry_buffer_set_text(iassistant->bufferPlaca,  "", 0);
        gtk_entry_buffer_set_text(iassistant->bufferInput,  "", 0);
        gtk_entry_buffer_set_text(iassistant->bufferOutput, "", 0);
        gtk_entry_buffer_set_text(iassistant->bufferModelo, "", 0);
        gtk_entry_buffer_set_text(iassistant->bufferCor,    "", 0);
        gtk_entry_buffer_set_text(iassistant->bufferRg,     "", 0);
        gtk_entry_buffer_set_text(iassistant->bufferEnd,    "", 0);
        gtk_entry_buffer_set_text(iassistant->bufferValor,  "", 0);
        gtk_entry_buffer_set_text(iassistant->bufferValorP, "", 0);
        gtk_entry_buffer_set_text(iassistant->bufferValorM, "", 0);
        gtk_entry_buffer_set_text(iassistant->bufferValorG, "", 0);
        gtk_entry_buffer_set_text(iassistant->bufferQuant,  "", 0);
        gtk_text_buffer_set_text (iassistant->bufferDescri, "", 0);

        gtk_entry_buffer_set_text(interface->extintor,  "", 0);
        gtk_entry_buffer_set_text(interface->oleo,    "", 0);
        gtk_entry_buffer_set_text(interface->trocaOleo, "", 0);

        GtkTreeIter iter;
        if(gtk_tree_model_get_iter_first(interface->treemodel_insser, &iter)){
            //pega o proximo
            do{
                gtk_list_store_set (GTK_LIST_STORE(interface->treemodel_insser),  &iter,
                                        COLUMN_INSSER_USA,      FALSE,
                                        COLUMN_INSSER_QUANTP,     "",
                                        COLUMN_INSSER_QUANTM,     "",
                                        COLUMN_INSSER_QUANTG,     "",
                                         -1);
            }while(gtk_tree_model_iter_next (interface->treemodel_insser, &iter) == TRUE);
        }

         GtkTreeIter iterS;

         if(gtk_tree_model_get_iter_first(interface->treemodel_ser, &iterS)){
            //pega o proximo
            do{
                   gtk_list_store_set (GTK_LIST_STORE(interface->treemodel_ser),  &iterS,
                                        COLUMN_SERV_X,       FALSE, -1);
            }while(gtk_tree_model_iter_next (interface->treemodel_ser, &iterS) == TRUE);
         }

         GtkTreeIter iterV;
         if(gtk_tree_model_get_iter_first(interface->treemodel_insert_v, &iterV))
            gtk_list_store_remove (GTK_LIST_STORE (interface->treemodel_insert_v), &iterV);


      gtk_widget_hide(assistant);
}

//show tree changes
void fixed_toggled_I(GtkCellRendererToggle *cell,gchar *path_str,gpointer data){
    GtkTreeIter  iter;
    GtkTreePath *path = gtk_tree_path_new_from_string (path_str);
    gboolean fixed;

    /* get toggled iter */
    gtk_tree_model_get_iter (interface->treemodel_index, &iter, path);
    gtk_tree_model_get (GTK_TREE_MODEL (interface->treemodel_index), &iter, COLUMN_ITEM_I, &fixed, -1);

    /* do something with the value */
    fixed ^= 1;

    /* set new value */
    gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_index), &iter, COLUMN_ITEM_I, fixed, -1);

    /* clean up */
    gtk_tree_path_free (path);
}

void fixed_toggled_P(GtkCellRendererToggle *cell,gchar *path_str,gpointer data){
    GtkTreeIter  iter;
    GtkTreePath *path = gtk_tree_path_new_from_string (path_str);
    gboolean fixed;

    /* get toggled iter */
    gtk_tree_model_get_iter (interface->treemodel_index, &iter, path);
    gtk_tree_model_get (GTK_TREE_MODEL (interface->treemodel_index), &iter, COLUMN_ITEM_P, &fixed, -1);

    /* do something with the value */
    fixed ^= 1;

    /* set new value */
    gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_index), &iter, COLUMN_ITEM_P, fixed, -1);

    /* clean up */
    gtk_tree_path_free (path);
}

void fixed_toggled_E(GtkCellRendererToggle *cell,gchar *path_str,gpointer data){
    GtkTreeIter  iter;
    GtkTreePath *path = gtk_tree_path_new_from_string (path_str);
    gboolean fixed;

    /* get toggled iter */
    gtk_tree_model_get_iter (interface->treemodel_index, &iter, path);
    gtk_tree_model_get (GTK_TREE_MODEL (interface->treemodel_index), &iter, COLUMN_ITEM_E, &fixed, -1);

    /* do something with the value */
    fixed ^= 1;

    /* set new value */
    gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_index), &iter, COLUMN_ITEM_E, fixed, -1);

    /* clean up */
    gtk_tree_path_free (path);
}

void fixed_toggled_USA(GtkCellRendererToggle *cell,gchar *path_str,gpointer data){
    GtkTreeIter  iter;
    GtkTreePath *path = gtk_tree_path_new_from_string (path_str);
    gboolean fixed;

    /* get toggled iter */
    gtk_tree_model_get_iter (interface->treemodel_insser, &iter, path);
    gtk_tree_model_get (interface->treemodel_insser, &iter, COLUMN_INSSER_USA, &fixed, -1);

    /* do something with the value */
    fixed ^= 1;

    /* set new value */
    gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_insser), &iter, COLUMN_INSSER_USA, fixed, -1);

    /* clean up */
    gtk_tree_path_free (path);
}

void cell_edited_QtdInsP(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data){
       GtkTreeIter  iter;
       GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
       gtk_tree_model_get_iter (interface->treemodel_insser, &iter, path);

       //valida entrada
       int i = 0;
       int flag = 0;
       int virgula = 0;
       while(new_text[i] != '\0'){
             if(!((new_text[i] >= '0') && (new_text[i] <= '9')) && new_text[i] != ','){
                flag = 1;
             }else if(new_text[i] == ','){
                virgula++;
             }
             i++;
       }

       gchar *old_text;
       gtk_tree_model_get (interface->treemodel_insser, &iter, COLUMN_INSSER_QUANTP, &old_text, -1);
       g_free (old_text);
       if(flag == 0){
            if(virgula < 2){
                gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_insser), &iter, COLUMN_INSSER_QUANTP,
                            g_strdup (new_text), -1);
            }else{
                message_of_error("Erro utilize apenas uma ',' para escrever o numero !");
            }
       }else{
            message_of_error("Erro utilize apenas numeros, ex: 123 \n e para valores quebrados digite ',' !");
       }
}

void cell_edited_QtdInsM(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data){
       GtkTreeIter  iter;
       GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
       gtk_tree_model_get_iter (interface->treemodel_insser, &iter, path);

       //valida entrada
       int i = 0;
       int flag = 0;
       int virgula = 0;
       while(new_text[i] != '\0'){
             if(!((new_text[i] >= '0') && (new_text[i] <= '9')) && new_text[i] != ','){
                flag = 1;
             }else if(new_text[i] == ','){
                virgula++;
             }
             i++;
       }

       gchar *old_text;
       gtk_tree_model_get (interface->treemodel_insser, &iter, COLUMN_INSSER_QUANTM, &old_text, -1);
       g_free (old_text);
       if(flag == 0){
            if(virgula < 2){
                gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_insser), &iter, COLUMN_INSSER_QUANTM,
                            g_strdup (new_text), -1);
            }else{
                message_of_error("Erro utilize apenas uma ',' para escrever o numero !");
            }
       }else{
            message_of_error("Erro utilize apenas numeros, ex: 123 \n e para valores quebrados digite ',' !");
       }
}

void cell_edited_QtdInsG(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data){
       GtkTreeIter  iter;
       GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
       gtk_tree_model_get_iter (interface->treemodel_insser, &iter, path);

       //valida entrada
       gint i = 0;
       int flag = 0;
       int virgula = 0;
       while(new_text[i] != '\0'){
             if(!((new_text[i] >= '0') && (new_text[i] <= '9')) && new_text[i] != ','){
                flag = 1;
             }else if(new_text[i] == ','){
                virgula++;
             }
             i++;
       }

       gchar *old_text;
       gtk_tree_model_get (interface->treemodel_insser, &iter, COLUMN_INSSER_QUANTG, &old_text, -1);
       g_free (old_text);

       if(flag == 0){
            if(virgula < 2){
               gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_insser), &iter, COLUMN_INSSER_QUANTG,
                                   g_strdup (new_text), -1);
            }else{
                message_of_error("Erro utilize apenas uma ',' para escrever o numero !");
            }
       }else{
            message_of_error("Erro utilize apenas numeros, ex: 123 \n e para valores quebrados digite ',' !");
       }
}

void fixed_toggled_X(GtkCellRendererToggle *cell,gchar *path_str,gpointer data){
    GtkTreeIter  iter;
    GtkTreePath  *path = gtk_tree_path_new_from_string (path_str);
    gboolean fixed;

    /* get toggled iter */
    gtk_tree_model_get_iter (interface->treemodel_ser , &iter, path);
    gtk_tree_model_get (interface->treemodel_ser , &iter, COLUMN_SERV_X, &fixed, -1);

    /* do something with the value */
    fixed ^= 1;

    /* set new value */
    gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_ser), &iter, COLUMN_SERV_X, fixed, -1);

    /* clean up */
    gtk_tree_path_free (path);
}

void fixed_toggled_Client(GtkCellRendererToggle *cell,gchar *path_str,gpointer data){
    GtkTreeIter  iter;
    GtkTreePath  *path = gtk_tree_path_new_from_string (path_str);
    gboolean fixed;

    /* get toggled iter */
    gtk_tree_model_get_iter (interface->treemodel_cli , &iter, path);
    gtk_tree_model_get (interface->treemodel_cli , &iter, COLUMN_ITEM_XCLI, &fixed, -1);

    /* do something with the value */
    fixed ^= 1;

    /* set new value */
    gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_cli), &iter, COLUMN_ITEM_XCLI, fixed, -1);

    /* clean up */
    gtk_tree_path_free (path);
}

void cell_edited_Vendedor(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data){
       GtkTreeIter  iter;
       GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
       gtk_tree_model_get_iter (interface->treemodel_index, &iter, path);

       //valida entrada
       int i = 0;
       int flag = 0;
       while(new_text[i] != '\0'){
             if(!(((new_text[i] >= 'a') && (new_text[i] <= 'z'))|| ((new_text[i] >= 'A') && (new_text[i] <= 'Z')) ) && new_text[i] != ' '){
                flag = 1;
             }
             i++;
       }

       gchar *old_text;
       gtk_tree_model_get (interface->treemodel_index, &iter, COLUMN_ITEM_VENDEDOR, &old_text, -1);
       g_free (old_text);
       if(flag == 0){
            gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_index), &iter, COLUMN_ITEM_VENDEDOR,
                            g_strdup (new_text), -1);
       }else{
            message_of_error("Erro utilize apenas numeros, ex: rodrigo! ");
       }
}

void cell_edited_Gorjeta(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data){
       GtkTreeIter  iter;
       GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
       gtk_tree_model_get_iter (interface->treemodel_index, &iter, path);

       //valida entrada
       gint i = 0;
       int flag = 0;
       while(new_text[i] != '\0'){
             if(!((new_text[i] >= '0') && (new_text[i] <= '9')) && new_text[i] != ','){
                flag = 1;
             }
             i++;
       }

       gchar *old_text;
       gtk_tree_model_get (interface->treemodel_index, &iter, COLUMN_ITEM_GORJETA, &old_text, -1);
       g_free (old_text);

       if(flag == 0){
               gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_index), &iter, COLUMN_ITEM_GORJETA,
                                   g_strdup (new_text), -1);
       }else{
            message_of_error("Erro utilize apenas numeros, ex: 123 \n e para valores quebrados digite ',' !");
       }
}

void cell_edited_Obs(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data){
       GtkTreeIter  iter;
       GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
       gtk_tree_model_get_iter (interface->treemodel_index, &iter, path);

       gchar *old_text,*placa;
       gtk_tree_model_get (interface->treemodel_index, &iter,
                           COLUMN_ITEM_IDVEHICLES, &placa,
                           COLUMN_ITEM_OBS, &old_text, -1);
       g_free (old_text);
       Arvore *car = buscar(vehicles, placa);
       gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_index), &iter, COLUMN_ITEM_OBS,
                            g_strdup (new_text), -1);
       strcpy(car->info.descri, new_text);
}

void cell_edited_Supervisor(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data){
       GtkTreeIter  iter;
       GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
       gtk_tree_model_get_iter (interface->treemodel_index, &iter, path);

       //valida entrada
       int i = 0;
       int flag = 0;
       while(new_text[i] != '\0'){
             if(!(((new_text[i] >= 'a') && (new_text[i] <= 'z'))|| ((new_text[i] >= 'A') && (new_text[i] <= 'Z')) ) && new_text[i] != ' '){
                flag = 1;
             }
             i++;
       }

       gchar *old_text;
       gtk_tree_model_get (interface->treemodel_index, &iter, COLUMN_ITEM_SUPERVISOR, &old_text, -1);
       g_free (old_text);
       if(flag == 0){
            gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_index), &iter, COLUMN_ITEM_SUPERVISOR,
                            g_strdup (new_text), -1);
       }else{
            message_of_error("Erro utilize apenas numeros, ex: rodrigo! ");
       }
}

void cell_edited_saidas(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data){
       GtkTreeIter  iter;
       GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
       gtk_tree_model_get_iter (interface->treemodel_despesa, &iter, path);

       //valida entrada
       int i = 0;
       int flag = 0;
       while(new_text[i] != '\0'){
             if(!(((new_text[i] >= 'a') && (new_text[i] <= 'z'))|| ((new_text[i] >= 'A') && (new_text[i] <= 'Z')) ) && new_text[i] != ' '){
                flag = 1;
             }
             i++;
       }

       gchar *old_text;
       gtk_tree_model_get (interface->treemodel_despesa, &iter, COLUMN_DESP_DESCRI, &old_text, -1);
       g_free (old_text);
       if(flag == 0){
            gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_despesa), &iter, COLUMN_DESP_DESCRI,
                            g_strdup (new_text), -1);
       }else{
            message_of_error("Erro utilize apenas numeros, ex: rodrigo! ");
       }
}

void cell_edited_Valor(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data){
       GtkTreeIter  iter;
       GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
       gtk_tree_model_get_iter (interface->treemodel_despesa, &iter, path);

       //valida entrada
       gint i = 0;
       int flag = 0;
       int virgula = 0;
       while(new_text[i] != '\0'){
             if(!((new_text[i] >= '0') && (new_text[i] <= '9')) && new_text[i] != ','){
                flag = 1;
             }else if(new_text[i] == ','){
                virgula++;
             }
             i++;
       }

       gchar *old_text;
       gtk_tree_model_get (interface->treemodel_despesa, &iter, COLUMN_DESP_VALOR, &old_text, -1);

       if(flag == 0){
            if(virgula < 2){
               gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_despesa), &iter, COLUMN_DESP_VALOR,
                                   g_strdup (new_text), -1);
               char *ptr;
               resultado_dia.saida -= strtod( old_text, &ptr);
               resultado_dia.saida += strtod( new_text, &ptr);
               gtk_label_set_text (interface->label_despesa, g_strdup_printf ("%.2f", resultado_dia.saida));
            }else{
                message_of_error("Erro utilize apenas uma ',' para escrever o numero !");
            }
       }else{
            message_of_error("Erro utilize apenas numeros, ex: 123 \n e para valores quebrados digite ',' !");
       }

       g_free (old_text);
}

void cell_edited_entF(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data){
       GtkTreeIter  iter;
       GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
       gtk_tree_model_get_iter (interface->treemodel_usu, &iter, path);

       //valida entrada
       int i = 0;
       int flag = 0;
       int pontos = 0;
       gchar *old_text;
       gtk_tree_model_get (interface->treemodel_usu, &iter, COLUMN_USER_ENT, &old_text, -1);

       while(new_text[i] != '\0'){
             if(!((new_text[i] >= '0') && (new_text[i] <= '9')) && new_text[i] != ':'){
                flag = 1;
             }else if(new_text[i] == ':'){
                pontos++;
             }
             i++;
       }

       if(flag == 0){
            if(pontos < 2){
               gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_usu), &iter, COLUMN_USER_ENT,
                            g_strdup (new_text), -1);
            }else{
                message_of_error("Erro utilize apenas uma vez ':' para escrever o numero !");
            }
       }else{
            message_of_error("Erro utilize apenas numeros, ex: 123 \n e para valores quebrados digite ':' !");
       }

       g_free (old_text);
}

void cell_edited_saiF(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data){
       GtkTreeIter  iter;
       GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
       gtk_tree_model_get_iter (interface->treemodel_usu, &iter, path);

       //valida entrada
       int i = 0;
       int flag = 0;
       int pontos = 0;
       gchar *old_text;
       gtk_tree_model_get (interface->treemodel_usu, &iter, COLUMN_USER_SAI, &old_text, -1);

       while(new_text[i] != '\0'){
             if(!((new_text[i] >= '0') && (new_text[i] <= '9')) && new_text[i] != ':'){
                flag = 1;
             }else if(new_text[i] == ':'){
                pontos++;
             }
             i++;
       }

       if(flag == 0){
            if(pontos < 2){
               gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_usu), &iter, COLUMN_USER_SAI,
                            g_strdup (new_text), -1);
            }else{
                message_of_error("Erro utilize apenas uma vez ':' para escrever o numero !");
            }
       }else{
            message_of_error("Erro utilize apenas numeros, ex: 123 \n e para valores quebrados digite ':' !");
       }

       g_free (old_text);
}

void cell_edited_pagF(GtkCellRendererText *cell,const gchar *path_string, const gchar  *new_text, gpointer data){
       GtkTreeIter  iter;
       GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
       gtk_tree_model_get_iter (interface->treemodel_usu, &iter, path);

       //valida entrada
       int i = 0;
       int flag = 0;
       int virgula = 0;
       gchar *old_text;
       gtk_tree_model_get (interface->treemodel_usu, &iter, COLUMN_USER_PAG, &old_text, -1);

       while(new_text[i] != '\0'){
             if(!((new_text[i] >= '0') && (new_text[i] <= '9')) && new_text[i] != ','){
                flag = 1;
             }else if(new_text[i] == ','){
                virgula++;
             }
             i++;
       }


       if(flag == 0){
            if(virgula < 2){
               gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_usu), &iter, COLUMN_USER_PAG,
                            g_strdup (new_text), -1);
            }else{
                message_of_error("Erro utilize apenas uma ',' para escrever o numero !");
            }
       }else{
            message_of_error("Erro utilize apenas numeros, ex: 123 \n e para valores quebrados digite ',' !");
       }

       g_free (old_text);
}
//Animação de carregamento de veiculo

gboolean timeout_small_cars (gpointer data){
  GtkTreeIter iter;
  gint pulse;

  if (interface->treemodel_index == NULL)
      return FALSE;

  //gtk_tree_model_get_iter_first (interface->treemodel_index, &iter);
  int i = 0;

  while(i < small_cars){

          gtk_tree_model_get (interface->treemodel_index, &interface->iterVeiSmall[i],
                            COLUMN_ITEM_PROCESSO, &pulse,  -1);

          if (pulse != 100){
             pulse++;
             gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_index),
                              &interface->iterVeiSmall[i], COLUMN_ITEM_PROCESSO ,
                              pulse, -1);
          }

          i++;
  }

  return TRUE;
}

gboolean timeout_medium_cars (gpointer data){
  GtkTreeIter iter;
  gint pulse;

  if (interface->treemodel_index == NULL)
      return FALSE;

  //gtk_tree_model_get_iter_first (interface->treemodel_index, &iter);
  int i = 0;

  while(i < medium_cars){

          gtk_tree_model_get (interface->treemodel_index, &interface->iterVeiMedium[i],
                            COLUMN_ITEM_PROCESSO, &pulse,  -1);

          if (pulse != 100){
             pulse++;
             gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_index),
                              &interface->iterVeiMedium[i], COLUMN_ITEM_PROCESSO ,
                              pulse, -1);
          }

          i++;
  }

  return TRUE;
}

gboolean timeout_big_cars (gpointer data){
  gint pulse;

  if (interface->treemodel_index == NULL)
      return FALSE;

  //gtk_tree_model_get_iter_first (interface->treemodel_index, &iter);
  int i = 0;

  while(i < big_cars){

          gtk_tree_model_get (interface->treemodel_index, &interface->iterVeiBig[i],
                              COLUMN_ITEM_PROCESSO, &pulse,  -1);

          if (pulse != 100){
             pulse++;
             gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_index),
                              &interface->iterVeiBig[i], COLUMN_ITEM_PROCESSO ,
                              pulse, -1);
          }

          i++;
  }

  return TRUE;
}

gboolean processo_timeout (gpointer data){
  GtkTreeIter iter;
  gint pulse;

  if (interface->treemodel_index == NULL)
      return FALSE;

  if(gtk_tree_model_get_iter_first (interface->treemodel_index, &iter)){
     gtk_tree_model_get (interface->treemodel_index, &iter,
                      COLUMN_ITEM_PROCESSO, &pulse,
                      -1);

  if (pulse != 99){
     pulse++;
  }else if(pulse == 99){
     pulse++;
     num_vehi_aten--;
  }
   gtk_list_store_set (GTK_LIST_STORE (interface->treemodel_index), &iter,
                       COLUMN_ITEM_PROCESSO , pulse,-1);

  }
  return TRUE;
}

void create_waittime(){
    waitinfo.tm_yday  = 0;
    waitinfo.tm_year  = 0;
    waitinfo.tm_mday  = 0;
    waitinfo.tm_mon   = 0;
    waitinfo.tm_isdst = 0;
    waitinfo.tm_hour  = 0;
    waitinfo.tm_min   = 0;
    waitinfo.tm_sec   = 0;
    waitinfo.tm_wday  = 0;
    mktime(&waitinfo);
    timewait(stringwaitTime,0,0,0);
}

//Animação de carregamento de banners
/*carrega images do banner*/
gboolean load_pixbufs (){
  int i;
  GError *error;
  for (i = 0; i < N_IMAGES; i++){
           images[i] = gdk_pixbuf_new_from_file (image_names[i], error);

      if (!images[i])
        return FALSE; /* Note that "error" was filled with a GError */
  }
  return TRUE;
}
/*troca banner*/
gint timeout_banner (gpointer data){
  if(timebanner == 0){
     gtk_image_set_from_pixbuf      (interface->image, images[0]);
     timebanner = 1;
  }else if(timebanner == 1){
     gtk_image_set_from_pixbuf      (interface->image, images[1]);
     timebanner = 2;
  }else{
     gtk_image_set_from_pixbuf      (interface->image, images[2]);
     timebanner = 0;
  }
  return TRUE;
}

gboolean timmer_timeout (gpointer data){
  if(waitinfo.tm_hour != 0 || waitinfo.tm_min != 0 || waitinfo.tm_sec != 0)
  timewait(stringwaitTime,0, 0, -1);
  if (interface->labelTimmer1 == NULL || interface->labelTimmer2 == NULL || interface->labelTimmer == NULL )
      return FALSE;

  pega_hora(stringTime);

  gtk_label_set_text (interface->labelTimmer1, stringwaitTime);
  gtk_label_set_text (interface->labelTimmer2, stringwaitTime);
  gtk_label_set_text (interface->labelTimmer, stringTime);

  return TRUE;
}

//interface index
void start_vehicle(void){
    GtkTreeIter iter;
    GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_index);

    if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
         gchar *id_vehi;
         gtk_tree_model_get (interface->treemodel_index, &iter,
                            COLUMN_ITEM_IDVEHICLES , &id_vehi, -1);
         Arvore* no = buscar(vehicles, id_vehi);
         Veiculo veic = no->info;
         Arvore* no_f = buscar(atendidos, id_vehi);

         if(no_f == NULL){
            if(strcmp(no->info.tamanho, "Pequeno") == 0){
                        interface->iterVeiSmall[small_cars] = iter;
                        atendidos  = inserir(atendidos, veic);
                        small_cars++;
             }else if(strcmp(no->info.tamanho, "Medio") == 0){
                        interface->iterVeiMedium[medium_cars] = iter;
                        atendidos  = inserir(atendidos, veic);
                        medium_cars++;
             }else{
                        interface->iterVeiSmall[big_cars] = iter;
                        atendidos  = inserir(atendidos, veic);
                        big_cars++;
             }
         }else{
             error_message("Este veiculo ja foi comecado!");
         }
    }else{
        error_message("Necessario selecionar um Veiculo da Lista!");
    }
}

void  num_func(GtkEntry* entryFun){
     gchar* numeros = gtk_entry_get_text(entryFun);
     int i = 0;
     int flag = 0;
     while(numeros[i] != '\0' && flag == 0){
          if(!(numeros[i] >= '0' && numeros[i] <= '9')){
            flag = 1;
          }
          i++;
     }
     int num = atoi(numeros);
     if(flag == 0){
         if( num > 1){
            quant_fun = num / 2;
         }else{
            error_message("quantidade de funciionario menor do que o possivel!");
         }
     }else{
            message_of_error("Erro utilize apenas numeros! ex: 123 ");
     }
     gtk_entry_set_text(entryFun, "");
}

void btn_delete_vehicletree(void){
    GtkTreeIter iter;
    GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_index);

    if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
         gchar *id_vehi;
         gtk_tree_model_get (interface->treemodel_index, &iter,
                             COLUMN_ITEM_IDVEHICLES ,    &id_vehi, -1);

         Arvore* no = buscar(atendidos, id_vehi);
         if(no == NULL ){
            vehiclesEqueue = remover_daFila(vehiclesEqueue, id_vehi);
            num_vehi_aten--;
            gtk_list_store_remove (GTK_LIST_STORE (interface->treemodel_index), &iter);
         }else{
            error_message("o veiculo nao pode ser excluido, \n por que ele ja foi comecado!");
         }
    }else{
            error_message("Selecione um Veiculo!");
    }
}

void btn_diagnostic_vehicle(GtkWidget* win){
    GtkTreeIter iter;
    GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_index);
    if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
         show_widget(interface->diagnost);
    }else{
        error_message("Necessario selecionar um Veiculo da Lista\n para se gerar um relatorio !");
    }
}

void zera_tempo(void){
    waitinfo.tm_hour = 0;
    waitinfo.tm_min  = 0;
    waitinfo.tm_sec  = 0;
    timewait(stringwaitTime,0, 0, 0);
    gtk_label_set_text (interface->labelTimmer1, stringwaitTime);
    gtk_label_set_text (interface->labelTimmer2, stringwaitTime);
}

void entradadecaixa(GtkEntryBuffer *buffer){
     //pegar o buffer jogar em uma variavel e limpar o buffer.
     char *ptr;
     resultado_dia.entrada = strtod( gtk_entry_buffer_get_text(buffer), &ptr);
     gtk_entry_buffer_set_text(buffer,   "", 0);
     close_widget(interface->entryCaixa);
}

void inserirDespesa(GtkTreeModel *model){
      GtkTreeIter iter;

      gtk_list_store_append (GTK_LIST_STORE (model), &iter);
      gtk_list_store_set (GTK_LIST_STORE (model), &iter,
                          COLUMN_DESP_NUMBER,  num_desp,
                          COLUMN_DESP_DESCRI,  g_strdup ("Digite a saida aqui"),
                          COLUMN_DESP_VALOR,   g_strdup ("0,00"),
                          COLUMN_DESP_EDITAR,  TRUE,
                          -1);
      num_desp++;
}

void excluirDespesa(void){
     GtkTreeIter iter;
     GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_desp);
     if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
         gchar *old_text;
         gtk_tree_model_get (interface->treemodel_despesa, &iter, COLUMN_DESP_VALOR, &old_text, -1);
         char *ptr;
         resultado_dia.saida -= strtod( old_text, &ptr);
         gtk_label_set_text (interface->label_despesa, g_strdup_printf ("%.2f", resultado_dia.saida));

         gtk_list_store_remove (GTK_LIST_STORE (interface->treemodel_despesa), &iter);
     }else{
         error_message("Necessario selecionar um item da Lista\n para excluir !");
     }
}

int hours_int(char* saif){
      int i = 0, j = 0, s = 0;
      char saida[8];
      while(saif[i] != '\0'){
          if(saif[i] != ':'){
             saida[j] = saif[i];
             j++;
          }
        i++;
      }
      saida[j] = '\0';
      s = atoi(saida);
      return s;
}

void false_resp(void){
     close_widget(interface->true_or_false);
     printf("%.2lf \n", gastcominsumos);
}

void true_resp(void){

     GtkTreeIter iter;
     GtkTreeSelection *selection = gtk_tree_view_get_selection (interface->treeview_ins);
     if (gtk_tree_selection_get_selected (selection, NULL, &iter)){
         //Get for conteudo of tree
         char* ptr;
         gchar* valorI;
         double ins_valor;
         gint id_insumo;
         gtk_tree_model_get (interface->treemodel_ins, &iter, COLUMN_INSUMOS_ID, &id_insumo,
                                                              COLUMN_INSUMOS_VALOR, &valorI, -1);
         ins_valor = strtod( valorI, &ptr);
         gastcominsumos += ins_valor;

         insumosDia[quant_ins] = id_insumo;
         quant_ins++;
     }
     close_widget(interface->true_or_false);
     printf("%.2lf \n", gastcominsumos);
}

void valid_password_d(GtkEntryBuffer* password){
     gchar* p = gtk_entry_buffer_get_text(password);
     if(strcmp(p, "Jesus37") == 0){
       gtk_entry_buffer_set_text(password, "", 0);
       close_widget(interface->passWord);
       gtk_widget_show (interface->dataFila);
       gtk_widget_show (interface->entryCaixa);
     }else{
       gtk_entry_buffer_set_text(password, "", 0);
       close_widget(interface->passWord);
       message_of_error("senha errada!");
     }
}

void valid_password_m(GtkEntryBuffer* password){
     gchar* p = gtk_entry_buffer_get_text(password);
     if(strcmp(p, "Jesus37") == 0){
        gtk_widget_show(interface->dataFilaMes);
        gtk_entry_buffer_set_text(password, "", 0);
        close_widget(interface->passWord1);
     }else{
        gtk_entry_buffer_set_text(password, "", 0);
        close_widget(interface->passWord1);
        message_of_error("senha errada!");
     }
}

void valid_password_a(GtkEntryBuffer* password){
     gchar* p = gtk_entry_buffer_get_text(password);
     if(strcmp(p, "Jesus37") == 0){
       gtk_entry_buffer_set_text(password, "", 0);
       close_widget(interface->passWord2);
       gtk_widget_show(interface->dataFilaAno);
     }else{
       gtk_entry_buffer_set_text(password, "", 0);
       close_widget(interface->passWord2);
       message_of_error("senha errada!");
     }
}

void btn_save_tree(void){
    //password
    gtk_widget_show (interface->passWord);
}

void relatorioMes(void){
    gtk_widget_show (interface->passWord1);
}

void relatorioAno(void){
    gtk_widget_show (interface->passWord2);
}
