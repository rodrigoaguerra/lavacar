#include "header.h"
/*
Trabalho desenvolvido com base nas disciplinas de linguagem de programação
e algoritmos-2 ministradas pelos professores Robson Linhares e Rodrigo Minetto
e com estudos feitos no livro 'Aprenda Aprogramar Em C,C++,C#' de Rosãngela Hickson.
Desenvolvedor: Rodrigo Alves Guerra.
*/

int main (int argc, char *argv[]){
    num_treevehicles = 1;
    num_vehi_aten = 1;
    small_cars  = 0;
    medium_cars = 0;
    big_cars    = 0;
    quant_fun = 1;
    num_desp = 1;
    resultado_dia.entrada = 0;
    resultado_dia.saida = 0;
    resultado_dia.resultado = 0;
    gastcominsumos = 0;
    loadFile = 0;
    gchar *date_a = NULL;
    gchar *date_m = NULL;
    gchar *date_d = NULL;

    for(quant_ins = 0; quant_ins < 36; quant_ins++){
        insumosDia[quant_ins] = 0;
    }

    quant_ins = 0;

    setlocale(LC_ALL, "UTF-8");

    vehiclesEqueue = criarFila();

    stringTime = (char*) malloc(51 * sizeof(char));
    stringwaitTime = (char*) malloc(51 * sizeof(char));

    create_waittime();

    /*INICIANDO A INTERFACE*/
    /* allocate the memory needed by our interfaceSystem struct */
    interface = g_slice_new (InterfaceSystem);
    iassistant = g_slice_new (AssistantSystem);

    /* initialize GTK+ libraries */
    gtk_init(&argc, &argv);
    if (init_app (interface) == FALSE) return 1; /* error loading UI */

    if (load_pixbufs () == FALSE) return 1;

    if(timebanner == 0 && timeoutSmall == 0 && timeoutMedium == 0 && timeoutBig == 0) {
       timebanner    = g_timeout_add (60000, timeout_banner, NULL);
       timeoutSmall  = g_timeout_add (18000, timeout_small_cars, NULL);
       timeoutMedium = g_timeout_add (30000, timeout_medium_cars, NULL);
       timeoutBig    = g_timeout_add (36000, timeout_big_cars, NULL);
    }

    //timmer color black
    GdkColor color;
    color.pixel = 0;
    color.red  = 0;
    color.green = 0;
    color.blue = 0;

    gtk_widget_modify_bg (interface->window_timmer, GTK_STATE_NORMAL, &color);

    /*--reading files--*/
    read_arqvs();

    /* show the window */
    gtk_widget_show (interface->index);
    gtk_widget_show (interface->window_timmer);

    if(timmer == 0) {
        timmer  = g_timeout_add (1000, timmer_timeout, NULL);
    }

    /* enter GTK+ main loop */
    gtk_main ();

    /*--saving files--*/
    save_arqvs();

    imprimirFila();

    if (timeout != 0){
      g_source_remove (timeout);
      timeout = 0;
    }

    if (timmer != 0)
    {
      g_source_remove (timmer);
      timmer = 0;
    }

    if (timebanner != 0)
    {
      g_source_remove (timebanner);
      timebanner = 0;
    }

    if (timeoutSmall != 0)
    {
      g_source_remove (timeoutSmall);
      timeoutSmall = 0;
    }

    if (timeoutMedium != 0)
    {
      g_source_remove (timeoutMedium);
      timeoutMedium = 0;
    }

    if (timeoutBig != 0)
    {
      g_source_remove (timeoutBig);
      timeoutBig = 0;
    }

    /*libera memoria da struct interface GTK*/
    g_slice_free (InterfaceSystem, interface);
    g_slice_free (AssistantSystem, iassistant);

    liberar(services);
    liberarInsumos(insumos);
    liberarlistcli(clientes);
    liberarlistusu(funcionarios);
    vehicles  = arv_libera (vehicles);
    atendidos = arv_libera (atendidos);
    free(vehiclesEqueue);
    free(stringTime);
    free(stringwaitTime);
    //printf("%.2lf", entrada);

    return 0;
}


