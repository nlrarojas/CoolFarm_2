#include "windownuevapartida.h"
#include <QStringList>

windownuevapartida::windownuevapartida(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::windownuevapartida)
{
    ui->setupUi(this);

    QLabel * tierra[8][8];
    for (int x=0; x<8; x++){
        for (int y=0; y<8; y++){
            tierra[x][y] = new QLabel(this->ui->juego);
            terreno[x][y] = new QLabel(this->ui->juego);
            tierra[x][y]->setPixmap(QPixmap(":/imagenes/tierra.png"));
            tierra[x][y]->setGeometry(x*50+50,y*50+50, 50, 50);
            terreno[x][y]->setGeometry(x*50+50,y*50+50, 50, 50);
            tierra[x][y]->setScaledContents(true);
            terreno[x][y]->setScaledContents(true);
            tierra[x][y]->show();
            terreno[x][y]->show();
        }
    }

    ui->tipoAnimales->addItem("Seleccione");
    ui->tipoAnimales->addItem("Ovejas");
    ui->tipoAnimales->addItem("Plagas");
    ui->tipoAnimales->addItem("Cuervos");
    ui->tipoArboles->addItem("Seleccione");
    ui->tipoArboles->addItem("ABB");
    ui->tipoArboles->addItem("HEAP");
    ui->tipoArboles->addItem("AVL");
    ui->tipoArboles->addItem("ROJINEGRO");

    lista = new ListaPlagas();
    lista->insertar(new plaga(0, 0, 0, 0, 0, "Cuervos"));
    lista->insertar(new plaga(0, 0, 0, 0, 0, "Ovejas"));
    lista->insertar(new plaga(0, 0, 0, 0, 0, "Plagas"));

    listaArbolesTerreno = new ListaNodosArbolesTerreno();

    tiposInfoArboles = new ListaNodosArboles();
    tiposInfoArboles->insertar(new NodoInfoArbol("ABB", 0, 0, 0, 0, 0, 0));
    tiposInfoArboles->insertar(new NodoInfoArbol("HEAP", 0, 0, 0, 0, 0, 0));
    tiposInfoArboles->insertar(new NodoInfoArbol("AVL", 0, 0, 0, 0, 0, 0));
    tiposInfoArboles->insertar(new NodoInfoArbol("ROJINEGRO", 0, 0, 0, 0, 0, 0));

    infoMercado = new Mercado(0, 0, 0, 0);
    infoEspantapajaros = new Espantapajaros(0.0, 0);
    granjero = new Granjero(0, 0, 0);
    mercadoPlataforma = new MercadoPlataforma();
    mercadoPlataforma->mercado = infoMercado;

    avlComprados = new ColaAVLComprados();
    abbComprados = new ColaABBComprados();
    heapComprados = new ColaHeapComprados();
    rojiNegroComprados = new ColaABBComprados();

    tipoPlaga = 0;
    tipoArbol = 0;
    cantidadEspantapajaros = 0;

    cantidadArbolesABB = 0;
    cantidadArbolesAVL = 0;
    cantitadArbolesRojiNegro = 0;
    cantidadArbolesHeap = 0;

    matrizJuego = new Matriz();
    matrizArboles = new MatrizArboles();

    terreno[granjero->posX][granjero->posY]->setPixmap(QPixmap(":/imagenes/granjero.png"));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizarDatosGUI()));
    timer->start(250);
    mercadoPlataforma->start();

    controlador = new ControladorHilos(matrizArboles, matrizJuego,
                                       tiposInfoArboles->buscarTipoArbol("ABB"),    tiposInfoArboles->buscarTipoArbol("AVL"),
                                       tiposInfoArboles->buscarTipoArbol("HEAP"),   tiposInfoArboles->buscarTipoArbol("ROJINEGRO"));
    controlador->start();
}

windownuevapartida::~windownuevapartida()
{
    delete ui;
}

