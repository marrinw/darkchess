#include"netserver.h"

netserver::netserver(){
    this->serverSide=0;
    this->setWindowTitle("服务器端红人");
    this->server=new QTcpServer(this);
    this->server->listen(QHostAddress::Any,8080);
    connect(server,SIGNAL(newConnection()),this,SLOT(ConnectToClient()));

}

netserver::~netserver(){
    delete this->socket;
    delete this->server;
}

void netserver::DataArrive(){
    QByteArray buffer = socket->readAll();
    if(this->chessb.getplayernow()!=this->serverSide){
        int x=buffer[0];
        int y=buffer[1];
        this->chessb.func(x,y);
        if(buffer.size()==4){
            x=buffer[2];
            y=buffer[3];
            this->chessb.func(x,y);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        int ifend=this->print();
        this->repaint();
        this->sendinfo();
        if(ifend!=3){
            this->socket->close();
            this->server->close();
        }
    }

}
void netserver::ConnectToClient(){
    this->socket=this->server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(DataArrive()));
    this->sendinfo();
    QMessageBox::information(this,
                             tr("连接成功"),
                             tr("连接成功!"));
}
void netserver::sendinfo(){
    this->socket->flush();
    char info[193];
    int i=0;
    for(int j=0;j<4;j++){
        for(int k=0;k<8;k++){
            info[i]=this->chessb.getchessdeck(k,j).getid()+'0';
            i++;
            info[i]=this->chessb.getchessdeck(k,j).getside()+'0';
            i++;
            info[i]=this->chessb.getchessdeck(k,j).getvisible()+'0';
            i++;
        }
    }
    info[i]=this->chessb.getplayernow()+'0';
    i++;
    for(int j=0;j<4;j++){
        for(int k=0;k<8;k++){
            info[i]=this->chessb.getdeadchessdeck(k,j).getid()+'0';
            i++;
            info[i]=this->chessb.getdeadchessdeck(k,j).getside()+'0';
            i++;
            info[i]=this->chessb.getdeadchessdeck(k,j).getvisible()+'0';
            i++;
        }
    }
    int k;
    do{
        this->socket->flush();
        k=this->socket->write(info,193);
    }while(k!=193);

}
void netserver::getclicked(int x,int y){
    if(this->chessb.getplayernow()==this->serverSide){
        this->chessb.func(x,y);
        this->print();
        this->sendinfo();
    }
}