gboolean init_app (InterfaceSystem *interface){

    GtkBuilder              *builder;
    GError                  *err=NULL;

    /* use GtkBuilder to build our interface from the XML file */
    builder = gtk_builder_new ();
    if (gtk_builder_add_from_file (builder, "interface.glade", &err) == 0)
    {
        error_message (err->message);
        g_error_free (err);
        return FALSE;
    }

    //conectando struct a interface
    interface->index               = GTK_WIDGET       (gtk_builder_get_object (builder, "index"));
    interface->image               = GTK_IMAGE        (gtk_builder_get_object (builder, "banner"));
    interface->treeview_index      = GTK_TREE_VIEW    (gtk_builder_get_object (builder, "treeviewindex"));
    interface->treemodel_index     = GTK_TREE_MODEL   (gtk_builder_get_object (builder, "listvehiclesdia"));
    interface->treeview_ins        = GTK_TREE_VIEW    (gtk_builder_get_object (builder, "treeviewInsumos"));
    interface->treemodel_ins       = GTK_TREE_MODEL   (gtk_builder_get_object (builder, "treemodelInsumos"));
    interface->treeview_insser     = GTK_TREE_VIEW    (gtk_builder_get_object (builder, "treeInsumosServ"));
    interface->treemodel_insser    = GTK_TREE_MODEL   (gtk_builder_get_object (builder, "treemodelInsServ"));
    interface->treeview_ser        = GTK_TREE_VIEW    (gtk_builder_get_object (builder, "treeviewServices"));
    interface->treemodel_ser       = GTK_TREE_MODEL   (gtk_builder_get_object (builder, "treemodelServices"));
    interface->treeview_cli        = GTK_TREE_VIEW    (gtk_builder_get_object (builder, "ListaClientes"));
    interface->treemodel_cli       = GTK_TREE_MODEL   (gtk_builder_get_object (builder, "ClientesCadastrados"));
    interface->treeview_usu        = GTK_TREE_VIEW    (gtk_builder_get_object (builder, "ListaUsuarios"));
    interface->treemodel_usu       = GTK_TREE_MODEL   (gtk_builder_get_object (builder, "UserCadastrados"));
    interface->treeview_vei        = GTK_TREE_VIEW    (gtk_builder_get_object (builder, "ListaVeiculos"));
    interface->treemodel_vei       = GTK_TREE_MODEL   (gtk_builder_get_object (builder, "liststorevehicles"));
    interface->treeview_veicli     = GTK_TREE_VIEW    (gtk_builder_get_object (builder, "treeviewClientes"));
    interface->treeview_alt_veicli = GTK_TREE_VIEW    (gtk_builder_get_object (builder, "treeviewClientes1"));
    interface->treeview_insert_v   = GTK_TREE_VIEW    (gtk_builder_get_object (builder, "ListainserteVehicles"));
    interface->treemodel_insert_v  = GTK_TREE_MODEL   (gtk_builder_get_object (builder, "ModelInsertVehicle"));
    interface->insertVehicle       = GTK_ASSISTANT    (gtk_builder_get_object (builder, "ColocaVeiculoNaFila"));
    interface->window_timmer       = GTK_WIDGET       (gtk_builder_get_object (builder,"Timmer"));
    interface->labelTimmer         = GTK_LABEL        (gtk_builder_get_object (builder,"labelTimmer"));
    interface->labelTimmer1        = GTK_LABEL        (gtk_builder_get_object (builder,"labelTimmer1"));
    interface->labelTimmer2        = GTK_LABEL        (gtk_builder_get_object (builder,"labelTimmer2"));
    interface->extintor            = GTK_ENTRY_BUFFER (gtk_builder_get_object (builder,"entrybufferext"));
    interface->trocaOleo           = GTK_ENTRY_BUFFER (gtk_builder_get_object (builder,"entrybufferTrocaOleo"));
    interface->oleo                = GTK_ENTRY_BUFFER (gtk_builder_get_object (builder,"entrybufferoleo"));
    interface->dialog              = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder,"messagedialog1"));
    interface->diagnost            = GTK_ASSISTANT    (gtk_builder_get_object (builder,"assistantDiagnost"));
    interface->treeview_desp       = GTK_TREE_VIEW    (gtk_builder_get_object (builder,"treeviewDepesas"));
    interface->treemodel_despesa   = GTK_TREE_MODEL   (gtk_builder_get_object (builder,"despesas"));
    interface->entryCaixa          = GTK_WIDGET       (gtk_builder_get_object (builder,"EntradaDeCaixa"));
    interface->dataFila            = GTK_WIDGET       (gtk_builder_get_object (builder,"DataDaFila"));
    interface->dataFilaMes         = GTK_WIDGET       (gtk_builder_get_object (builder,"DataDoMes"));
    interface->dataFilaAno         = GTK_WIDGET       (gtk_builder_get_object (builder,"DataDoAno"));
    interface->passWord            = GTK_WIDGET       (gtk_builder_get_object (builder,"DigiteSenha"));
    interface->passWord1            = GTK_WIDGET       (gtk_builder_get_object (builder,"DigiteSenha1"));
    interface->passWord2            = GTK_WIDGET       (gtk_builder_get_object (builder,"DigiteSenha2"));
    interface->label_despesa       = GTK_LABEL        (gtk_builder_get_object (builder,"label92"));
    interface->true_or_false       = GTK_WIDGET       (gtk_builder_get_object (builder,"dialog1"));
    interface->mensagem_tf         = GTK_LABEL        (gtk_builder_get_object (builder,"label94"));
    interface->getfile             = GTK_FILE_CHOOSER_DIALOG (gtk_builder_get_object (builder,"filechooserdialog1"));
    interface->filterFile          = GTK_FILE_FILTER  (gtk_builder_get_object (builder,"filefilter1"));

    //conectando eventos e sinais
    gtk_builder_connect_signals (builder, interface);

    //conectando struct a interface
    iassistant->bufferName    =  GTK_ENTRY_BUFFER  (gtk_builder_get_object (builder,"entrybufferName"));
    iassistant->bufferPhone   =  GTK_ENTRY_BUFFER  (gtk_builder_get_object (builder,"entrybufferPhone"));
    iassistant->bufferInput   =  GTK_ENTRY_BUFFER  (gtk_builder_get_object (builder,"entrybufferEntrada"));
    iassistant->bufferOutput  =  GTK_ENTRY_BUFFER  (gtk_builder_get_object (builder,"entrybufferSaida"));
    iassistant->bufferPlaca   =  GTK_ENTRY_BUFFER  (gtk_builder_get_object (builder,"entrybufferPlaca"));
    iassistant->bufferModelo  =  GTK_ENTRY_BUFFER  (gtk_builder_get_object (builder,"entrybufferModelo"));
    iassistant->bufferCor     =  GTK_ENTRY_BUFFER  (gtk_builder_get_object (builder,"entrybufferCor"));
    iassistant->bufferRg      =  GTK_ENTRY_BUFFER  (gtk_builder_get_object (builder,"entrybufferRg"));
    iassistant->bufferEnd     =  GTK_ENTRY_BUFFER  (gtk_builder_get_object (builder,"entrybufferEnd"));
    iassistant->bufferValor   =  GTK_ENTRY_BUFFER  (gtk_builder_get_object (builder,"entrybufferValor"));
    iassistant->bufferValorP  =  GTK_ENTRY_BUFFER  (gtk_builder_get_object (builder,"entrybufferValorPequeno"));
    iassistant->bufferValorM  =  GTK_ENTRY_BUFFER  (gtk_builder_get_object (builder,"entrybufferValorMedio"));
    iassistant->bufferValorG  =  GTK_ENTRY_BUFFER  (gtk_builder_get_object (builder,"entrybufferValorGrande"));
    iassistant->bufferQuant   =  GTK_ENTRY_BUFFER  (gtk_builder_get_object (builder,"entrybufferNum"));
    iassistant->bufferDescri  =  GTK_TEXT_BUFFER   (gtk_builder_get_object (builder,"textbufferDescri"));
    iassistant->tamanho       =  GTK_COMBO_BOX     (gtk_builder_get_object (builder,"comboboxtextTamanho"));
    iassistant->alt_tamanho   =  GTK_COMBO_BOX     (gtk_builder_get_object (builder,"comboboxtextTamanho1"));
    iassistant->tipo          =  GTK_COMBO_BOX     (gtk_builder_get_object (builder,"comboboxtextTipo"));
    iassistant->tipo_alt      =  GTK_COMBO_BOX     (gtk_builder_get_object (builder,"comboboxtextTipo1"));

    //conectando eventos e sinais
    gtk_builder_connect_signals (builder, iassistant);


    /* liberando memoria dos objetos  */
    g_object_unref (G_OBJECT (builder));

    return TRUE;
}