void windownuevapartida::actualizarDatosGUI(){
    plaga * plagaActualizar;
    if(tipoPlaga == 1){
        plagaActualizar = lista->buscarPlaga("Ovejas");
        plagaActualizar->tasaPlagas = ui->spinBox_64->text().toInt();
        plagaActualizar->tiempo = ui->spinBox_65->text().toInt();
        plagaActualizar->probabilidad = ui->probabilidad->text().toInt();
        plagaActualizar->tasaFrutos = ui->spinBox_66->text().toInt();
        plagaActualizar->tiempoConsumeFrutos = ui->spinBox_67->text().toInt();
    }else if(tipoPlaga == 2){
        plagaActualizar = lista->buscarPlaga("Plagas");
        plagaActualizar->tasaPlagas = ui->spinBox_64->text().toInt();
        plagaActualizar->tiempo = ui->spinBox_65->text().toInt();
        plagaActualizar->probabilidad = ui->probabilidad->text().toInt();
        plagaActualizar->tasaFrutos = ui->spinBox_66->text().toInt();
        plagaActualizar->tiempoConsumeFrutos = ui->spinBox_67->text().toInt();
    }else if(tipoPlaga == 3){
        plagaActualizar = lista->buscarPlaga("Cuervos");
        plagaActualizar->tasaPlagas = ui->spinBox_64->text().toInt();
        plagaActualizar->tiempo = ui->spinBox_65->text().toInt();
        plagaActualizar->probabilidad = ui->probabilidad->text().toInt();
        plagaActualizar->tasaFrutos = ui->spinBox_66->text().toInt();
        plagaActualizar->tiempoConsumeFrutos = ui->spinBox_67->text().toInt();
    }

    NodoInfoArbol * nodoArbol;
    //Actualización valores de los arboles
    if(tipoArbol == 1){
        nodoArbol = tiposInfoArboles->buscarTipoArbol("ABB");
        nodoArbol->precio = ui->spinBox_79->text().toInt();
        nodoArbol->tiempoCrecimiento = ui->spinBox_78->text().toInt();
        nodoArbol->cantidadFrutos = ui->spinBox_81->text().toInt();
        nodoArbol->tiempoCosecha = ui->spinBox->text().toInt();
        nodoArbol->rangoInferior = ui->spinBox_3->text().toInt();
        nodoArbol->rangoSuperior = ui->spinBox_2->text().toInt();
    } else if(tipoArbol == 2){
        nodoArbol = tiposInfoArboles->buscarTipoArbol("HEAP");
        nodoArbol->precio = ui->spinBox_79->text().toInt();
        nodoArbol->tiempoCrecimiento = ui->spinBox_78->text().toInt();
        nodoArbol->cantidadFrutos = ui->spinBox_81->text().toInt();
        nodoArbol->tiempoCosecha = ui->spinBox->text().toInt();
        nodoArbol->rangoInferior = ui->spinBox_3->text().toInt();
        nodoArbol->rangoSuperior = ui->spinBox_2->text().toInt();
    } else if(tipoArbol == 3){
        nodoArbol = tiposInfoArboles->buscarTipoArbol("AVL");
        nodoArbol->precio = ui->spinBox_79->text().toInt();
        nodoArbol->tiempoCrecimiento = ui->spinBox_78->text().toInt();
        nodoArbol->cantidadFrutos = ui->spinBox_81->text().toInt();
        nodoArbol->tiempoCosecha = ui->spinBox->text().toInt();
        nodoArbol->rangoInferior = ui->spinBox_3->text().toInt();
        nodoArbol->rangoSuperior = ui->spinBox_2->text().toInt();
    } else if(tipoArbol == 4){
        nodoArbol = tiposInfoArboles->buscarTipoArbol("ROJINEGRO");
        nodoArbol->precio = ui->spinBox_79->text().toInt();
        nodoArbol->tiempoCrecimiento = ui->spinBox_78->text().toInt();
        nodoArbol->cantidadFrutos = ui->spinBox_81->text().toInt();
        nodoArbol->tiempoCosecha = ui->spinBox->text().toInt();
        nodoArbol->rangoInferior = ui->spinBox_3->text().toInt();
        nodoArbol->rangoSuperior = ui->spinBox_2->text().toInt();
    }

    infoEspantapajaros->costo = ui->spinBox_76->text().toInt();
    infoEspantapajaros->cantidadPorTerreno = ui->spinBox_77->text().toInt();

    infoMercado->tiempoAbre = ui->spinBox_73->text().toInt();
    infoMercado->tiempoAbierto = ui->spinBox_74->text().toInt();
    infoMercado->rangoInferior = ui->spinBox_75->text().toInt();
    infoMercado->rangoSuperior = ui->spinBox_4->text().toInt();
    mercadoPlataforma->mercado = infoMercado;

    //granjero->tiempoDesplazamiento = ui->spinBox_80->text().toInt();

    ui->label_cantidad_AVL->setText("AVL x " + QString::number(cantidadArbolesAVL));
    ui->label_cantidad_ABB->setText("Árbol binario x " + QString::number(cantidadArbolesABB));
    ui->label_cantidad_HEAP->setText("HEAP x " + QString::number(cantidadArbolesHeap));
    ui->label_cantidad_SPLAY->setText("ROJINEGRO x " + QString::number(cantitadArbolesRojiNegro));

    ui->label_cantidad_espantapajaros->setText("Cantidad: " + QString::number(cantidadEspantapajaros) + "/" + QString::number(infoEspantapajaros->cantidadPorTerreno));

    datosMercado();
    pintarTablero();
    estadoMercado();
    actualizarTablaArboles();
}

void windownuevapartida::on_tipoAnimales_currentIndexChanged(const QString &arg1)
{
    tipoPlaga = ui->tipoAnimales->currentIndex();
    plaga * plagaBuscar;
    if(tipoPlaga == 1){
        plagaBuscar = lista->buscarPlaga("Ovejas");
        ui->spinBox_64->setValue(plagaBuscar->tasaPlagas);
        ui->spinBox_65->setValue(plagaBuscar->tiempo);
        ui->probabilidad->setValue(plagaBuscar->probabilidad);
        ui->spinBox_66->setValue(plagaBuscar->tasaFrutos);
        ui->spinBox_67->setValue(plagaBuscar->tiempoConsumeFrutos);
    }else if(tipoPlaga == 2){
        plagaBuscar = lista->buscarPlaga("Plagas");
        ui->spinBox_64->setValue(plagaBuscar->tasaPlagas);
        ui->spinBox_65->setValue(plagaBuscar->tiempo);
        ui->probabilidad->setValue(plagaBuscar->probabilidad);
        ui->spinBox_66->setValue(plagaBuscar->tasaFrutos);
        ui->spinBox_67->setValue(plagaBuscar->tiempoConsumeFrutos);
    }else if(tipoPlaga == 3){
        plagaBuscar = lista->buscarPlaga("Cuervos");
        ui->spinBox_64->setValue(plagaBuscar->tasaPlagas);
        ui->spinBox_65->setValue(plagaBuscar->tiempo);
        ui->probabilidad->setValue(plagaBuscar->probabilidad);
        ui->spinBox_66->setValue(plagaBuscar->tasaFrutos);
        ui->spinBox_67->setValue(plagaBuscar->tiempoConsumeFrutos);
    }
}

void windownuevapartida::on_tipoArboles_currentIndexChanged(const QString &arg1)
{
    tipoArbol = ui->tipoArboles->currentIndex();
    NodoInfoArbol * nodoArbol;
    if(tipoArbol == 1){
        nodoArbol = tiposInfoArboles->buscarTipoArbol("ABB");
        ui->spinBox_79->setValue(nodoArbol->precio);
        ui->spinBox_78->setValue(nodoArbol->tiempoCrecimiento);
        ui->spinBox_81->setValue(nodoArbol->cantidadFrutos);
        ui->spinBox->setValue(nodoArbol->tiempoCosecha);
        ui->spinBox_3->setValue(nodoArbol->rangoInferior);
        ui->spinBox_2->setValue(nodoArbol->rangoSuperior);
    } else if(tipoArbol == 2){
        nodoArbol = tiposInfoArboles->buscarTipoArbol("HEAP");
        ui->spinBox_79->setValue(nodoArbol->precio);
        ui->spinBox_78->setValue(nodoArbol->tiempoCrecimiento);
        ui->spinBox_81->setValue(nodoArbol->cantidadFrutos);
        ui->spinBox->setValue(nodoArbol->tiempoCosecha);
        ui->spinBox_3->setValue(nodoArbol->rangoInferior);
        ui->spinBox_2->setValue(nodoArbol->rangoSuperior);
    } else if(tipoArbol == 3){
        nodoArbol = tiposInfoArboles->buscarTipoArbol("AVL");
        ui->spinBox_79->setValue(nodoArbol->precio);
        ui->spinBox_78->setValue(nodoArbol->tiempoCrecimiento);
        ui->spinBox_81->setValue(nodoArbol->cantidadFrutos);
        ui->spinBox->setValue(nodoArbol->tiempoCosecha);
        ui->spinBox_3->setValue(nodoArbol->rangoInferior);
        ui->spinBox_2->setValue(nodoArbol->rangoSuperior);
    } else if(tipoArbol == 4){
        nodoArbol = tiposInfoArboles->buscarTipoArbol("ROJINEGRO");
        ui->spinBox_79->setValue(nodoArbol->precio);
        ui->spinBox_78->setValue(nodoArbol->tiempoCrecimiento);
        ui->spinBox_81->setValue(nodoArbol->cantidadFrutos);
        ui->spinBox->setValue(nodoArbol->tiempoCosecha);
        ui->spinBox_3->setValue(nodoArbol->rangoInferior);
        ui->spinBox_2->setValue(nodoArbol->rangoSuperior);
    }
}

void windownuevapartida::datosMercado(){
    ui->lineEdit_costo_espantapajaros->setText(QString::number(infoEspantapajaros->costo));
    ui->label_cantidad_espantapajaros->setText("Cantidad: " + QString::number(cantidadEspantapajaros) + "/" + QString::number(infoEspantapajaros->cantidadPorTerreno));

    NodoInfoArbol * abb = tiposInfoArboles->buscarTipoArbol("ABB");
    NodoInfoArbol * avl = tiposInfoArboles->buscarTipoArbol("AVL");
    NodoInfoArbol * heap = tiposInfoArboles->buscarTipoArbol("HEAP");
    NodoInfoArbol * rojinegro = tiposInfoArboles->buscarTipoArbol("ROJINEGRO");

    ui->lineEdit_costo_abb->setText(QString::number(abb->precio));
    ui->lineEdit_crece_abb->setText(QString::number(abb->tiempoCrecimiento));

    ui->lineEdit_costo_avl->setText(QString::number(avl->precio));
    ui->lineEdit_crece_avl->setText(QString::number(avl->tiempoCrecimiento));

    ui->lineEdit_costo_heap->setText(QString::number(heap->precio));
    ui->lineEdit_crece_heap->setText(QString::number(heap->tiempoCrecimiento));

    ui->lineEdit_costo_rojinegro->setText(QString::number(rojinegro->precio));
    ui->lineEdit_crece_rojinegro->setText(QString::number(rojinegro->tiempoCrecimiento));
}

void windownuevapartida::pintarTablero(){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(matrizJuego->matrizJuego[i][j] == 1){
                terreno[i][j]->setPixmap(QPixmap(":/imagenes/granjero.png"));
            } else if(matrizJuego->matrizJuego[i][j] == 10){
                terreno[i][j]->setPixmap(QPixmap(":/imagenes/heap.png"));
            } else if(matrizJuego->matrizJuego[i][j] == 3){
                terreno[i][j]->setPixmap(QPixmap(":/imagenes/avl.png"));
            } else if(matrizJuego->matrizJuego[i][j] == 4){
                terreno[i][j]->setPixmap(QPixmap(":/imagenes/abb.png"));
            } else if(matrizJuego->matrizJuego[i][j] == 5){
                terreno[i][j]->setPixmap(QPixmap(":/imagenes/rojinegro.png"));
            } else if(matrizJuego->matrizJuego[i][j] == 6){
                terreno[i][j]->setPixmap(QPixmap(":/imagenes/espantapajaros.png"));
            } else if(matrizJuego->matrizJuego[i][j] == 7){
                terreno[i][j]->setPixmap(QPixmap(":/imagenes/cuervo.png"));
            } else if(matrizJuego->matrizJuego[i][j] == 8){
                terreno[i][j]->setPixmap(QPixmap(":/imagenes/plaga.png"));
            } else if(matrizJuego->matrizJuego[i][j] == 9){
                terreno[i][j]->setPixmap(QPixmap(":/imagenes/oveja.png"));
            }
        }
    }
}

void windownuevapartida::keyPressEvent(QKeyEvent * tecla){
    if (tecla->key() == Qt::Key_A){
        terreno[granjero->posX][granjero->posY]->setPixmap(QPixmap(" "));
        granjero->moverIzquierda();
        terreno[granjero->posX][granjero->posY]->setPixmap(QPixmap(":/imagenes/granjero.png"));
    }
    if (tecla->key() == Qt::Key_W){
        terreno[granjero->posX][granjero->posY]->setPixmap(QPixmap(" "));
        granjero->moverArriba();
        terreno[granjero->posX][granjero->posY]->setPixmap(QPixmap(":/imagenes/granjero.png"));
    }
    if (tecla->key() == Qt::Key_S){
        terreno[granjero->posX][granjero->posY]->setPixmap(QPixmap(" "));
        granjero->moverAbajo();
        terreno[granjero->posX][granjero->posY]->setPixmap(QPixmap(":/imagenes/granjero.png"));

    }
    if (tecla->key() == Qt::Key_D){
        terreno[granjero->posX][granjero->posY]->setPixmap(QPixmap(" "));
        granjero->moverDerecha();
        terreno[granjero->posX][granjero->posY]->setPixmap(QPixmap(":/imagenes/granjero.png"));
    }
    if (tecla->key() == Qt::Key_H){
        sembrarArbolHEAP();
    }
    if (tecla->key() == Qt::Key_J){
        sembrarArbolABB();
    }
    if (tecla->key() == Qt::Key_K){
        sembrarArbolAVL();
    }
    if (tecla->key() == Qt::Key_L){
        sembrarArbolRojiNegro();
    }
    if (tecla->key() == Qt::Key_P){
        colocarEspantapajaros();
    }
}

void windownuevapartida::estadoMercado(){
    if(mercadoPlataforma->estado){
        ui->label_estado_mercado->setText("Estado: Abierto");
    }else{
        ui->label_estado_mercado->setText("Estado: Cerrado");
    }
}

void windownuevapartida::on_toolButton_3_clicked()
{
    comprarAbolAVL();
}

void windownuevapartida::on_toolButton_6_clicked()
{
    comprarAbolRojinegro();
}

void windownuevapartida::on_toolButton_4_clicked()
{
    comprarAbolHeap();
}

void windownuevapartida::on_toolButton_5_clicked()
{
    comprarAbolABB();
}

void windownuevapartida::comprarAbolAVL(){
    if(mercadoPlataforma->estado){
        NodoInfoArbol * temporal = tiposInfoArboles->buscarTipoArbol("AVL");
        Avl * nuevoArbol = new Avl(temporal);
        avlComprados->encolar(new NodoArbolAVL(nuevoArbol));
        cantidadArbolesAVL++;
    }else{
        mostrarMensaje("El mercado no está abierto. Tiene que esperar a que abra para poder realizar su compra");
    }
}

void windownuevapartida::comprarAbolABB(){
    if(mercadoPlataforma->estado){
        NodoInfoArbol * temporal = tiposInfoArboles->buscarTipoArbol("ABB");
        Arbol * nuevoArbol = new Arbol(temporal);
        abbComprados->encolar(new NodoArbolABB(nuevoArbol));
        cantidadArbolesABB++;
    }else{
        mostrarMensaje("El mercado no está abierto. Tiene que esperar a que abra para poder realizar su compra");
    }
}

void windownuevapartida::comprarAbolHeap(){
    if(mercadoPlataforma->estado){
        NodoInfoArbol * temporal = tiposInfoArboles->buscarTipoArbol("HEAP");
        Heap * nuevoArbol = new Heap(temporal);
        heapComprados->encolar(new NodoArbolHeap(nuevoArbol));
        cantidadArbolesHeap++;
    }else{
        mostrarMensaje("El mercado no está abierto. Tiene que esperar a que abra para poder realizar su compra");
    }
}

void windownuevapartida::comprarAbolRojinegro(){
    if(mercadoPlataforma->estado){
        NodoInfoArbol * temporal = tiposInfoArboles->buscarTipoArbol("ROJINEGRO");
        Arbol * nuevoArbol = new Arbol(temporal);
        rojiNegroComprados->encolar(new NodoArbolABB(nuevoArbol));
        cantitadArbolesRojiNegro++;
    }else{
        mostrarMensaje("El mercado no está abierto. Tiene que esperar a que abra para poder realizar su compra");
    }
}

void windownuevapartida::sembrarArbolAVL(){
    if(matrizJuego->matrizJuego[granjero->posX][granjero->posY] == 0 || matrizJuego->matrizJuego[granjero->posX][granjero->posY] == -1
            || matrizJuego->matrizJuego[granjero->posX][granjero->posY] == 2){
        if(!avlComprados->isEmpty()){
            Avl * temporal = avlComprados->desEncolar()->arbolAVL;
            NodoArbolesTerreno * nuevoNodoArbolesTerreno = new NodoArbolesTerreno(NULL, temporal, NULL, NULL, "AVL");
            matrizArboles->Terreno[granjero->posX][granjero->posY] = nuevoNodoArbolesTerreno;
            matrizJuego->matrizJuego[granjero->posX][granjero->posY] = 3;
            nuevoNodoArbolesTerreno->posX = granjero->posX;
            nuevoNodoArbolesTerreno->posY = granjero->posY;
            listaArbolesTerreno->insertar(nuevoNodoArbolesTerreno);
            matrizJuego->estado[granjero->posX][granjero->posY] += 2;
            cantidadArbolesAVL--;
            insertarEnTablaArboles();
        }else{
            mostrarMensaje("No tiene árboles disponibles debe de comprar");
        }
    } else{
        mostrarMensaje("No puede sembrar un árbol en esa posición");
    }
}

void windownuevapartida::sembrarArbolABB(){
    if(matrizJuego->matrizJuego[granjero->posX][granjero->posY] == 0 || matrizJuego->matrizJuego[granjero->posX][granjero->posY] == -1
            || matrizJuego->matrizJuego[granjero->posX][granjero->posY] == 2){
        if(!abbComprados->isEmpty()){
            if(validarInfoArbol("ABB")){
                Arbol * temporal = abbComprados->desEncolar()->arbolABB;
                NodoArbolesTerreno * nuevoNodoArbolesTerreno = new NodoArbolesTerreno(temporal, NULL, NULL, NULL, "ABB");
                matrizArboles->Terreno[granjero->posX][granjero->posY] = nuevoNodoArbolesTerreno;
                matrizJuego->matrizJuego[granjero->posX][granjero->posY] = 4;
                matrizJuego->estado[granjero->posX][granjero->posY] += 2;
                nuevoNodoArbolesTerreno->posX = granjero->posX;
                nuevoNodoArbolesTerreno->posY = granjero->posY;
                listaArbolesTerreno->insertar(nuevoNodoArbolesTerreno);
                cantidadArbolesABB--;
                insertarEnTablaArboles();
            }
        }else{
            mostrarMensaje("No tiene árboles disponibles debe de comprar");
        }
    } else{
        mostrarMensaje("No puede sembrar un árbol en esa posición");
    }
}

void windownuevapartida::sembrarArbolHEAP(){
    if(matrizJuego->matrizJuego[granjero->posX][granjero->posY] == 0 || matrizJuego->matrizJuego[granjero->posX][granjero->posY] == -1
            || matrizJuego->matrizJuego[granjero->posX][granjero->posY] == 2){
        if(!heapComprados->isEmpty()){
            Heap * temporal = heapComprados->desEncolar()->arbolHeap;
            NodoArbolesTerreno * nuevoNodoArbolesTerreno = new NodoArbolesTerreno(NULL, NULL, temporal, NULL, "HEAP");
            matrizArboles->Terreno[granjero->posX][granjero->posY] = nuevoNodoArbolesTerreno;
            matrizJuego->matrizJuego[granjero->posX][granjero->posY] = 10;
            matrizJuego->estado[granjero->posX][granjero->posY] += 2;
            nuevoNodoArbolesTerreno->posX = granjero->posX;
            nuevoNodoArbolesTerreno->posY = granjero->posY;
            listaArbolesTerreno->insertar(nuevoNodoArbolesTerreno);
            cantidadArbolesHeap--;
            insertarEnTablaArboles();
        }else{
            mostrarMensaje("No tiene árboles disponibles debe de comprar");
        }
    } else{
        mostrarMensaje("No puede sembrar un árbol en esa posición");
    }
}

void windownuevapartida::sembrarArbolRojiNegro(){
    if(matrizJuego->matrizJuego[granjero->posX][granjero->posY] == 0 || matrizJuego->matrizJuego[granjero->posX][granjero->posY] == -1
            || matrizJuego->matrizJuego[granjero->posX][granjero->posY] == 2){
        if(!rojiNegroComprados->isEmpty()){
            Arbol * temporal = rojiNegroComprados->desEncolar()->arbolABB;
            NodoArbolesTerreno * nuevoNodoArbolesTerreno = new NodoArbolesTerreno(NULL, NULL, NULL, temporal, "ROJINEGRO");
            matrizArboles->Terreno[granjero->posX][granjero->posY] = nuevoNodoArbolesTerreno;
            matrizJuego->matrizJuego[granjero->posX][granjero->posY] = 5;
            matrizJuego->estado[granjero->posX][granjero->posY] += 2;
            nuevoNodoArbolesTerreno->posX = granjero->posX;
            nuevoNodoArbolesTerreno->posY = granjero->posY;
            listaArbolesTerreno->insertar(nuevoNodoArbolesTerreno);
            cantitadArbolesRojiNegro--;
            insertarEnTablaArboles();
        }else{
            mostrarMensaje("No tiene árboles disponibles debe de comprar");
        }
    } else{
        mostrarMensaje("No puede sembrar un árbol en esa posición");
    }
}

void windownuevapartida::colocarEspantapajaros(){
    if(matrizJuego->matrizJuego[granjero->posX][granjero->posY] == 0){
        if(cantidadEspantapajaros > 0){
            matrizJuego->matrizJuego[granjero->posX][granjero->posY] = 6;
            matrizJuego->estado[granjero->posX][granjero->posY] = 3;
            protegerAdyacentes(granjero->posX,granjero->posY);
            cantidadEspantapajaros--;
        }else
            mostrarMensaje("No tiene más espantapájaros disponibles");
    }else{
        mostrarMensaje("No puede colocar el espantapájaros en esa posición por que está ocupado por otro objeto");
    }
}

void windownuevapartida::on_toolButton_7_clicked()
{
    if(mercadoPlataforma->estado){
        if(cantidadEspantapajaros < infoEspantapajaros->cantidadPorTerreno){
            cantidadEspantapajaros++;
        }else{
            mostrarMensaje("Ya no puede comprar más espantapajaros");
        }
    }else{
        mostrarMensaje("El mercado no está abierto. Tiene que esperar a que abra para poder realizar su compra");
    }
}

void windownuevapartida::mostrarMensaje(QString mensaje){
    QMessageBox * msgBox = new QMessageBox();
    msgBox->setText(mensaje);
    msgBox->show();
    msgBox->setAttribute(Qt::WA_DeleteOnClose);
    QTimer::singleShot(2000, msgBox, SLOT(close()));
}

void windownuevapartida::insertarEnTablaArboles(){
    int filas = 0;
    QTableWidgetItem *item, *item2;
    NodoArbolesTerreno * temporal = listaArbolesTerreno->primerNodo;
    while (temporal != NULL){

        QString tipo = temporal->tipoArbol;
        ui->tablaArbolesComprados->setRowCount(filas + 1);
        item = new QTableWidgetItem(tipo);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);

        QString ubicacion = QString::number(temporal->posX) + " , " + QString::number(temporal->posY);
        item2 = new QTableWidgetItem(ubicacion);
        item2->setFlags(item2->flags() & ~Qt::ItemIsEditable);
        if(tipo == "ABB"){
            ui->tablaArbolesComprados->setItem(filas, 0, item);
            item = new QTableWidgetItem(QString::number(temporal->abb->cantidadFrutos()));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 2, item);
            item = new QTableWidgetItem(QString::number(temporal->abb->montoTotal()));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 3, item);
            item = new QTableWidgetItem(QString::number(temporal->abb->vendidos));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 4, item);
            item = new QTableWidgetItem(QString::number(temporal->abb->perdidos));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 5, item);
            ui->tablaArbolesComprados->setItem(filas++, 1, item2);
        }else if(tipo == "AVL"){
            temporal->avl;
            ui->tablaArbolesComprados->setItem(filas, 0, item);
            item = new QTableWidgetItem(QString::number(temporal->avl->cantidadFrutos()));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 2, item);
            item = new QTableWidgetItem(QString::number(temporal->avl->montoTotal()));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 3, item);
            item = new QTableWidgetItem(QString::number(temporal->avl->vendidos));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 4, item);
            item = new QTableWidgetItem(QString::number(temporal->avl->perdidos));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 5, item);
            ui->tablaArbolesComprados->setItem(filas++, 1, item2);
        }else if(tipo == "HEAP"){
            temporal->heap;
            ui->tablaArbolesComprados->setItem(filas, 0, item);
            item = new QTableWidgetItem(QString::number(temporal->heap->cantidadFrutos()));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 2, item);
            item = new QTableWidgetItem(QString::number(temporal->heap->montoTotal()));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 3, item);
            item = new QTableWidgetItem(QString::number(temporal->heap->vendidos));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 4, item);
            item = new QTableWidgetItem(QString::number(temporal->heap->perdidos));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 5, item);
            ui->tablaArbolesComprados->setItem(filas++, 1, item2);
        }else if(tipo == "ROJINEGRO"){
            temporal->rojinegro;
            ui->tablaArbolesComprados->setItem(filas, 0, item);
            item = new QTableWidgetItem(QString::number(temporal->rojinegro->cantidadFrutos()));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 2, item);
            item = new QTableWidgetItem(QString::number(temporal->rojinegro->montoTotal()));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 3, item);
            item = new QTableWidgetItem(QString::number(temporal->rojinegro->vendidos));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 4, item);
            item = new QTableWidgetItem(QString::number(temporal->rojinegro->perdidos));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tablaArbolesComprados->setItem(filas, 5, item);
            ui->tablaArbolesComprados->setItem(filas++, 1, item2);
        }
        temporal = temporal->siguiente;
    }
}

void windownuevapartida::actualizarTablaArboles(){
    int filas = ui->tablaArbolesComprados->rowCount();
    int posX = 0;
    int posY = 0;
    QString tipo;
    QString posiciones;
    QStringList pos;
    for (int i = 0; i < filas; i++) {
        posiciones = ui->tablaArbolesComprados->item(i, 1)->text();
        pos = posiciones.split(" , ");
        posX = pos.at(0).toInt();
        posY = pos.at(1).toInt();

        tipo = matrizArboles->Terreno[posX][posY]->tipoArbol;
        if(tipo == "ABB"){
            Arbol * nodo = matrizArboles->Terreno[posX][posY]->abb;
            ui->tablaArbolesComprados->item(i, 2)->setText(QString::number(nodo->cantidadFrutos()));
            ui->tablaArbolesComprados->item(i, 3)->setText(QString::number(nodo->montoTotal()));
            ui->tablaArbolesComprados->item(i, 4)->setText(QString::number(nodo->vendidos));
            ui->tablaArbolesComprados->item(i, 5)->setText(QString::number(nodo->perdidos));
        }
        if(tipo == "AVL"){
            Avl * nodo = matrizArboles->Terreno[posX][posY]->avl;
            ui->tablaArbolesComprados->item(i, 2)->setText(QString::number(nodo->cantidadFrutos()));
            ui->tablaArbolesComprados->item(i, 3)->setText(QString::number(nodo->montoTotal()));
            ui->tablaArbolesComprados->item(i, 4)->setText(QString::number(nodo->vendidos));
            ui->tablaArbolesComprados->item(i, 5)->setText(QString::number(nodo->perdidos));
        }
        if(tipo == "HEAP"){
            Heap * nodo = matrizArboles->Terreno[posX][posY]->heap;
            ui->tablaArbolesComprados->item(i, 2)->setText(QString::number(nodo->cantidadFrutos()));
            ui->tablaArbolesComprados->item(i, 3)->setText(QString::number(nodo->montoTotal()));
            ui->tablaArbolesComprados->item(i, 4)->setText(QString::number(nodo->vendidos));
            ui->tablaArbolesComprados->item(i, 5)->setText(QString::number(nodo->perdidos));
        }
        if(tipo == "ROJINEGRO"){
            Arbol * nodo = matrizArboles->Terreno[posX][posY]->rojinegro;
            ui->tablaArbolesComprados->item(i, 2)->setText(QString::number(nodo->cantidadFrutos()));
            ui->tablaArbolesComprados->item(i, 3)->setText(QString::number(nodo->montoTotal()));
            ui->tablaArbolesComprados->item(i, 4)->setText(QString::number(nodo->vendidos));
            ui->tablaArbolesComprados->item(i, 5)->setText(QString::number(nodo->perdidos));
        }
    }
}


bool windownuevapartida::validarInfoArbol(QString tipoArbol){
    NodoInfoArbol * temporal = tiposInfoArboles->buscarTipoArbol(tipoArbol);
    if (temporal->cantidadFrutos == 0){
        mostrarMensaje("Ingrese la cantidad de frutos del arbol en la sección de configuración");
        return false;
    }
    if(temporal->precio == 0){
        mostrarMensaje("Ingrese el precio del arbol en la sección de configuración");
        return false;
    }
    if(temporal->rangoInferior >= temporal->rangoSuperior){
        mostrarMensaje("El rango inferior es mayor o igual al rango superior");
        return false;
    }
    if(temporal->tiempoCosecha == 0){
        mostrarMensaje("Ingrese el tiempo que tarda en producir cosecha el arbol en la sección de configuración");
        return false;
    }
    if(temporal->tiempoCrecimiento == 0){
        mostrarMensaje("Ingrese el tiempo de crecimiento del arbol en la sección de configuración");
        return false;
    }
    return true;
}

void windownuevapartida::protegerAdyacentes(int x, int y){
    if (y-1 > -1 && x-1> -1){
        if (matrizJuego->estado[x-1][y-1] == 1)
            matrizJuego->estado[x-1][y-1] = 2;
        else if(matrizJuego->estado[x-1][y-1] == -1)
            matrizJuego->estado[x-1][y-1] = 0;
    }if ( y-1 > -1 && x+1 < 8){
        if (matrizJuego->estado[x+1][y-1] == 1)
            matrizJuego->estado[x+1][y-1] = 2;
        else if(matrizJuego->estado[x+1][y-1] == -1)
            matrizJuego->estado[x+1][y-1] = 0;
    }if ( y-1 > -1 ){
        if (matrizJuego->estado[x][y-1] == 1)
            matrizJuego->estado[x][y-1] = 2;
        else if(matrizJuego->estado[x][y-1] == -1)
            matrizJuego->estado[x][y-1] = 0;
    }if (y+1 < 8 && x-1 > -1){
        if (matrizJuego->estado[x-1][y+1] == 1)
            matrizJuego->estado[x-1][y+1] = 2;
        else if(matrizJuego->estado[x-1][y+1] == -1)
            matrizJuego->estado[x-1][y+1] = 0;
    }if ( y+1 < 8 && x+1 < 8){
        if (matrizJuego->estado[x+1][y+1] == 1)
            matrizJuego->estado[x+1][y+1] = 2;
        else if(matrizJuego->estado[x+1][y+1] == -1)
            matrizJuego->estado[x+1][y+1]= 0;
    }if ( y+1 < 8 ){
        if (matrizJuego->estado[x][y+1] == 1)
            matrizJuego->estado[x][y+1] = 2;
        else if(matrizJuego->estado[x][y+1] == -1)
            matrizJuego->estado[x][y+1] = 0;
    }if (x-1 > -1){
        if (matrizJuego->estado[x-1][y] == 1)
            matrizJuego->estado[x-1][y] = 2;
        else if(matrizJuego->estado[x-1][y] == -1)
            matrizJuego->estado[x-1][y] = 0;
    }if (x+1 <8){
        if (matrizJuego->estado[x+1][y] == 1)
            matrizJuego->estado[x+1][y] = 2;
        else if(matrizJuego->estado[x+1][y] == -1)
            matrizJuego->estado[x+1][y] = 0;
    }
}

void windownuevapartida::on_toolButton_clicked()
{
    controlador->cambiarEstado(2);
    ui->label_estado_juego->setText("Estado: Pausado");
}

void windownuevapartida::on_toolButton_8_clicked()
{
    controlador->cambiarEstado(3);
    ui->label_estado_juego->setText("Estado: Activo");
}
